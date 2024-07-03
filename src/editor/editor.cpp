//fucking hell
#include "editor.h"

Editor::Editor(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
    : wxStyledTextCtrl(parent, id, pos, size, style)
{
    SetupEditor();
    SetupStyles();
}

void Editor::SetupEditor()
{
    SetViewWhiteSpace(false);
    SetIndentationGuides(true);
    SetIndent(8);
    SetTabWidth(8);
    SetUseTabs(false);
    SetViewEOL(false);
    SetWrapMode(wxSTC_WRAP_WORD);

    // for line numbers
    SetMarginType(0, wxSTC_MARGIN_NUMBER);
    SetMarginWidth(0, 50);
    SetUndoCollection(true);
    EmptyUndoBuffer();
}

void Editor::SetupStyles()
{
    // style for entire editor
    StyleSetForeground(wxSTC_STYLE_DEFAULT, wxColour(200, 200, 200)); // style for the editor background
    StyleSetBackground(wxSTC_STYLE_DEFAULT, wxColour(30, 30, 30));       // style for the editor text
    SetCaretForeground(wxColour(255, 255, 255));
    StyleSetForeground(wxSTC_STYLE_LINENUMBER, wxColour(75, 75, 75)); // style for line number
    StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour(35, 35, 35));

    // To make sure style is refreshed and also without this the background color of text is not as same as editor
    StyleClearAll();
    Refresh();
    Update();

    // wxStyledTextCtrl *editor = new wxStyledTextCtrl(this, wxID_ANY);
    // editor->StyleSetForeground(wxSTC_STYLE_DEFAULT, wxColour(200, 200, 200));
    // editor->StyleSetBackground(wxSTC_STYLE_DEFAULT, wxColour(30, 30, 30));
    // editor->StyleClearAll();
    // editor->SetCaretForeground(wxColour(255, 255, 255));
    // editor->SetMarginWidth(0, 50);
    // editor->StyleSetForeground(wxSTC_STYLE_LINENUMBER, wxColour(75, 75, 75));
    // editor->StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour(35, 35, 35));

    // Refresh();
    // Update();
}

void Editor::Undo()
{
    if (CanUndo())
    {
        wxStyledTextCtrl::Undo();
    }
}

void Editor::Redo()
{
    if (CanRedo())
    {
        wxStyledTextCtrl::Redo();
    }
}