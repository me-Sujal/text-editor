#pragma once

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/stc/stc.h>
#include <wx/treectrl.h>
#include <wx/aui/auibook.h>
#include "../editor/editor.h"
#include <vector>
#include <wx/fdrepdlg.h>
#include <wx/srchctrl.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &filepath, const wxString &initialContent);
    ~MyFrame();

private:
    bool m_isWrapEnabled = false;
    bool m_isSidePanelShown = true;
    wxMenuItem *m_wrapMenuItem = nullptr;
    void CreateMenuBar();
    void CreateLayout();
    void BindEventHandlers();
    void ToggleSidePanel(wxCommandEvent &event);

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

    void CreateTab(const wxString &filename = wxEmptyString);
    void onTabClose(wxAuiNotebookEvent &event);
    void UpdateTitle();
    void UpdateTitle(int Count);//overloaded function
    void OnTabChange(wxAuiNotebookEvent &event);

    void PopulateTreeWithDirs(const wxString &path, wxTreeItemId parentId);
    void OnTreeItemActivated(wxTreeEvent &event);
    void onCloseTabCleanup(wxCommandEvent &event);
    void onTimer(wxTimerEvent &event);
    wxString GetItemPath(wxTreeItemId itemId);

    wxTimer *m_timer;
    wxAuiNotebook *m_notebook;
    std::vector<Editor *> m_editors;
    wxTreeCtrl *m_treeCtrl;
    wxSplitterWindow *m_splitter;
    Editor *GetCurrentEditor();
    wxString m_rootPath;
    wxString m_currentFile;
    wxStaticText *m_cursorPosition;

    wxFindReplaceDialog *m_findReplaceDialog;
    wxFindReplaceData m_findReplaceData;
    wxSearchCtrl *m_searchCtrl;
    wxTextCtrl* m_replaceCtrl;
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
    ID_Find,
    ID_Replace,
    ID_FindNext,
    ID_FindPrevious
};