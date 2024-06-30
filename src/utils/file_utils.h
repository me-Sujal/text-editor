#pragma once

#include <wx/wx.h>
#include <wx/dir.h>
#include<wx/filename.h>

wxString ReadFileContent(const wxString &filePath);

void WriteFileContent(const wxString &filePath, const wxString &content);

bool FileExists(const wxString &filePath);

wxString GetFileName(const wxString &filePath);

wxString GetFileExtension(const wxString &filePath);
