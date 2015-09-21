#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include "utils/RGBImage.hpp"
#include <cmath>

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
MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    
    assert(isPrime(7) == true);
    assert(isPrime(3) == true);
    assert(isPrime(2) == true);
    assert(isPrime(2333) == true);
    
    assert(isPrime(8) == false);
    assert(isPrime(128) == false);
    assert(isPrime(3123*231) == false);
    
    RGBImage rgbImage(1000, 1000);
    for(int64_t y = 0; y < rgbImage.height(); ++y){
        for(int64_t x = 0; x < rgbImage.width(); ++x){
            int64_t index = 1000*1000*100 + x + y*rgbImage.width();
            if(isPrime(index)){
                rgbImage.setPixel(x, y, 0x00FF00);
            } else {
                rgbImage.setPixel(x, y, 0x000000);
            }
        }
    }
    
    wxImage image(rgbImage.width(), rgbImage.height(), rgbImage.data());
    rgbImage.releaseOwnership();
    
    wxBitmap bitmap(image);
    
    m_outputBitmap->SetBitmap(bitmap);
    
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
