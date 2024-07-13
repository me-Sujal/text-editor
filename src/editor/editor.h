#pragma once

#include <wx/stc/stc.h>

class Editor : public wxStyledTextCtrl
{
public:
    Editor(wxWindow *parent, wxWindowID id = wxID_ANY,
           const wxPoint &pos = wxDefaultPosition,
           const wxSize &size = wxDefaultSize,
           long style = 0);
    int FindText(int start, int end, const wxString& text, int flags);
    void ReplaceSelection(const wxString& text);
    void SetTargetStart(int pos);
    void SetTargetEnd(int pos);
    void ReplaceTarget(const wxString& text);
    void Cut();
    void Copy();
    void Paste();
    void Undo();
    void Redo();

private:
    void SetupEditor();
    void SetupStyles();
};