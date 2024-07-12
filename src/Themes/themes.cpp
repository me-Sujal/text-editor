#include "themes.h"

std::vector<Theme> availableThemes = {
    {
        "Default",
        wxColour(255, 255, 255),  // White background
        wxColour(0, 0, 0),        // Black text
        wxColour(240, 240, 240),  // Light grey for line numbers
        wxColour(100, 100, 100),  // Dark grey for line number text
        wxColour(173, 214, 255),  // Light blue selection
        wxColour(0, 0, 0),        // Black text for selection
        wxColour(0, 0, 0)         // Black caret
    },
    {
        "Dark",
        wxColour(30, 30, 30),     // Dark background
        wxColour(220, 220, 220),  // Light grey text
        wxColour(45, 45, 45),     // Slightly lighter for line numbers background
        wxColour(150, 150, 150),  // Much lighter grey for line number text
        wxColour(60, 60, 60),     // Dark grey selection
        wxColour(220, 220, 220),  // Light grey text for selection
        wxColour(255, 255, 255)   // White caret
    },
    {
         "Bluish Grey",
        wxColour(50, 55, 65),     // Bluish-grey background
        wxColour(220, 220, 220),  // Light grey text
        wxColour(40, 45, 55),     // Slightly darker for line numbers background
        wxColour(180, 180, 180),  // Much lighter grey for line number text
        wxColour(70, 75, 85),     // Slightly lighter selection
        wxColour(240, 240, 240),  // Very light grey text for selection
        wxColour(255, 255, 255)   // White caret
    }
    // Add more themes as needed
};