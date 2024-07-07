#include "mainframe.h"
#include "../utils/file_utils.h"
#include <wx/utils.h>

MyFrame::MyFrame(const wxString &filepath, const wxString &initialContent)
    : wxFrame(nullptr, wxID_ANY, "Code Lite", wxDefaultPosition, wxSize(800, 500))
{
    CreateLayout();
    CreateMenuBar();
    BindEventHandlers();

    if (!filepath.IsEmpty())
    {
        CreateTab(filepath);
    }
    else
    {
        CreateTab();
    }

    Centre();
    m_currentFile = filepath;
}

void MyFrame::CreateMenuBar()
{
    wxMenuBar *menuBar = new wxMenuBar();

    // File menu
    wxMenu *fileMenu = new wxMenu();
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
    wxMenu *editMenu = new wxMenu();
    editMenu->Append(ID_Cut, "Cu&t\tCtrl+X");
    editMenu->Append(ID_Copy, "&Copy\tCtrl+C");
    editMenu->Append(ID_Paste, "&Paste\tCtrl+V");
    editMenu->AppendSeparator();
    m_wrapMenuItem = editMenu->AppendCheckItem(ID_Wrap, "&Wrap\tAlt+Z");
    editMenu->Append(wxID_UNDO, "&Undo\tCtrl+Z");
    editMenu->Append(wxID_REDO, "&Redo\tCtrl+Y");
    menuBar->Append(editMenu, "&Edit");

    // Help menu
    wxMenu *helpMenu = new wxMenu();
    helpMenu->Append(ID_Documentation, "&Documentation");
    helpMenu->Append(wxID_ABOUT, "&About");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);
}

void MyFrame::BindEventHandlers()
{

    // All the Event Handlers goes here
    // // File menu
    Bind(wxEVT_MENU, &MyFrame::OnNewFile, this, ID_NewFile);
    Bind(wxEVT_MENU, &MyFrame::OnNewWindow, this, ID_NewWindow);
    Bind(wxEVT_MENU, &MyFrame::OnOpenFile, this, ID_OpenFile);
    Bind(wxEVT_MENU, &MyFrame::OnOpenFolder, this, ID_OpenFolder);
  
    Bind(wxEVT_MENU, &MyFrame::OnUndo, this, wxID_UNDO);
    Bind(wxEVT_MENU, &MyFrame::OnRedo, this, wxID_REDO);
    // Bind(wxEVT_MENU, &MyFrame::OnSave, this, ID_Save);
    // Bind(wxEVT_MENU, &MyFrame::OnSaveAs, this, ID_SaveAs);
    // Bind(wxEVT_MENU, &MyFrame::OnSaveAll, this, ID_SaveAll);
    // Bind(wxEVT_MENU, &MyFrame::OnQuit, this, wxID_EXIT);

    // // Edit menu
    Bind(wxEVT_MENU, &MyFrame::OnCut, this, ID_Cut);
    Bind(wxEVT_MENU, &MyFrame::OnCopy, this, ID_Copy);
    Bind(wxEVT_MENU, &MyFrame::OnPaste, this, ID_Paste);
    Bind(wxEVT_MENU, &MyFrame::OnWrap, this, ID_Wrap);

    Bind(wxEVT_MENU, &MyFrame::OnWrap, this, ID_Wrap);
    Bind(wxEVT_BUTTON, &MyFrame::ToggleSidePanel, this, ID_ToggleButton);
    Bind(wxEVT_TIMER, &MyFrame::onTimer, this);

    // // Help menu
    // Bind(wxEVT_MENU, &MyFrame::OnDocumentation, this, ID_Documentation);
    // Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);

    m_treeCtrl->Bind(wxEVT_TREE_ITEM_ACTIVATED, &MyFrame::OnTreeItemActivated, this);

    m_notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &MyFrame::onTabClose, this);
    m_notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &MyFrame::OnTabChange, this);
}

