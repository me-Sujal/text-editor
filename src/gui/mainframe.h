#pragma once
#include "../Themes/themes.h"
#include"../Welcome/welcome_page.h"
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/stc/stc.h>
#include <wx/treectrl.h>
#include <wx/aui/auibook.h>
#include "../editor/editor.h"
#include <vector>
#include "../popups/popups.h"
#include <wx/fdrepdlg.h>

#include <wx/srchctrl.h>
#include <wx/gtk/srchctrl.h>


class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &filepath, const wxString &initialContent);
    ~MyFrame();

private:
    bool m_isWrapEnabled = false;
    bool m_isSidePanelShown = false;
    bool m_isSearchEnabled = false;
    bool m_isLexerApplied = false;

    wxMenuItem *m_wrapMenuItem = nullptr;
    void CreateMenuBar();
    void CreateLayout();
    void BindEventHandlers();
    void ToggleSidePanel(wxCommandEvent &event);
    void ToggleSearch(wxCommandEvent &event);

    void OnNewFile(wxCommandEvent &event);
    void OnNewWindow(wxCommandEvent &event);
    void OnOpenFile(wxCommandEvent &event);
    void OnOpenFolder(wxCommandEvent &event);
    void OnCut(wxCommandEvent &event);
    void OnCopy(wxCommandEvent &event);
    void OnPaste(wxCommandEvent &event);
    void OnWrap(wxCommandEvent &event);
    void OnUndo(wxCommandEvent &event);
    void OnRedo(wxCommandEvent &event);

    void onDocumentation(wxCommandEvent &event);

    void CreateFindReplaceDialog();
    void OnFind(wxCommandEvent &event);
    void OnReplace(wxCommandEvent &event);
    void OnFindNext(wxCommandEvent &event);
    void OnFindPrevious(wxCommandEvent &event);
    void OnFindDialogClose(wxFindDialogEvent &event);
    void OnFindDialogFind(wxFindDialogEvent &event);
    void OnFindDialogReplace(wxFindDialogEvent &event);
    void OnFindDialogReplaceAll(wxFindDialogEvent &event);
    void OnReplaceSidePanel(wxCommandEvent &event);

    void OnSearchCtrl(wxCommandEvent &event);

    int m_currentThemeIndex;
    void ApplyTheme(const Theme& theme);
    void OnChangeTheme(wxCommandEvent& event);

    WelcomePage* m_welcomePage;
    void ShowWelcomePage();
    void HideWelcomePage();

    void CreateTab(const wxString &filename = wxEmptyString);
    void onTabClose(wxAuiNotebookEvent &event);
    void UpdateTitle();
    void UpdateTitle(int Count); // overloaded function
    void OnTabChange(wxAuiNotebookEvent &event);

    void PopulateTreeWithDirs(const wxString &path, wxTreeItemId parentId);
    void OnTreeItemActivated(wxTreeEvent &event);
    void onCloseTabCleanup(wxCommandEvent &event);
    void onTimer(wxTimerEvent &event);
    void SetCurrentLanguage();
    wxString ConvertExtension(wxString &fileExtension);

    wxString GetItemPath(wxTreeItemId itemId);

    wxTimer *m_timer;
    wxAuiNotebook *m_notebook;
    wxBoxSizer *m_subSizer;
    std::vector<Editor *> m_editors;
    wxTreeCtrl *m_treeCtrl;
    wxSplitterWindow *m_splitter;
    wxPanel *m_searchPane1;
    Editor *GetCurrentEditor();
    wxString m_rootPath;
    wxString m_currentFile;
    wxStaticText *m_cursorPosition;
    wxStaticText *m_currentLanguage;

    wxButton *m_zoomButton;
    void OnZoomButtonClick(wxCommandEvent &event);
    void UpdateZoom(int zoom);

    ZoomPopup *m_zoomPopup;
    wxFindReplaceDialog *m_findReplaceDialog;
    wxFindReplaceData m_findReplaceData;
    wxSearchCtrl *m_searchCtrl;
    wxTextCtrl *m_replaceCtrl;
};

// Menu item IDs
enum
{
    ID_NewFile = 1,
    ID_NewWindow,
    ID_OpenFile,
    ID_OpenFolder,
    ID_Save,
    ID_SaveAs,
    ID_SaveAll,
    ID_Cut,
    ID_Copy,
    ID_Paste,
    ID_Wrap,
    ID_Documentation,
    ID_About,
    ID_CLOSE_TAB_CLEANUP,
    ID_ToggleButton,
    ID_ShowSearch,
    ID_Find,
    ID_Replace,
    ID_FindNext,
    ID_FindPrevious,
    ID_ThemeDefault,
    ID_ThemeDark,
    ID_ThemeBluishGrey,
    ID_ThemeSolarizedLight,
    ID_ThemeSolarizedDark,
    ID_ThemeMonokai,
    ID_ThemeDracula,
    ID_ThemeGitHubLight,
    ID_ThemeNord
};