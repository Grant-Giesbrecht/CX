CC = clang++
CC_LINUX = g++

TEST_DIR = tests

INSTALL_BIN_DIR = /usr/local/bin/

cx: cx.cpp
	@$(CC) -o cx cx.cpp

cx_linux: cx.cpp
	@$(CC_LINUX) -o cx cx.cpp

install: cx
	@mv ./cx $(INSTALL_BIN_DIR)cx
	@echo "CX installed in $(INSTALL_BIN_DIR)"

install_linux: cx_linux
	@mv ./cx $(INSTALL_BIN_DIR)cx
	@echo "CX installed in $(INSTALL_BIN_DIR)"

test: install
	@echo "Test not yet implimented"

uninstall:
	rm $(INSTALL_BIN_DIR)cx
	@echo "Uninstalled CX from $(INSTALL_BIN_DIR)"
