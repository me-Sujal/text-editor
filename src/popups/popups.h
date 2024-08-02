// Creating custom Popup windows as required after defination in popups.h file

#pragma once

#include <wx/wx.h>
#include <wx/popupwin.h>
#include <functional>

class ZoomPopup : public wxPopupWindow
{
public:
    ZoomPopup(wxWindow *parent, wxWindow *button, std::function<void(int)> updateZoomCallback);

    void Popup();
    void Dismiss();

private:
    wxWindow* m_button;
    bool m_shown;
    wxButton *m_zoomOutBtn;
    wxStaticText *m_zoomLabel;
    wxButton *m_zoomInBtn;
    wxButton *m_resetBtn;
    std::function<void(int)> m_updateZoomCallback;
    int m_currentZoom;

    void CreateContent();
    void UpdateZoomLabel();
    void OnZoomIn(wxCommandEvent &event);
    void OnZoomOut(wxCommandEvent &event);
    void OnReset(wxCommandEvent &event);
};


