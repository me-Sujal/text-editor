#pragma once

#include <wx/stc/stc.h>

class Editor : public wxStyledTextCtrl
{
public:
    Editor(wxWindow *parent, wxWindowID id = wxID_ANY,
           const wxPoint &pos = wxDefaultPosition,
           const wxSize &size = wxDefaultSize,
           long style = 0);

private:
    void SetupEditor();
    void SetupStyles();
};