void MyFrame::CreateLayout()
{
    m_splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);

    m_treeCtrl = new wxTreeCtrl(m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );

    // m_Editor = new Editor(m_splitter);
    m_notebook = new wxAuiNotebook(m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxAUI_NB_CLOSE_ON_ALL_TABS | wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_SCROLL_BUTTONS);

    m_splitter->SplitVertically(m_treeCtrl, m_notebook);
    m_splitter->SetMinimumPaneSize(100);
    m_splitter->SetSashPosition(200);
    m_splitter->Unsplit(m_treeCtrl);
    m_isSidePanelShown = false;

    wxButton *toggleButton = new wxButton(this, ID_ToggleButton, wxT("Toggle Side Panel"));

    wxBoxSizer *sidePanel = new wxBoxSizer(wxVERTICAL);
    sidePanel->Add(toggleButton, 0, wxCENTER, 10);

    // m_cursorPosition = new wxStaticText(this, wxID_ANY, "Line 0, Column 0");
    // sidePanel->Add(m_cursorPosition, 1, wxCENTER, 10);

    CreateStatusBar(2);

    wxBoxSizer *cursorPosition = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(sidePanel, 0, 10, wxALL);
    mainSizer->Add(m_splitter, 1, wxEXPAND);
    SetSizer(mainSizer);

    // CreateStatusBar(2);

    m_timer = new wxTimer(this, wxID_ANY);
    m_timer->Start(100);
}

void MyFrame ::onTimer(wxTimerEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (currentEditor)
    {
        int pos = currentEditor->GetCurrentPos();
        int lineNum = currentEditor->LineFromPosition(pos);
        int col = currentEditor->GetColumn(pos);

        wxString cursor = wxString::Format("Line %d , Column %d", lineNum + 1, col + 1);
        // m_cursorPosition->SetLabel(cursor);
        SetStatusText(cursor);
    }
}

void MyFrame::ToggleSidePanel(wxCommandEvent &event)
{
    if (m_isSidePanelShown)
    {
        m_splitter->Unsplit(m_treeCtrl);
        m_isSidePanelShown = false;
    }
    else
    {
        m_splitter->SplitVertically(m_treeCtrl, m_notebook);
        m_splitter->SetSashPosition(200);
        m_isSidePanelShown = true;
    }
}

void MyFrame::CreateTab(const wxString &filename)
{
    wxString title = filename.IsEmpty() ? "Untitled" : GetFileName(filename);
    Editor *newEditor = new Editor(m_notebook);
    newEditor->SetWrapMode(m_isWrapEnabled ? wxSTC_WRAP_WORD : wxSTC_WRAP_NONE);
    m_editors.push_back(newEditor);
    m_notebook->AddPage(newEditor, title, true);

    if (!filename.IsEmpty())
    {
        wxString content = ReadFileContent(filename);
        if (!content.IsEmpty())
        {
            newEditor->SetText(content);
        }
    }
    UpdateTitle();
}

void MyFrame::onTabClose(wxAuiNotebookEvent &event)
{
    int index = event.GetSelection();

    wxQueueEvent(this, new wxCommandEvent(wxEVT_COMMAND_MENU_SELECTED, ID_CLOSE_TAB_CLEANUP));
    int tabCount = m_notebook->GetPageCount();

    UpdateTitle(tabCount - 1); // - 1 because while updating the count it stays at 1 for some reason even if last of tab has been closed
    event.Skip();
}

void MyFrame::onCloseTabCleanup(wxCommandEvent &event)
{

    int index = m_notebook->GetSelection();
    if (index != wxNOT_FOUND && index < m_editors.size())
    {
        delete m_editors[index];
        m_editors.erase(m_editors.begin() + index);
    }

    if (m_notebook->GetPageCount() == 0)
    {
        CreateTab();
    }
}

void MyFrame::OnTabChange(wxAuiNotebookEvent &event)
{
    UpdateTitle();
    event.Skip();
}

void MyFrame::OnOpenFolder(wxCommandEvent &event)
{
    wxDirDialog dlg(nullptr, "Choose Directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dlg.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    m_rootPath = dlg.GetPath();
    m_treeCtrl->DeleteAllItems();
    wxTreeItemId rootId = m_treeCtrl->AddRoot(m_rootPath);
    PopulateTreeWithDirs(m_rootPath, rootId);
    m_treeCtrl->Expand(rootId);
}

void MyFrame::PopulateTreeWithDirs(const wxString &path, wxTreeItemId parentId)
{
    wxDir dir(path);
    if (!dir.IsOpened())
    {
        return;
    }

    wxString filename;
    bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES | wxDIR_DIRS);

    while (cont)
    {
        wxString fullPath = wxFileName(path, filename).GetFullPath();
        wxTreeItemId newItem = m_treeCtrl->AppendItem(parentId, filename);

        if (wxDir::Exists(fullPath))
        {
            PopulateTreeWithDirs(fullPath, newItem);
        }

        cont = dir.GetNext(&filename);
    }
    m_splitter->SplitVertically(m_treeCtrl, m_notebook);
    m_splitter->SetSashPosition(200);
    m_isSidePanelShown = true;
}

