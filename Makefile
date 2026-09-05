.PHONY: all build clean

SRC_DIR := src
BUILD_DIR := build
TARGET := $(BUILD_DIR)/6502_sim

CXX ?= g++
CXXFLAGS ?= -O2 -Wall -Wextra -std=c++26
LDFLAGS ?=
LDLIBS ?=

export CXX CPPFLAGS CXXFLAGS LDFLAGS LDLIBS

all: build

build:
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C $(SRC_DIR) BUILD_DIR=../$(BUILD_DIR) TARGET=../$(TARGET)

clean:
	$(MAKE) -C $(SRC_DIR) clean BUILD_DIR=../$(BUILD_DIR) TARGET=../$(TARGET)
	rm -rf $(BUILD_DIR)