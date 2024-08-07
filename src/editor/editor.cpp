// Creation of editor as well as implementation of the editor related functions

#include "editor.h"
#include <wx/wx.h>
#include <wx/stc/stc.h>

Editor::Editor(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
    : wxStyledTextCtrl(parent, id, pos, size, style)
{
    SetupEditor();
    SetupStyles();
    SetupBracketCompletion();
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
    SetMarginWidth(0, 150);
    SetUndoCollection(true);
    EmptyUndoBuffer();

    // for code foldings

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

    // StyleClearAll();
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

void Editor::Cut()
{
    wxStyledTextCtrl::Cut();
}

void Editor::Copy()
{
    wxStyledTextCtrl::Copy();
}

void Editor::Paste()
{
    wxStyledTextCtrl::Paste();
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

void Editor::SetupPythonSyntaxHighlighting()
{
    SetLexer(wxSTC_LEX_PYTHON);

    SetKeyWords(0, "and as assert break class continue def del elif else except "
        "finally for from global if import in is lambda nonlocal not "
        "or pass raise return try while with yield");

    // Define colors that work well with both light and dark themes
    wxColour keywordColor(0, 0, 255);       // Blue
    wxColour commentColor(0, 128, 0);       // Green
    wxColour stringColor(163, 21, 21);      // Dark Red
    wxColour numberColor(128, 0, 128);      // Purple
    wxColour operatorColor(64, 64, 64);     // Dark Gray
    wxColour identifierColor(0, 0, 0);      // Black (will be adjusted for dark themes)

    // Set styles
    StyleSetForeground(wxSTC_P_DEFAULT, identifierColor);
    StyleSetForeground(wxSTC_P_COMMENTLINE, commentColor);
    StyleSetForeground(wxSTC_P_NUMBER, numberColor);
    StyleSetForeground(wxSTC_P_STRING, stringColor);
    StyleSetForeground(wxSTC_P_CHARACTER, stringColor);
    StyleSetForeground(wxSTC_P_WORD, keywordColor);
    StyleSetBold(wxSTC_P_WORD, true);
    StyleSetForeground(wxSTC_P_TRIPLE, stringColor);
    StyleSetForeground(wxSTC_P_TRIPLEDOUBLE, stringColor);
    StyleSetForeground(wxSTC_P_CLASSNAME, wxColour(0, 0, 128));  // Dark Blue
    StyleSetForeground(wxSTC_P_DEFNAME, wxColour(128, 0, 0));    // Dark Red
    StyleSetBold(wxSTC_P_DEFNAME, true);
    StyleSetForeground(wxSTC_P_OPERATOR, operatorColor);
    StyleSetForeground(wxSTC_P_IDENTIFIER, identifierColor);

    // Additional styles
    StyleSetForeground(wxSTC_P_COMMENTBLOCK, commentColor);
    StyleSetForeground(wxSTC_P_DECORATOR, wxColour(255, 128, 0)); // Orange

    Colourise(0, -1);
    Refresh();
}

void Editor::SetupCppSyntaxHighlighting()
{
    // Set lexer to C++
    SetLexer(wxSTC_LEX_CPP);

    // Set C++ keywords
    SetKeyWords(0, "auto break case char const continue default do double else enum extern "
                   "float for goto if int long register return short signed sizeof static "
                   "struct switch typedef union unsigned void volatile while class namespace "
                   "try catch throw new delete using");

    // Define colors for syntax elements
    const wxColor keywordColor(0, 0, 255);       // Blue
    const wxColor stringColor(163, 21, 21);      // Red
    const wxColor commentColor(0, 128, 0);       // Green
    const wxColor preprocessorColor(128, 64, 0); // Brown

    // Set styles
    StyleSetForeground(wxSTC_C_DEFAULT, *wxBLACK);
    StyleSetForeground(wxSTC_C_COMMENT, commentColor);
    StyleSetForeground(wxSTC_C_COMMENTLINE, commentColor);
    StyleSetForeground(wxSTC_C_NUMBER, *wxBLUE);
    StyleSetForeground(wxSTC_C_STRING, stringColor);
    StyleSetForeground(wxSTC_C_CHARACTER, stringColor);
    StyleSetForeground(wxSTC_C_WORD, keywordColor);
    StyleSetBold(wxSTC_C_WORD, true);
    StyleSetForeground(wxSTC_C_PREPROCESSOR, preprocessorColor);
    StyleSetForeground(wxSTC_C_OPERATOR, *wxBLACK);
    StyleSetForeground(wxSTC_C_IDENTIFIER, *wxBLACK);

    Colourise(0, -1);
    Refresh();
    Update();
}

void Editor::SetupCssSyntaxHighlighting()
{
    SetLexer(wxSTC_LEX_CSS);

    SetKeyWords(0, "color background-color font-size font-family margin padding border");

    const wxColor propertyColor(0, 0, 255);
    const wxColor valueColor(163, 21, 21);
    const wxColor selectorColor(0, 128, 0);

    StyleSetForeground(wxSTC_CSS_DEFAULT, *wxBLACK);
    StyleSetForeground(wxSTC_CSS_TAG, selectorColor);
    StyleSetForeground(wxSTC_CSS_CLASS, selectorColor);
    StyleSetForeground(wxSTC_CSS_PSEUDOCLASS, selectorColor);
    StyleSetForeground(wxSTC_CSS_UNKNOWN_PSEUDOCLASS, selectorColor);
    StyleSetForeground(wxSTC_CSS_ATTRIBUTE, propertyColor);
    StyleSetForeground(wxSTC_CSS_VALUE, valueColor);
    StyleSetForeground(wxSTC_CSS_COMMENT, wxColor(128, 128, 128));

    Colourise(0, -1);
    Refresh();
    Update();
}

void Editor::SetupHtmlSyntaxHighlighting()
{
    SetLexer(wxSTC_LEX_HTML);

    SetKeyWords(0, "a abbr address area article aside audio b base bdi bdo blockquote body br "
                   "button canvas caption cite code col colgroup data datalist dd del details "
                   "dfn dialog div dl dt em embed fieldset figcaption figure footer form h1 h2 "
                   "h3 h4 h5 h6 head header hr html i iframe img input ins kbd label legend li "
                   "link main map mark meta meter nav noscript object ol optgroup option output "
                   "p param picture pre progress q rp rt ruby s samp script section select small "
                   "source span strong style sub summary sup table tbody td template textarea "
                   "tfoot th thead time title tr track u ul var video wbr");

    const wxColor tagColor(0, 0, 255);
    const wxColor attributeColor(128, 0, 128);
    const wxColor stringColor(163, 21, 21);

    StyleSetForeground(wxSTC_H_DEFAULT, *wxBLACK);
    StyleSetForeground(wxSTC_H_TAG, tagColor);
    StyleSetForeground(wxSTC_H_TAGUNKNOWN, tagColor);
    StyleSetForeground(wxSTC_H_ATTRIBUTE, attributeColor);
    StyleSetForeground(wxSTC_H_ATTRIBUTEUNKNOWN, attributeColor);
    StyleSetForeground(wxSTC_H_NUMBER, *wxBLUE);
    StyleSetForeground(wxSTC_H_DOUBLESTRING, stringColor);
    StyleSetForeground(wxSTC_H_SINGLESTRING, stringColor);
    StyleSetForeground(wxSTC_H_COMMENT, wxColor(0, 128, 0));

    Colourise(0, -1);
    Refresh();
    Update();
}

void Editor::ApplySyntaxHighlighting(const wxString &fileType)
{
    if (fileType == "py")
    {
        SetupPythonSyntaxHighlighting();
    }
    else if (fileType == "cpp" || fileType == "c" | fileType == "h")
    {
        SetupCppSyntaxHighlighting();
    }
    else if (fileType == "css")
    {
        SetupCssSyntaxHighlighting();
    }
    else if (fileType == "html")
    {
        SetupHtmlSyntaxHighlighting();
    }
    // Add more file types as needed
}

void Editor::SetupBracketCompletion(){
    Bind(wxEVT_STC_CHARADDED, &Editor::OnCharAdded, this);
}

void Editor::OnCharAdded(wxStyledTextEvent &event)
{
    char ch = event.GetKey();
    int currentPos = GetCurrentPos();

    switch (ch)
    {
    case '(':
        InsertText(currentPos, ")");
        SetSelection(currentPos, currentPos);
        break;
    case '[':
        InsertText(currentPos, "]");
        SetSelection(currentPos, currentPos);
        break;
    case '{':
        InsertText(currentPos, "}");
        SetSelection(currentPos, currentPos);
        break;
    case '"':
        // Only add closing quote if there isn't already one
        if (GetCharAt(currentPos) != '"')
        {
            InsertText(currentPos, "\"");
            SetSelection(currentPos, currentPos);
        }
        break;
    case '\'':
        // Only add closing quote if there isn't already one
        if (GetCharAt(currentPos) != '\'')
        {
            InsertText(currentPos, "'");
            SetSelection(currentPos, currentPos);
        }
        break;
    }

    event.Skip();
}