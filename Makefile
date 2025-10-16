debug ?= 0
NAME := labcurl
SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin

src_files := $(wildcard $(SRC_DIR)/*.c)
str_files := $(wildcard $(SRC_DIR)/string/*.c)

main:
	gcc -Wall -pedantic -Wno-unused-result -std=gnu99 -Og -g -lcurl -fsanitize=address $(src_files) $(str_files) -o bin/$(NAME)

rough:
	gcc -Wall -pedantic -Wno-unused-result -std=gnu99 -Og -g -lcurl $(src_files) $(str_files) -o bin/$(NAME)

clean:
	rm -rf bin/
	mkdir bin

