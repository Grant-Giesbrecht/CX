# CX
A simple program that lets you compile and run C++ programs with one command

## Dependencies

CX is pretty simple and doesn't require much. It requires:
* A C++ compiler. clang++ is recommended on macOS, g++ on all other systems.
* make
* git (or download the repository manually via any browser)

## Installation

First, clone or download the GitHub repo:

`git clone git@github.com:Grant-Giesbrecht/CX.git`

change to the directory of the repository

`cd  CX`

Run the makefile, with the target 'install'

`make install`

Now CX is installed on your system. Test your installation with:

`make test`

## Uninstall

CX is entirely contained in one binary. By default, it is installed in
/usr/local/include/. You can delete CX's binary and thus uninstall it by running
`make uninstall` in the CX source code's folder if it is still present on your
system. Otherwise, run `which cx` to identify where CX is installed on your
system. Then delete the CX binary in the folder indicated by `which`.
