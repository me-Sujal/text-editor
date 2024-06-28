#include "gui.h"
#include "editor.h"
#include <wx/wx.h>
#include <wx/file.h>
#include <wx/filename.h>

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame(wxEmptyString, wxEmptyString);
    frame->Show();
    return true;
}

MyFrame::MyFrame(const wxString& filepath, const wxString& initialContent)
    : wxFrame(nullptr, wxID_ANY, "Code Lite", wxDefaultPosition, wxSize(800, 500))
{
    CreateMenuBar();
    BindEventHandlers();

    m_Editor = new Editor(this);

    // Set up the main sizer to add other sizer if decalre  append in main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(m_Editor, 1, wxEXPAND);
    SetSizer(mainSizer);

    Centre();

    m_currentFile = filepath;
}

void MyFrame::CreateMenuBar()
{
    wxMenuBar* menuBar = new wxMenuBar();

    // File menu
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(ID_NewFile, "&New File\tCtrl+N");
    fileMenu->Append(ID_NewWindow, "New &Window\tCtrl+Shift+N");
    fileMenu->Append(ID_OpenFile, "&Open File...\tCtrl+O");
    fileMenu->Append(ID_OpenFolder, "Open F&older...\tCtrl+Shift+O");
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_Save, "&Save\tCtrl+S");
    fileMenu->Append(ID_SaveAs, "Save &As...\tCtrl+Shift+S");
    fileMenu->Append(ID_SaveAll, "Save A&ll\tCtrl+Alt+S");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt+F4");
    menuBar->Append(fileMenu, "&File");

    // Edit menu
    wxMenu* editMenu = new wxMenu();
    editMenu->Append(ID_Cut, "Cu&t\tCtrl+X");
    editMenu->Append(ID_Copy, "&Copy\tCtrl+C");
    editMenu->Append(ID_Paste, "&Paste\tCtrl+V");
    editMenu->AppendSeparator();
    editMenu->Append(ID_Wrap, "&Wrap");
    editMenu->Append(wxID_UNDO, "&Undo\tCtrl+Z");
    editMenu->Append(wxID_REDO, "&Redo\tCtrl+Y");
    menuBar->Append(editMenu, "&Edit");

    // Help menu
    wxMenu* helpMenu = new wxMenu();
    helpMenu->Append(ID_Documentation, "&Documentation");
    helpMenu->Append(wxID_ABOUT, "&About");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);
}

void MyFrame::BindEventHandlers()
{
    // All the Event Handlers goes here
    // // File menu
    // Bind(wxEVT_MENU, &MyFrame::OnNewFile, this, ID_NewFile);
    Bind(wxEVT_MENU, &MyFrame::OnNewWindow, this, ID_NewWindow);
    Bind(wxEVT_MENU, &MyFrame::OnOpenFile, this, ID_OpenFile);
    Bind(wxEVT_MENU, &MyFrame::OnUndo, this, wxID_UNDO);
    Bind(wxEVT_MENU, &MyFrame::OnRedo, this, wxID_REDO);
    // Bind(wxEVT_MENU, &MyFrame::OnOpenFolder, this, ID_OpenFolder);
    // Bind(wxEVT_MENU, &MyFrame::OnSave, this, ID_Save);
    // Bind(wxEVT_MENU, &MyFrame::OnSaveAs, this, ID_SaveAs);
    // Bind(wxEVT_MENU, &MyFrame::OnSaveAll, this, ID_SaveAll);
    // Bind(wxEVT_MENU, &MyFrame::OnQuit, this, wxID_EXIT);

    // // Edit menu
    // Bind(wxEVT_MENU, &MyFrame::OnCut, this, ID_Cut);
    // Bind(wxEVT_MENU, &MyFrame::OnCopy, this, ID_Copy);
    // Bind(wxEVT_MENU, &MyFrame::OnPaste, this, ID_Paste);
    // Bind(wxEVT_MENU, &MyFrame::OnWrap, this, ID_Wrap);

    // // Help menu
    // Bind(wxEVT_MENU, &MyFrame::OnDocumentation, this, ID_Documentation);
    // Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
}

void MyFrame::UpdateTitle() {
    wxString title = m_currentFile.IsEmpty() ? "Untitled" : wxFileName(m_currentFile).GetFullName();
    SetTitle(title + " - CodeLite");
}

void MyFrame::OnNewWindow(wxCommandEvent& event) {
    MyFrame* newFrame = new MyFrame(wxEmptyString, wxEmptyString);
    newFrame->Show(true);
}

void MyFrame::OnOpenFile(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, "Open File", "", "", "All Files(*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString filePath = openFileDialog.GetPath();
    wxFile file(filePath);

    if (!file.IsOpened())
    {
        wxMessageBox("Oops! Cannot Open file ' " + filePath + "'.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxString content;
    file.ReadAll(&content);
    file.Close();

    m_Editor->SetText(content);
    m_currentFile = filePath;
    UpdateTitle();
}
void MyFrame::OnUndo(wxCommandEvent& event)
{
    m_Editor->Undo();
}
void MyFrame::OnRedo(wxCommandEvent& event)
{
    m_Editor->Redo();
}
