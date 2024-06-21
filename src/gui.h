#pragma once

#include <wx/wx.h>

class Editor; // Forward declaration

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void CreateMenuBar();
    void BindEventHandlers();

    // File menu event handlers
    void OnNewFile(wxCommandEvent &event);
    void OnNewWindow(wxCommandEvent &event);
    void OnOpenFile(wxCommandEvent &event);
    void OnOpenFolder(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnSaveAs(wxCommandEvent &event);
    void OnSaveAll(wxCommandEvent &event);
    void OnQuit(wxCommandEvent &event);

    // Edit menu event handlers
    void OnCut(wxCommandEvent &event);
    void OnCopy(wxCommandEvent &event);
    void OnPaste(wxCommandEvent &event);
    void OnWrap(wxCommandEvent &event);
    void OnSelection(wxCommandEvent &event);

    // Help menu event handlers
    void OnDocumentation(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

    Editor *m_Editor;
};

// Menu item IDs
enum
{
    ID_NewFile = wxID_HIGHEST + 1,
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
    ID_About
};