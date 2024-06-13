GREEN="\033[00;32m"
RESTORE="\033[0m"

SRC_DIR=src
INCLUDE_DIR=include
LIB_DIR=lib
BUILD_DIR=build
BUILD_SOURCE_DIR=${BUILD_DIR}/${SRC_DIR}
BIN_DIR=bin
BIN_NAME=Chess
BINARY=${BIN_DIR}/${BIN_NAME}

# make the output of the message appear green
define style_calls
	$(eval $@_msg = $(1))
	printf ${GREEN}${$@_msg}${RESTORE}
	echo
endef

default_target: all

all: build clean

build:
	@$(call style_calls, "Building project")
	mkdir -p build
	cd build && cmake .. && make
	cmake -S . -G "Unix Makefiles" -B "cmake"
	@$(call style_calls, "Copying binary to ${BINARY}")
	mkdir -p ./bin
	cp ${BUILD_SOURCE_DIR}/${BIN_NAME} ${BINARY}
	@$(call style_calls, "Done")
.PHONY: build

clean:
	@$(call style_calls, "Cleaning ${BUILD_DIR}")
	rm -rf ${BUILD_DIR}
	@$(call style_calls, "Done")
.PHONY: clean

lint:
	@$(call style_calls, "Running clang-format")
	@clang-format -n -Werror -style=file -i src/*.cpp
	@$(call style_calls, "Done")
.PHONY: lint

run:
	@$(call style_calls, "Running ${BINARY}")
	@./${BINARY}
	@$(call style_calls, "Done")
.PHONY: run

help:
	@echo "Usage: make [target]"
	@echo "Targets:"
	@echo "         all:     build the projecti and clean the build directory"
	@echo "         build:   build the project"
	@echo "         clean:   clean the build directory"
	@echo "         lint:    run clang-format"
	@echo "         run:     run the project"
	@echo "         help:    show this help"
.PHONY: help
