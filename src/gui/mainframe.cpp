#include "mainframe.h"
#include "../utils/file_utils.h"
#include <wx/utils.h>
#include <wx/fdrepdlg.h>
#include <wx/srchctrl.h>

//Initialization and setup .........................
MyFrame::MyFrame(const wxString &filepath, const wxString &initialContent)
    : wxFrame(nullptr, wxID_ANY, "Code Lite", wxDefaultPosition, wxSize(800, 500)),
      m_findReplaceDialog(nullptr),
      m_zoomPopup(nullptr)
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
    editMenu->AppendSeparator();
    editMenu->Append(ID_Find, "&Find\tCtrl+F");
    editMenu->Append(ID_Replace, "&Replace\tCtrl+H");
    editMenu->Append(ID_FindNext, "Find &Next\tF3");
    editMenu->Append(ID_FindPrevious, "Find &Previous\tShift+F3");

    // Help menu
    wxMenu *helpMenu = new wxMenu();
    helpMenu->Append(ID_Documentation, "&Documentation");
    helpMenu->Append(wxID_ABOUT, "&About");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);
}

void MyFrame::BindEventHandlers()
{
    // File operations
    Bind(wxEVT_MENU, &MyFrame::OnNewFile, this, ID_NewFile);
    Bind(wxEVT_MENU, &MyFrame::OnNewWindow, this, ID_NewWindow);
    Bind(wxEVT_MENU, &MyFrame::OnOpenFile, this, ID_OpenFile);
    Bind(wxEVT_MENU, &MyFrame::OnOpenFolder, this, ID_OpenFolder);

    // Edit operations
    Bind(wxEVT_MENU, &MyFrame::OnCut, this, ID_Cut);
    Bind(wxEVT_MENU, &MyFrame::OnCopy, this, ID_Copy);
    Bind(wxEVT_MENU, &MyFrame::OnPaste, this, ID_Paste);
    Bind(wxEVT_MENU, &MyFrame::OnUndo, this, wxID_UNDO);
    Bind(wxEVT_MENU, &MyFrame::OnRedo, this, wxID_REDO);
    Bind(wxEVT_MENU, &MyFrame::OnWrap, this, ID_Wrap);

    // Find and Replace operations
    Bind(wxEVT_MENU, &MyFrame::OnFind, this, ID_Find);
    Bind(wxEVT_MENU, &MyFrame::OnReplace, this, ID_Replace);
    Bind(wxEVT_MENU, &MyFrame::OnFindNext, this, ID_FindNext);
    Bind(wxEVT_MENU, &MyFrame::OnFindPrevious, this, ID_FindPrevious);
    Bind(wxEVT_FIND, &MyFrame::OnFindDialogFind, this);
    Bind(wxEVT_FIND_NEXT, &MyFrame::OnFindDialogFind, this);
    Bind(wxEVT_FIND_REPLACE, &MyFrame::OnFindDialogReplace, this);
    Bind(wxEVT_FIND_REPLACE_ALL, &MyFrame::OnFindDialogReplaceAll, this);
    Bind(wxEVT_FIND_CLOSE, &MyFrame::OnFindDialogClose, this);

    // UI and Layout events
    Bind(wxEVT_BUTTON, &MyFrame::ToggleSidePanel, this, ID_ToggleButton);
    Bind(wxEVT_BUTTON, &MyFrame::ToggleSearch, this, ID_ShowSearch);
    Bind(wxEVT_TIMER, &MyFrame::onTimer, this);
    m_treeCtrl->Bind(wxEVT_TREE_ITEM_ACTIVATED, &MyFrame::OnTreeItemActivated, this);
    m_notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &MyFrame::onTabClose, this);
    m_notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &MyFrame::OnTabChange, this);
    Bind(wxEVT_BUTTON, &MyFrame::OnZoomButtonClick, this, m_zoomButton->GetId());

    // Search control events
    m_searchCtrl->Bind(wxEVT_COMMAND_TEXT_ENTER, &MyFrame::OnSearchCtrl, this);
    m_searchCtrl->Bind(wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, &MyFrame::OnSearchCtrl, this);
    Bind(wxEVT_FIND, &MyFrame::OnFindDialogFind, this);
    Bind(wxEVT_FIND_NEXT, &MyFrame::OnFindDialogFind, this);
    Bind(wxEVT_FIND_REPLACE, &MyFrame::OnFindDialogReplace, this);
    Bind(wxEVT_FIND_REPLACE_ALL, &MyFrame::OnFindDialogReplaceAll, this);
}

