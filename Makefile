debug ?= 0
NAME := labcurl
SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin

src_files := $(wildcard $(SRC_DIR)/*.c)

main:
	gcc -Wall -Wno-unused-result -std=gnu99 -Og -g -lcurl $(src_files) -o bin/$(NAME)
	./bin/$(NAME)

clean:
	rm -rf bin/
	mkdir bin

