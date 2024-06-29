#pragma once

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/stc/stc.h>
#include <wx/treectrl.h>
#include <wx/aui/auibook.h>

class Editor;

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& filepath, const wxString& initialContent);

private:
    void CreateMenuBar();
    void CreateLayout();
    void BindEventHandlers();

    // File menu event handlers
    void OnNewFile(wxCommandEvent& event);
    void OnNewWindow(wxCommandEvent& event);
    void OnOpenFile(wxCommandEvent& event);
    void OnOpenFolder(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnSaveAll(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);

    // Edit menu event handlers
    void OnCut(wxCommandEvent& event);
    void OnCopy(wxCommandEvent& event);
    void OnPaste(wxCommandEvent& event);
    void OnWrap(wxCommandEvent& event);
    void OnSelection(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);

    // Help menu event handlers
    void OnDocumentation(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxAuiNotebook* m_notebook;
    std::vector<Editor*>m_editors;

    void CreateTab(const wxString& filename = wxEmptyString);
    void CloseTab(size_t index);
    void onTabClose(wxAuiNotebookEvent& event);

    // For dynamics title
    void UpdateTitle();

    void PopulateTreeWithDirs(const wxString& path, wxTreeItemId parentId);
    void OnTreeItemActivated(wxTreeEvent& event);
    wxString GetItemPath(wxTreeItemId itemId);

    wxTreeCtrl* m_treeCtrl;
    wxSplitterWindow* m_splitter;

    // Editor Declaration
    Editor* m_Editor;

    wxString m_rootPath;
    wxString m_currentFile;
};

// Menu item IDs
enum
{
    ID_NewFile = 1,
    ID_NewWindow = 2,
    ID_OpenFile = 3,
    ID_OpenFolder = 4,
    ID_Save = 5,
    ID_SaveAs = 6,
    ID_SaveAll = 7,
    ID_Cut = 8,
    ID_Copy = 9,
    ID_Paste = 10,
    ID_Wrap = 11,
    ID_Documentation = 12,
    ID_About = 13
}; 
