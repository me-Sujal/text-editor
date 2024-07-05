
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

    //for code foldings

    SetLexer(wxSTC_LEX_PYTHON);

    SetProperty("fold", "1");
    SetProperty("fold.comment", "1");
    SetProperty("fold.compact", "1");
    SetProperty("fold.python.string.literals", "1");

    SetMarginType(2, wxSTC_MARGIN_SYMBOL);
    SetMarginWidth(2, 16);
    SetMarginMask(2, wxSTC_MASK_FOLDERS);
    SetMarginSensitive(2, true);

    MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN, wxSTC_MARK_MINUS);
    MarkerDefine(wxSTC_MARKNUM_FOLDER, wxSTC_MARK_PLUS);
    MarkerDefine(wxSTC_MARKNUM_FOLDERSUB, wxSTC_MARK_VLINE);
    MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL, wxSTC_MARK_LCORNER);
    MarkerDefine(wxSTC_MARKNUM_FOLDEREND, wxSTC_MARK_BOXPLUSCONNECTED);
    MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_BOXMINUSCONNECTED);
    MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_TCORNER);

    MarkerSetForeground(wxSTC_MARKNUM_FOLDER, wxColor(0, 0, 0));
    MarkerSetBackground(wxSTC_MARKNUM_FOLDER, wxColor(255, 255, 255));

    SetFoldFlags(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED | wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);

    SetAutomaticFold(wxSTC_AUTOMATICFOLD_SHOW | wxSTC_AUTOMATICFOLD_CLICK | wxSTC_AUTOMATICFOLD_CHANGE);
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


}
// void Editor::Cut()
// {
//     wxStyledTextCtrl::Cut();
// }

// void Editor::Copy()
// {
//     wxStyledTextCtrl::Copy();
// }

// void Editor::Paste()
// {
//     wxStyledTextCtrl::Paste();
// }

// void Editor::Undo()
// {
//     if (CanUndo())
//     {
//         wxStyledTextCtrl::Undo();
//     }
// }

// void Editor::Redo()
// {
//     if (CanRedo())
//     {
//         wxStyledTextCtrl::Redo();
//     }
// }