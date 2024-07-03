cmake_minimum_required(VERSION 3.10)
project(CodeEditor)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find wxWidgets
find_package(wxWidgets REQUIRED base core stc aui)
include(${wxWidgets_USE_FILE})

# Add compile definition for STC
add_definitions(-DwxUSE_STC=1)

# Add your source files
set(SOURCE_FILES 
    src/main.cpp
    src/app.cpp
    src/editor/editor.cpp
    src/gui/mainframe.cpp
    src/utils/file_utils.cpp
    # Add other .cpp files if you have any
)

# Create the executablez
add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})

# Link wxWidgets libraries
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
