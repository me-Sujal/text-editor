// Generat a welcome page for the application

#include "welcome_page.h"
#include"../gui/mainframe.h"
#include <wx/sizer.h>
#include <wx/font.h>

WelcomePage::WelcomePage(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    SetBackgroundColour(wxColour(240, 240, 240));
    CreateLayout();
}

void WelcomePage::CreateLayout()
{
    //SetBackgroundColour(wxColour(240, 240, 240));  // Light grey background

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Title
    m_titleText = new wxStaticText(this, wxID_ANY, "Welcome to CodeLite");
    wxFont titleFont = m_titleText->GetFont();
    titleFont.SetPointSize(24);
    titleFont.SetWeight(wxFONTWEIGHT_BOLD);
    m_titleText->SetFont(titleFont);

    // Subtitle
    m_subtitleText = new wxStaticText(this, wxID_ANY, "Get started with your coding journey");
    wxFont subtitleFont = m_subtitleText->GetFont();
    subtitleFont.SetPointSize(14);
    m_subtitleText->SetFont(subtitleFont);

    // Links
    m_newFileLink = new wxHyperlinkCtrl(this, wxID_ANY, "Create a new file", wxEmptyString);
    m_openFileLink = new wxHyperlinkCtrl(this, wxID_ANY, "Open a file", wxEmptyString);
    m_openFolderLink = new wxHyperlinkCtrl(this, wxID_ANY, "Open a folder", wxEmptyString);

    // Add items to sizer
    mainSizer->AddSpacer(50);
    mainSizer->Add(m_titleText, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(m_subtitleText, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->AddSpacer(30);
    mainSizer->Add(m_newFileLink, 0, wxALIGN_CENTER | wxALL, 5);
    mainSizer->Add(m_openFileLink, 0, wxALIGN_CENTER | wxALL, 5);
    mainSizer->Add(m_openFolderLink, 0, wxALIGN_CENTER | wxALL, 5);

    // Bind events
    m_newFileLink->Bind(wxEVT_HYPERLINK, &WelcomePage::OnNewFile, this);
    m_openFileLink->Bind(wxEVT_HYPERLINK, &WelcomePage::OnOpenFile, this);
    m_openFolderLink->Bind(wxEVT_HYPERLINK, &WelcomePage::OnOpenFolder, this);

    SetSizer(mainSizer);
    Layout();
}

void WelcomePage::OnNewFile(wxCommandEvent& event)
{
    wxCommandEvent newEvent(wxEVT_MENU, ID_NewFile);
    wxPostEvent(GetParent(), newEvent);
}

void WelcomePage::OnOpenFile(wxCommandEvent& event)
{
    wxCommandEvent newEvent(wxEVT_MENU, ID_OpenFile);
    wxPostEvent(GetParent(), newEvent);
}

void WelcomePage::OnOpenFolder(wxCommandEvent& event)
{
    wxCommandEvent newEvent(wxEVT_MENU, ID_OpenFolder);
    wxPostEvent(GetParent(), newEvent);
}