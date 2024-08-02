// Creation of application frame

#include "app.h"
#include "gui/mainframe.h"

bool MyApp::OnInit()
{
    GuiFrame *frame = new GuiFrame(wxEmptyString, wxEmptyString);
    frame->Show(true);
    return true;
}