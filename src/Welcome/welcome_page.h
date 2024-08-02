// defination for the welcomepage class

#pragma once
#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/hyperlink.h>

class WelcomePage : public wxPanel
{
public:
    WelcomePage(wxWindow* parent);

private:
    void CreateLayout();
    void OnNewFile(wxCommandEvent& event);
    void OnOpenFile(wxCommandEvent& event);
    void OnOpenFolder(wxCommandEvent& event);

    wxStaticText* m_titleText;
    wxStaticText* m_subtitleText;
    wxHyperlinkCtrl* m_newFileLink;
    wxHyperlinkCtrl* m_openFileLink;
    wxHyperlinkCtrl* m_openFolderLink;
};
