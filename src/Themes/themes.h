#pragma once
#include <wx/colour.h>
#include <string>
#include <vector>

struct Theme {
    std::string name;
    wxColour background;
    wxColour foreground;
    wxColour selectionBackground;
    wxColour selectionForeground;
    wxColour lineNumberBackground;
    wxColour lineNumberForeground;
    wxColour caretForeground;
};

extern std::vector<Theme> availableThemes;

