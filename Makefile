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

.PHONY: build clean run lint

all: build clean

build:
	mkdir -p build
	cd build && cmake .. && make
	mkdir -p ./bin
	cp ${BUILD_SOURCE_DIR}/${BIN_NAME} ${BINARY}

clean:
	rm -rf ${BUILD_DIR}

lint:
	@$(call style_calls, "Running clang-format")
	@clang-format -n -Werror -style=file -i src/*.cpp

run:
	@./${BINARY}