void MyFrame::OnTreeItemActivated(wxTreeEvent &event)
{
    wxTreeItemId itemId = event.GetItem();
    wxString path = GetItemPath(itemId);

    if (wxFile::Exists(path))
    {
        CreateTab(path);
        UpdateTitle();
    }
    else if (wxDir::Exists(path))
    {
        if (m_treeCtrl->IsExpanded(itemId))
        {
            m_treeCtrl->Collapse(itemId);
        }
        else
        {
            m_treeCtrl->Expand(itemId);
        }
    }
}

wxString MyFrame::GetItemPath(wxTreeItemId itemId)
{
    wxString path = m_treeCtrl->GetItemText(itemId);
    wxTreeItemId parent = m_treeCtrl->GetItemParent(itemId);
    while (parent.IsOk() && parent != m_treeCtrl->GetRootItem())
    {
        path = m_treeCtrl->GetItemText(parent) + wxFileName::GetPathSeparator() + path;
        parent = m_treeCtrl->GetItemParent(parent);
    }

    return wxFileName(m_rootPath, path).GetFullPath();
}

void MyFrame::UpdateTitle()
{
    int currentPage = m_notebook->GetSelection();
    if (currentPage != wxNOT_FOUND)
    {
        wxString title = m_notebook->GetPageText(currentPage);
        SetTitle(title + " - CodeLite ");
    }
    else
    {
        SetTitle("Code Editor");
    }
}

void MyFrame::UpdateTitle(int count)
{
    if (count == 0)
    {
        SetTitle("CodeLite");
    }
}

void MyFrame::OnNewFile(wxCommandEvent &event)
{
    CreateTab();
}

void MyFrame::OnNewWindow(wxCommandEvent &event)
{
    MyFrame *newFrame = new MyFrame(wxEmptyString, wxEmptyString);
    newFrame->Show(true);
}

void MyFrame::OnOpenFile(wxCommandEvent &event)
{
    wxFileDialog openFileDialog(this, "Open File", "", "", "All Files(*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString filePath = openFileDialog.GetPath();

    CreateTab(filePath);
}

Editor *MyFrame::GetCurrentEditor()
{
    int currentPage = m_notebook->GetSelection();
    if (currentPage != wxNOT_FOUND && currentPage < m_editors.size())
    {
        return m_editors[currentPage];
    }

    return nullptr;
}

void MyFrame::OnCut(wxCommandEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (currentEditor)
    {
        currentEditor->Cut();
    }
}

void MyFrame::OnCopy(wxCommandEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (currentEditor)
    {
        currentEditor->Copy();
    }
}

void MyFrame::OnPaste(wxCommandEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (currentEditor)
    {
        currentEditor->Paste();
    }
}

void MyFrame::OnWrap(wxCommandEvent &event)
{
    if ((m_notebook->GetPageCount() - 1) != 0) // check if all tabs are closed or not
    {
        m_isWrapEnabled = !m_isWrapEnabled;
        m_wrapMenuItem->Check(m_isWrapEnabled);

        Editor *currentEditor = GetCurrentEditor();
        if (currentEditor)
        {
            currentEditor->SetWrapMode(m_isWrapEnabled ? wxSTC_WRAP_WORD : wxSTC_WRAP_NONE);
        }

        // Apply wrap setting to all open editors
        for (Editor *editor : m_editors)
        {
            editor->SetWrapMode(m_isWrapEnabled ? wxSTC_WRAP_WORD : wxSTC_WRAP_NONE);
        }
    }
}

void MyFrame::OnUndo(wxCommandEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (currentEditor)
    {
        currentEditor->Undo();
    }
}

void MyFrame::OnRedo(wxCommandEvent &event)
{

    Editor *currentEditor = GetCurrentEditor();
    if (currentEditor)
    {
        currentEditor->Redo();
    }
}

MyFrame::~MyFrame()
{
    for (Editor *editor : m_editors)
    {
        delete editor;
    }
    m_editors.clear();
}