void MyFrame::CreateLayout()
{
    m_splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);

    m_treeCtrl = new wxTreeCtrl(m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE);

    m_notebook = new wxAuiNotebook(m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxAUI_NB_CLOSE_ON_ALL_TABS | wxAUI_NB_WINDOWLIST_BUTTON | wxAUI_NB_SCROLL_BUTTONS);

    m_searchPane1 = new wxPanel(m_splitter, wxID_ANY);
    m_searchPane1->SetMinSize(wxSize(200, -1));
    m_searchPane1->SetBackgroundColour(wxColour(255, 0, 0));
    wxStaticBoxSizer *searchSizer = new wxStaticBoxSizer(wxVERTICAL, m_searchPane1);

    wxButton *toggleButton = new wxButton(this, ID_ToggleButton, wxT("Toggle Side Panel"));
    wxButton *showSearchButton = new wxButton(this, ID_ShowSearch, wxT("Show search"));
    wxBoxSizer *sidePanel = new wxBoxSizer(wxVERTICAL);

    sidePanel->Add(toggleButton, 0, wxALL, 5);
    sidePanel->Add(showSearchButton, 0, wxALL, 5);

    wxBoxSizer *bottomSizer = new wxBoxSizer(wxHORIZONTAL);
    m_cursorPosition = new wxStaticText(this, wxID_ANY, "Line 0, Column 0");
    bottomSizer->Add(m_cursorPosition, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
    m_zoomButton = new wxButton(this, wxID_ANY, "Zoom: 0", wxDefaultPosition, wxSize(100, -1), wxBU_EXACTFIT);
    bottomSizer->Add(m_zoomButton, 0, wxALIGN_CENTER_VERTICAL, 5);

    m_subSizer = new wxBoxSizer(wxHORIZONTAL);
    m_subSizer->Add(sidePanel, 0, wxEXPAND);
    m_subSizer->Add(m_splitter, 1, wxEXPAND);

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(m_subSizer, 1, wxEXPAND);
    mainSizer->Add(bottomSizer, 0, wxEXPAND);

    SetSizer(mainSizer);


    m_timer = new wxTimer(this, wxID_ANY);
    m_timer->Start(100);

    // NEED TO ADD THIS TO THE SPLITTER AS WELL
    m_searchCtrl = new wxSearchCtrl(m_searchPane1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, -1), wxTE_PROCESS_ENTER);
    m_searchCtrl->ShowSearchButton(true);
    m_searchCtrl->ShowCancelButton(true);
    // sidePanel->Add(m_searchCtrl, 0, wxEXPAND | wxALL, 5);
    searchSizer->Add(m_searchCtrl, 0, wxEXPAND | wxALL, 5);

    wxBoxSizer *replaceSizer = new wxBoxSizer(wxHORIZONTAL);
    m_replaceCtrl = new wxTextCtrl(m_searchPane1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(150, -1));
    wxButton *replaceButton = new wxButton(m_searchPane1, wxID_ANY, "Replace", wxDefaultPosition, wxSize(50, -1));
    replaceSizer->Add(m_replaceCtrl, 1, wxEXPAND | wxRIGHT, 5);
    replaceSizer->Add(replaceButton, 0, wxEXPAND);
    // sidePanel->Add(replaceSizer, 0, wxEXPAND | wxALL, 5);
    searchSizer->Add(replaceSizer, 0, wxEXPAND | wxALL, 5);

    m_searchPane1->SetSizer(searchSizer);
    m_searchPane1->Layout();

    m_splitter->SplitVertically(m_searchPane1, m_notebook);

    m_splitter->SetMinimumPaneSize(100);

    m_splitter->SetSashPosition(200);

    m_splitter->Unsplit(m_searchPane1);

    m_isSidePanelShown = false;

    m_searchCtrl->Bind(wxEVT_COMMAND_TEXT_ENTER, &MyFrame::OnSearchCtrl, this);
    m_searchCtrl->Bind(wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, &MyFrame::OnSearchCtrl, this);
    replaceButton->Bind(wxEVT_BUTTON, &MyFrame::OnReplaceSidePanel, this);
    ////////////////////////////////////////////////////////
}

