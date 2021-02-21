# CX
A simple program that lets you compile and run C++ programs with one command

## Dependencies

CX is pretty simple and doesn't require much. It requires:
* A C++ compiler. clang++ is recommended on macOS, g++ on all other systems.
* make
* git (or download the repository manually via any browser)

## Installation

### macOS and Linux

First, clone or download the GitHub repo:

`git clone git@github.com:Grant-Giesbrecht/CX.git`

change to the directory of the repository

`cd  CX`

Run the makefile, with the target 'install'

`make install`

Now CX is installed on your system. Test your installation with:

`make test`

### Windows

CX is optimized to work on macOS and linux. As such, an installer or windows-
specific makefile is not included. However, you can install CX on a windows
machine if you have a C++ compiler available. The steps to do so are:

1. Compile CX using your compiler of choice. I would recommend Mingw-w64's port
of gcc. Using gcc, you would compile CX as `gcc -o cx cx.cpp`.
2. Place CX somewhere in your system path. Alternatively, you can place it in a
new folder such as a 'bin' folder in your 'C:\Program Files\' and add the new
folder to your PATH environment variable (searching 'environment variable' in 
the start menu will get in to the right window to edit the path).
3. That's it!. Type CX into a command prompt/power shell (will need to open a 
new window after changing the environment variables for them to update) and 
you should see the 'No imput arguments' message. If so, you're good to go!

Note: You will need to explicitly tell CX how to run your program via CX
directives (CXGENRUN and CXCOMPILE). CX will try to run your program using
the UNIX-style commands used by macOS and Linux, hence the need to tell it 
"how to Windows".

## Uninstall

CX is entirely contained in one binary. By default, it is installed in
/usr/local/include/. You can delete CX's binary and thus uninstall it by running
`make uninstall` in the CX source code's folder if it is still present on your
system. Otherwise, run `which cx` to identify where CX is installed on your
system. Then delete the CX binary in the folder indicated by `which`.
