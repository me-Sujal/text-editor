//hi 
#include <wx/wx.h>
#include <wx/stc/stc.h>
#include "editor.h"

Editor::Editor(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
    : wxStyledTextCtrl(parent, id, pos, size, style)
{
    SetupEditor();
    SetupStyles(); // All the styling for editor goes here
}

void Editor::SetupEditor()
{
    SetViewWhiteSpace(false);
    SetIndentationGuides(true);
    SetIndent(4);
    SetTabWidth(4);
    SetUseTabs(false);
    SetViewEOL(false);
    SetWrapMode(wxSTC_WRAP_WORD);

   

   // for line numbers
    SetMarginType(0, wxSTC_MARGIN_NUMBER);
    SetMarginWidth(0, 25);
 

  
}

void Editor::SetupStyles(){

    // style for entire editor
    StyleSetBackground(wxSTC_STYLE_DEFAULT, wxColour(14, 20, 25)); // style for the editor background
    StyleSetForeground(wxSTC_STYLE_DEFAULT, wxColour(62, 78, 110)); // style for the editor text

    StyleSetForeground(wxSTC_STYLE_LINENUMBER, wxColour(180, 180, 180)); // style for line number 
    StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour(62, 78, 110));
    
    // To make sure style is refreshed and also without this the background color of text is not as same as editor
    StyleClearAll();
    Refresh();
    Update();
}
