.PHONY: all clear run memleak copy_over

.DEFAULT_GOAL := all

SRC_FILES := $(shell find src -name *.c)

C_FLAGS := -std=c99 -Wall -Werror

bin/main: $(SRC_FILES) ; $(CC) -g $(C_FLAGS) $^ -o $@

copy_over: ; cp assets/* bin/

### default build target ###
all: bin/main copy_over

### runs the executable through valgrind (has to be installed) ###
memleak: ; @if [ -e ./bin/main ]; then cd ./bin && valgrind --leak-check=yes ./main; else echo "No build ready"; fi

### runs the executable ###
run: ; @if [ -e ./bin/main ]; then cd ./bin && ./main; else echo "No build ready"; fi

### clears build files ###
clear: ; @rm -r bin/* obj/* 2>/dev/null ; echo "Directory cleared"
