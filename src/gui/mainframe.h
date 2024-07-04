#pragma once

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/stc/stc.h>
#include <wx/treectrl.h>
#include <wx/aui/auibook.h>
#include "../editor/editor.h"
#include <vector>

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

    void CreateTab(const wxString &filename = wxEmptyString);
    void onTabClose(wxAuiNotebookEvent &event);
    void UpdateTitle();
    void UpdateTitle(int Count);//overloaded function
    void OnTabChange(wxAuiNotebookEvent &event);

    void PopulateTreeWithDirs(const wxString &path, wxTreeItemId parentId);
    void OnTreeItemActivated(wxTreeEvent &event);
    void onCloseTabCleanup(wxCommandEvent &event);
    wxString GetItemPath(wxTreeItemId itemId);

    wxAuiNotebook *m_notebook;
    std::vector<Editor *> m_editors;
    wxTreeCtrl *m_treeCtrl;
    wxSplitterWindow *m_splitter;
    Editor *GetCurrentEditor();
    wxString m_rootPath;
    wxString m_currentFile;
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
    ID_ToggleButton
};