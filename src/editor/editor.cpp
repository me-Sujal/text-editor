
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
    // These will be overwritten by the theme, but set defaults just in case
    wxColour defaultBackground = wxColour(255, 255, 255);
    wxColour defaultForeground = wxColour(0, 0, 0);
    wxColour defaultLineNumBg = wxColour(255, 255, 255);
    wxColour defaultLineNumFg = wxColour(0, 0, 0);

    StyleSetForeground(wxSTC_STYLE_DEFAULT, defaultForeground);
    StyleSetBackground(wxSTC_STYLE_DEFAULT, defaultBackground);
    StyleSetForeground(wxSTC_STYLE_LINENUMBER, defaultLineNumFg);
    StyleSetBackground(wxSTC_STYLE_LINENUMBER, defaultLineNumBg);

    SetCaretForeground(defaultForeground);

    // Increase line number margin width and add a separator
    SetMarginWidth(0, 50);
    SetMarginType(1, wxSTC_MARGIN_FORE);
    SetMarginWidth(1, 1);
    StyleSetForeground(1, wxColour(200, 200, 200));

    StyleClearAll();
}
int Editor::FindText(int start, int end, const wxString &text, int flags)
{
    return wxStyledTextCtrl::FindText(start, end, text, flags);
}

void Editor::ReplaceSelection(const wxString &text)
{
    wxStyledTextCtrl::ReplaceSelection(text);
}

void Editor::SetTargetStart(int pos)
{
    wxStyledTextCtrl::SetTargetStart(pos);
}

void Editor::SetTargetEnd(int pos)
{
    wxStyledTextCtrl::SetTargetEnd(pos);
}

void Editor::ReplaceTarget(const wxString &text)
{
    wxStyledTextCtrl::ReplaceTarget(text);
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