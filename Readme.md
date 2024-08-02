# 📝 CodeLite Text Editor
A basic text editor created using C++ and wxWidgets with scintilla based editor interface

# 🛠️ Features
📃 Create, Open and Save files of any language
🔍 Quick Search, find and replace keywords
🖌️ Multi-theme support
📂 Directory Display in tree structure
📑 Multi-Tab support
📋 Cut, Paste, Copy support
🖌️ Syntax highlighting for string, numbers and comment for selective languages

# 📋 Requirement 
- C++ compiler 
- wxWidgets library

# 🚀 Building a🖱️nd running
1. Clone the Repo
```Bash
    git clone https://github.com/me-Sujal/text-editor
```

2. Generate MakeFile for compilation
```bash
    cd text-editor
    mkdir build
    cd build
    cmake ..
    make
```
**Make sure to have CMakeLists.txt in the cloned directory**

*In case of error such as*
```bash
    identifier "wxSearchCtrl" is undefined
``` 
use proper include file according to your system in file : src/mainframe.h, line number : 17 and 18 according to the instruction

# 🖱️Usage
1. Launch application
```bash
    cd /path-to-cloned-directory/build/
    ./TextEditor
```
Alternatively the application can be launched by clicking .exe file in the build directory

2. Some Keyboard shortcuts
- Create New file : **ctrl + N**
- Create New Window : **ctrl + shift + N**
- Open Existing file : **ctrl + O**
- Open Folder : **ctrl + shift + O**
- Save file : **Ctrl + S**
- Find : **Ctrl + F**
- Replace : **Ctrl + H**
and so on.....

***Note: Shortcuts for cut, copy, paste, undo, and redo follow standard conventions.***


**To check out Github please go to Documentation option in Help section**