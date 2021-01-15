OS := $(shell uname)
ifeq ($(OS),Darwin)
	CC = clang++ -std=c++11
else
	CC = g++ -std=c++11
endif

TEST_DIR = tests

INSTALL_BIN_DIR = /usr/local/bin/

cx: cx.cpp
	@$(CC) -o cx cx.cpp

install: cx
	@mv ./cx $(INSTALL_BIN_DIR)cx
	@echo "CX installed in $(INSTALL_BIN_DIR)"

test:
	@echo "If 'CX Installed Correctly' prints below, installation was"
	@echo "successful. Otherwise, an error occured."
	@cd tests; cx test1

uninstall:
	rm $(INSTALL_BIN_DIR)cx
	@echo "Uninstalled CX from $(INSTALL_BIN_DIR)"
