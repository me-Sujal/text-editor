// Implementation of the file handling functions 

#include "file_utils.h"
#include <wx/file.h>
#include <wx/filename.h>

wxString ReadFileContent(const wxString &filePath)
{
    wxFile file(filePath, wxFile::read);
    if (!file.IsOpened())
    {
        wxLogError("Cannot open file '%s'", filePath);
        return wxEmptyString;
    }

    wxString content;
    if (!file.ReadAll(&content))
    {
        wxLogError("Cannot read file '%s'", filePath);
        return wxEmptyString;
    }

    return content;
}

void WriteFileContent(const wxString &filePath, const wxString &content)
{
    wxFile file(filePath, wxFile::write);
    if (!file.IsOpened())
    {
        wxLogError("Cannot open file '%s' for writing", filePath);
        return;
    }

    if (!file.Write(content))
    {
        wxLogError("Cannot write to file '%s'", filePath);
    }
}

bool FileExists(const wxString &filePath)
{
    return wxFileExists(filePath);
}

wxString GetFileName(const wxString &filePath)
{
    wxFileName fileName(filePath);
    return fileName.GetFullName();
}

wxString GetFileExtension(const wxString &filePath)
{
    wxFileName fileName(filePath);
    return fileName.GetExt();
}