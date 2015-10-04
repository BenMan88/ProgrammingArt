#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include "utils/RGBImage.hpp"
#include <cmath>
#include <gd.h>
#include "utils/GDUtils.hpp"
#include <memory>
#include <mutex>
#include <condition_variable>
#include "utils/ThreadUtils.hpp"
#include <chrono>
#include <thread>

inline double degreesToRadians(double degrees){
    double radians = degrees*M_PI/180.0;
    return radians;
}
bool isPrime(int64_t x) {
    if(x <= 2){
        return true;
    }
    
    int64_t root = std::sqrt(x)+1;
    
    for(int64_t i = 2; i < root; ++i){
        if((x % i) == 0){
            return false;
        }
    }
    return true;
}

std::shared_ptr<gdImage> makeGdImageSharedPtr(gdImagePtr image){
    std::shared_ptr<gdImage> imagePtr(image, [](gdImagePtr imagePtr){
       gdImageDestroy(imagePtr); 
    });
    return imagePtr;
}

void circleFractal(std::shared_ptr<gdImage> imagePtr, int cx, int cy, int radius){
    if(radius < 10){
        return;
    }
    gdImageEllipse(imagePtr.get(), cx, cy, radius*2, radius*2, 0x0000FF00);
    
    circleFractal(imagePtr, cx-radius, cy, radius/2);
    circleFractal(imagePtr, cx+radius, cy, radius/2);
    circleFractal(imagePtr, cx, cy+radius, radius/2);
    circleFractal(imagePtr, cx, cy-radius, radius/2);
}

void treeFractal(std::shared_ptr<gdImage> imagePtr, int startX, int startY, double angle, double length){
    if(length < 1){
        return;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    int endX = cos(angle)*length + startX;
    int endY = sin(angle)*length + startY;
    
    gdImageLine(imagePtr.get(), startX, startY, endX, endY, rand());
    
    treeFractal(imagePtr, endX, endY, angle - degreesToRadians(-50), length*0.6);
    treeFractal(imagePtr, endX, endY, angle + degreesToRadians(-50), length*0.6);
}

std::shared_ptr<gdImage> fractalTest(std::shared_ptr<gdImage> image){
    assert(image != nullptr);
    int width = image->sx;
    int height = image->sy;
    
    //circleFractal(image, width/2, height/2, 300);
    treeFractal(image, width/2, height-1, degreesToRadians(-90), 300);
    return image;
}

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{

    
}

MainFrame::~MainFrame()
{
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.SetCopyright(_("My MainFrame"));
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(_("Short description goes here"));
    ::wxAboutBox(info);
}
void MainFrame::onStart(wxCommandEvent& event)
{
    assert(isPrime(7) == true);
    assert(isPrime(3) == true);
    assert(isPrime(2) == true);
    assert(isPrime(2333) == true);
    
    assert(isPrime(8) == false);
    assert(isPrime(128) == false);
    assert(isPrime(3123*231) == false);
    
    int width = 1000;
    int height = 1000;
    std::shared_ptr<gdImage> gdImagePtr = makeGdImageSharedPtr(gdImageCreateTrueColor(width, height));

    spawnThread([this, gdImagePtr]{
        assert(gdImagePtr != nullptr);
        fractalTest(gdImagePtr);
    });
    
    spawnThread([this, gdImagePtr]{
        while(true){
            assert(gdImagePtr != nullptr);
            // converts gdImagePtr to rgbImage
            RGBImage rgbImage(gdImagePtr->sx, gdImagePtr->sy);
            for(int64_t y = 0; y < gdImagePtr->sy; ++y){
                for(int64_t x = 0; x < gdImagePtr->sx; ++x){
                    uint32_t color = gdImagePtr->tpixels[y][x];
                    rgbImage.setPixel(x, y, color);
                }
            }
            
            
            
            wxImage image(rgbImage.width(), rgbImage.height(), rgbImage.data());
            rgbImage.releaseOwnership();
            
            

            syncOnThread([this](const std::function<void()> &func){
                this->CallAfter(func);
            }, [this, &image]{
                wxBitmap bitmap(image);
                this->m_outputBitmap->SetBitmap(bitmap);
            });
        }

    });

}
