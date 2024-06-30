#include "app.h"
#include "gui/mainframe.h"

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame(wxEmptyString, wxEmptyString);
    frame->Show(true);
    return true;
}