// File operations
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
    if (m_notebook->GetCurrentPage() == 0)
    {
        CreateTab();
    }
    CreateTab(filePath);
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

/////////////////////////////////////////////////////////

//Tab Management ...................................

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

////////////////////////////////////////////////////////
// UI and Layout Management

void MyFrame ::onTimer(wxTimerEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (currentEditor)
    {
        int pos = currentEditor->GetCurrentPos();
        int lineNum = currentEditor->LineFromPosition(pos);
        int col = currentEditor->GetColumn(pos);

        wxString cursor = wxString::Format("Line %d , Column %d", lineNum + 1, col + 1);
        m_cursorPosition->SetLabel(cursor);
        // SetStatusText(cursor);
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

void MyFrame::OnZoomButtonClick(wxCommandEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (!currentEditor || !m_zoomButton)
        return;

    if (!m_zoomPopup)
    {
        m_zoomPopup = new ZoomPopup(this, m_zoomButton, [this, currentEditor](int zoom)
                                    {
            if (zoom >= -8 && zoom <= 8)
            { 
                currentEditor->SetZoom(zoom*5);
                UpdateZoom(zoom); 
            } });
    }

    if (m_zoomPopup)
    {
        if (m_zoomPopup->IsShown())
        {
            m_zoomPopup->Dismiss();
        }
        else
        {
            m_zoomPopup->Popup();
        }
    }
}

void MyFrame::UpdateZoom(int zoom)
{
    int level = zoom;
    m_zoomButton->SetLabel(wxString::Format("Zoom: %d", level));
}

void MyFrame::ToggleSearch(wxCommandEvent &event){
    if (!m_isSearchEnabled)
    {
        m_splitter->SplitVertically(m_searchPane1, m_notebook);
        m_splitter->SetSashPosition(200);
        m_isSearchEnabled = true;
    }
    else
    {
        m_splitter->Unsplit(m_searchPane1);
        m_isSearchEnabled = false;
    }
}
/////////////////////////////////////////////////////////

// Text Editing Operations

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

//////////////////////////////////////////////////////////////


// Find and Replace Operations...............................

void MyFrame::CreateFindReplaceDialog()
{
    if (!m_findReplaceDialog)
    {
        m_findReplaceDialog = new wxFindReplaceDialog(
            this,
            &m_findReplaceData,
            "Find and Replace",
            wxFR_REPLACEDIALOG);
    }
    m_findReplaceDialog->Show(true);
}

void MyFrame::OnFind(wxCommandEvent &event)
{
    CreateFindReplaceDialog();
}

void MyFrame::OnReplace(wxCommandEvent &event)
{
    CreateFindReplaceDialog();
}

void MyFrame::OnFindNext(wxCommandEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (currentEditor)
    {
        wxString findString = m_findReplaceData.GetFindString();
        if (!findString.IsEmpty())
        {
            int flags = 0;
            if (m_findReplaceData.GetFlags() & wxFR_MATCHCASE)
                flags |= wxSTC_FIND_MATCHCASE;

            int currentPos = currentEditor->GetCurrentPos();
            int length = currentEditor->GetLength();
            int found = currentEditor->FindText(currentPos, length, findString, flags);

            if (found != wxNOT_FOUND)
            {
                currentEditor->SetSelection(found, found + findString.Length());
                currentEditor->EnsureCaretVisible();
            }
        }
    }
}

void MyFrame::OnFindPrevious(wxCommandEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (currentEditor)
    {
        wxString findString = m_findReplaceData.GetFindString();
        if (!findString.IsEmpty())
        {
            int flags = 0;
            if (m_findReplaceData.GetFlags() & wxFR_MATCHCASE)
                flags |= wxSTC_FIND_MATCHCASE;

            int currentPos = currentEditor->GetCurrentPos();
            int found = currentEditor->FindText(currentPos, 0, findString, flags);

            if (found != wxNOT_FOUND)
            {
                currentEditor->SetSelection(found, found + findString.Length());
                currentEditor->EnsureCaretVisible();
            }
        }
    }
}


void MyFrame::OnFindDialogFind(wxFindDialogEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (!currentEditor)
        return;

    wxString findString = event.GetFindString();
    int flags = 0;
    if (event.GetFlags() & wxFR_WHOLEWORD)
        flags |= wxSTC_FIND_WHOLEWORD;
    if (event.GetFlags() & wxFR_MATCHCASE)
        flags |= wxSTC_FIND_MATCHCASE;
    wxLogDebug("Search flags: %d", flags);

    int startPos = (event.GetEventType() == wxEVT_FIND) ? 0 : currentEditor->GetCurrentPos();
    int length = currentEditor->GetLength();
    int found = currentEditor->FindText(startPos, length, findString, flags);

    if (found != wxNOT_FOUND)
    {
        currentEditor->SetSelection(found, found + findString.Length());
        currentEditor->EnsureCaretVisible();
    }
    else
    {
        wxMessageBox("Text not found", "Find", wxOK | wxICON_INFORMATION);
    }
}

void MyFrame::OnFindDialogReplace(wxFindDialogEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (!currentEditor)
        return;

    wxString findString = event.GetFindString();
    wxString replaceString = event.GetReplaceString();
    int flags = 0;
    if (event.GetFlags() & wxFR_WHOLEWORD)
        flags |= wxSTC_FIND_WHOLEWORD;
    if (event.GetFlags() & wxFR_MATCHCASE)
        flags |= wxSTC_FIND_MATCHCASE;
    wxLogDebug("Search flags: %d", flags);
    // Check if the current selection matches the find string
    wxString selectedText = currentEditor->GetSelectedText();
    if (selectedText.IsSameAs(findString, (flags & wxSTC_FIND_MATCHCASE) == 0))
    {
        // Replace the current selection
        currentEditor->ReplaceSelection(replaceString);
    }

    // Find the next occurrence
    int currentPos = currentEditor->GetCurrentPos();
    int length = currentEditor->GetLength();
    int found = currentEditor->FindText(currentPos, length, findString, flags);

    if (found != wxNOT_FOUND)
    {
        currentEditor->SetSelection(found, found + findString.Length());
        currentEditor->EnsureCaretVisible();
    }
    else
    {
        wxMessageBox("No more occurrences found", "Replace", wxOK | wxICON_INFORMATION);
    }
}

void MyFrame::OnFindDialogReplaceAll(wxFindDialogEvent &event)
{
    Editor *currentEditor = GetCurrentEditor();
    if (currentEditor)
    {
        wxString findString = event.GetFindString();
        wxString replaceString = event.GetReplaceString();
        int flags = 0;
        if (event.GetFlags() & wxFR_WHOLEWORD)
            flags |= wxSTC_FIND_WHOLEWORD;
        if (event.GetFlags() & wxFR_MATCHCASE)
            flags |= wxSTC_FIND_MATCHCASE;
        wxLogDebug("Search flags: %d", flags);

        int count = 0;
        int found = 0;
        do
        {
            found = currentEditor->FindText(found, currentEditor->GetLength(), findString, flags);
            if (found != wxNOT_FOUND)
            {
                currentEditor->SetTargetStart(found);
                currentEditor->SetTargetEnd(found + findString.Length());
                currentEditor->ReplaceTarget(replaceString);
                found += replaceString.Length();
                count++;
            }
        } while (found != wxNOT_FOUND);

        wxMessageBox(wxString::Format("Replaced %d occurrences", count), "Replace All");
    }
}

void MyFrame::OnFindDialogClose(wxFindDialogEvent &event)
{
    m_findReplaceDialog->Destroy();
    m_findReplaceDialog = nullptr;
}

void MyFrame::OnSearchCtrl(wxCommandEvent &event)
{
    wxString searchString = m_searchCtrl->GetValue();
    if (!searchString.IsEmpty())
    {
        Editor *currentEditor = GetCurrentEditor();
        if (currentEditor)
        {
            int flags = 0;
            int currentPos = currentEditor->GetCurrentPos() - 1;
            int length = currentEditor->GetLength();
            int found = currentEditor->FindText(currentPos, length, searchString, flags);

            if (found != wxNOT_FOUND)
            {
                currentEditor->SetSelection(found, found + searchString.Length());
                currentEditor->EnsureCaretVisible();
            }
            else
            {
                // If not found from current position, search from the beginning
                found = currentEditor->FindText(0, length, searchString, flags);
                if (found != wxNOT_FOUND)
                {
                    currentEditor->SetSelection(found, found + searchString.Length());
                    currentEditor->EnsureCaretVisible();
                }
                else
                {
                    wxMessageBox("Text not found", "Search Result", wxOK | wxICON_INFORMATION);
                }
            }
        }
    }
}

void MyFrame::OnReplaceSidePanel(wxCommandEvent &event)
{
    wxString searchString = m_searchCtrl->GetValue();
    wxString replaceString = m_replaceCtrl->GetValue();
    if (!searchString.IsEmpty())
    {
        Editor *currentEditor = GetCurrentEditor();
        if (currentEditor)
        {
            int flags = 0;
            int currentPos = currentEditor->GetCurrentPos();
            int length = currentEditor->GetLength();
            int found = currentEditor->FindText(0, length, searchString, flags);

            if (found != wxNOT_FOUND)
            {
                // Replace the current occurrence
                currentEditor->SetTargetStart(found);
                currentEditor->SetTargetEnd(found + searchString.Length());
                currentEditor->ReplaceTarget(replaceString);

                // Move to the end of the replaced text
                currentEditor->GotoPos(found + replaceString.Length());

                // Search for the next occurrence
                int nextFound = currentEditor->FindText(found + replaceString.Length(), length, searchString, flags);

                if (nextFound != wxNOT_FOUND)
                {
                    // Select the next occurrence
                    currentEditor->SetSelection(nextFound, nextFound + searchString.Length());
                }

                currentEditor->EnsureCaretVisible();
            }
            else
            {
                wxMessageBox("Text not found", "Replace Result", wxOK | wxICON_INFORMATION);
            }
        }
    }
}

////////////////////////////////////////////////////////////////

// Utility Functions...........................................

Editor *MyFrame::GetCurrentEditor()
{
    int currentPage = m_notebook->GetSelection();
    if (currentPage != wxNOT_FOUND && currentPage < m_editors.size())
    {
        return m_editors[currentPage];
    }

    return nullptr;
}

////////////////////////////////////////////////////////////////

// Destructor..................................................
MyFrame::~MyFrame()
{
    for (Editor *editor : m_editors)
    {
        delete editor;
    }
    m_editors.clear();

    if (m_zoomPopup)
    {
        m_zoomPopup->Destroy();
        m_zoomPopup = nullptr;
    }
}


