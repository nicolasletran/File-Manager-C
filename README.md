
# CLI File Manager in C

A simple **Command-Line Interface (CLI) File Manager** written in C.  
It allows users to list files, create/delete files and directories, copy/move files, search for files, and navigate the file system using commands similar to Unix shell.

---

## Features

### Core Features
- **List files and directories**: `ls`  
  - Optionally shows detailed info: `ls -l`
- **Create / Delete files**: `touch filename`, `rm filename`
- **Create / Delete directories**: `mkdir dirname`, `rmdir dirname`
- **Copy / Move files**: `cp src dest`, `mv src dest`
- **Search files recursively**: `find name_pattern`
- **Navigation**: `cd dirname`, `pwd`

### Optional / Bonus Features
- Color-coded directories
- File permissions and last modified time display (`ls -l`)

---

## Usage

Compile the project using the provided Makefile:

```bash
make
```
Run the file manager:
```bash
./filemanager   # Linux / MinGW
filemanager.exe # Windows
```
Example session:
```bash
cfm> mkdir test
cfm> cd test
cfm> pwd
C:/Users/YourName/Desktop/File-Manager-C/test
cfm> touch example.txt
cfm> ls
       example.txt
cfm> cd ..
cfm> rm test/example.txt
cfm> rmdir test
cfm> exit
```
Project Structure:
File-Manager-C/
├── main.c         # Main CLI loop & command parsing
├── file_ops.c     # File & directory operations
├── file_ops.h
├── utils.c        # Helper functions (e.g., input parsing)
├── utils.h
├── Makefile
└── README.md

Build & Clean:
```bash
# Build
make

# Clean compiled files
make clean
```

