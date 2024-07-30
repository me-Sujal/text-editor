// popups.cpp
#include "popups.h"
ZoomPopup::ZoomPopup(wxWindow *parent, wxWindow *button, std::function<void(int)> updateZoomCallback)
    : wxPopupWindow(parent), m_updateZoomCallback(updateZoomCallback), m_currentZoom(0), m_button(button), m_shown(false)
{
    CreateContent();
}
void ZoomPopup::CreateContent()
{
    wxPanel *panel = new wxPanel(this);
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    m_zoomOutBtn = new wxButton(panel, wxID_ANY, "-", wxDefaultPosition, wxSize(30, 30), wxBORDER_NONE);
    m_zoomLabel = new wxStaticText(panel, wxID_ANY, "0", wxDefaultPosition, wxSize(30, 30), wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
    m_zoomInBtn = new wxButton(panel, wxID_ANY, "+", wxDefaultPosition, wxSize(30, 30), wxBORDER_NONE);
    m_resetBtn = new wxButton(panel, wxID_ANY, "Reset", wxDefaultPosition, wxSize(50, 30), wxBORDER_NONE);

    sizer->Add(m_zoomOutBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer->Add(m_zoomLabel, 0, wxALIGN_CENTER | wxALL, 5);
    sizer->Add(m_zoomInBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    sizer->Add(m_resetBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    panel->SetSizer(sizer);
    sizer->Fit(panel);
    SetClientSize(panel->GetSize());

    // Position the popup above the button
    // wxPoint pos = button->GetScreenPosition();
    // pos.y -= GetSize().GetHeight();
    // SetPosition(pos);

    // Bind events
    m_zoomInBtn->Bind(wxEVT_BUTTON, &ZoomPopup::OnZoomIn, this);
    m_zoomOutBtn->Bind(wxEVT_BUTTON, &ZoomPopup::OnZoomOut, this);
    m_resetBtn->Bind(wxEVT_BUTTON, &ZoomPopup::OnReset, this);
}

void ZoomPopup::UpdateZoomLabel()
{
    m_zoomLabel->SetLabel(wxString::Format("%d", m_currentZoom));
    m_updateZoomCallback(m_currentZoom);
}

void ZoomPopup::OnZoomIn(wxCommandEvent &event)
{
    m_currentZoom > 8 ? m_currentZoom++ : 8 ;
    UpdateZoomLabel();
}

void ZoomPopup::OnZoomOut(wxCommandEvent &event)
{
    m_currentZoom < -2 ? m_currentZoom-- : -2 ;
    UpdateZoomLabel();
}

void ZoomPopup::OnReset(wxCommandEvent &event)
{
    m_currentZoom = 0;
    UpdateZoomLabel();
}

void ZoomPopup::Popup()
{
    if (!m_shown)
    {
        wxPoint pos = m_button->GetScreenPosition();
        pos.y -= GetSize().GetHeight();
        SetPosition(pos);
        Show(true);
        m_shown = true;
    }
}

void ZoomPopup::Dismiss()
{
    if (m_shown)
    {
        Show(false);
        m_shown = false;
    }
}
