#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include "utils/RGBImage.hpp"


MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    RGBImage rgbImage(1000, 1000);
    for(int y = 0; y < rgbImage.height(); ++y){
        for(int x = 0; x < rgbImage.width(); ++x){
            rgbImage.setPixel(x, y, x*y);
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
