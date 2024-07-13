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
    },
     {
        "Solarized Light",
        wxColour(253, 246, 227),  // Light beige background
        wxColour(101, 123, 131),  // Dark greyish-blue text
        wxColour(238, 232, 213),  // Light tan for line numbers background
        wxColour(147, 161, 161),  // Grey-blue for line number text
        wxColour(238, 232, 213),  // Light tan selection
        wxColour(101, 123, 131),  // Dark greyish-blue text for selection
        wxColour(181, 137, 0)     // Dark yellow caret
    },
    {
        "Solarized Dark",
        wxColour(0, 43, 54),      // Dark blue-green background
        wxColour(131, 148, 150),  // Light grey-blue text
        wxColour(7, 54, 66),      // Slightly lighter background for line numbers
        wxColour(101, 123, 131),  // Greyish-blue for line number text
        wxColour(7, 54, 66),      // Slightly lighter selection
        wxColour(131, 148, 150),  // Light grey-blue text for selection
        wxColour(181, 137, 0)     // Dark yellow caret
    },
    {
        "Monokai",
        wxColour(39, 40, 34),     // Dark greyish background
        wxColour(248, 248, 242),  // Off-white text
        wxColour(49, 50, 44),     // Slightly lighter for line numbers background
        wxColour(117, 113, 94),   // Brownish-grey for line number text
        wxColour(73, 72, 62),     // Dark grey selection
        wxColour(248, 248, 242),  // Off-white text for selection
        wxColour(249, 38, 114)    // Bright pink caret
    },
    {
        "Dracula",
        wxColour(40, 42, 54),     // Dark purplish background
        wxColour(248, 248, 242),  // Off-white text
        wxColour(30, 31, 41),     // Slightly darker for line numbers background
        wxColour(98, 114, 164),   // Light purple for line number text
        wxColour(68, 71, 90),     // Lighter purplish selection
        wxColour(248, 248, 242),  // Off-white text for selection
        wxColour(80, 250, 123)    // Bright green caret
    },
    {
        "GitHub Light",
        wxColour(255, 255, 255),  // White background
        wxColour(36, 41, 46),     // Dark grey text
        wxColour(245, 245, 245),  // Light grey for line numbers background
        wxColour(106, 115, 125),  // Medium grey for line number text
        wxColour(200, 225, 255),  // Light blue selection
        wxColour(36, 41, 46),     // Dark grey text for selection
        wxColour(0, 0, 0)         // Black caret
    },
    {
        "Nord",
        wxColour(46, 52, 64),     // Dark blue-grey background
        wxColour(216, 222, 233),  // Light greyish-blue text
        wxColour(59, 66, 82),     // Slightly lighter for line numbers background
        wxColour(136, 192, 208),  // Light blue for line number text
        wxColour(67, 76, 94),     // Slightly lighter selection
        wxColour(216, 222, 233),  // Light greyish-blue text for selection
        wxColour(236, 239, 244)   // Very light grey caret
    }
    // Add more themes as needed
};