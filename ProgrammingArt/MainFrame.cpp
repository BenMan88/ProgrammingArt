#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include "utils/RGBImage.hpp"
#include <cmath>
#include <gd.h>
#include <utils/GDUtils.hpp>

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
    
    gdImagePtr gdImagePtr = loadPng("somefile.png");
    
    for(int64_t y = 0; y < gdImagePtr->sy; ++y){
        for(int64_t x = 0; x < gdImagePtr->sx; ++x){
            uint32_t color = gdImagePtr->tpixels[y][x];
            gdImagePtr->tpixels[y][x] = color*color;
        }
    }
    
    
    RGBImage rgbImage(gdImagePtr->sx, gdImagePtr->sy);
    for(int64_t y = 0; y < gdImagePtr->sy; ++y){
        for(int64_t x = 0; x < gdImagePtr->sx; ++x){
            uint32_t color = gdImagePtr->tpixels[y][x];
            rgbImage.setPixel(x, y, color);
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
