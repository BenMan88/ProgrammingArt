#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include "utils/RGBImage.hpp"
#include <cmath>

bool isPrime(int x) {
    if(x <= 2){
        return true;
    }
    
    int root = std::sqrt(x)+1;
    
    for(int i = 2; i < root; ++i){
        if((x % i) == 0){
            return false;
        }
    }
    return true;
}
MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    RGBImage rgbImage(1000, 1000);
    for(int y = 0; y < rgbImage.height(); ++y){
        for(int x = 0; x < rgbImage.width(); ++x){
            int index = x + y*rgbImage.width();
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
