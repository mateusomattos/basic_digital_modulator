# Platform detection
ifeq ($(OS),Windows_NT)
  # Windows
  ifeq ($(shell uname -s),)
    CLEANUP = del /F /Q
    MKDIR = cmd /C "if not exist \"$1\" mkdir \"$1\""
    TARGET_EXTENSION=.exe
    RM_DIR = rmdir /S /Q
    EXE_PREFIX=
  else # Bash-like shell on Windows (e.g., Git Bash, MinGW, Cygwin)
    CLEANUP = rm -f
    MKDIR = mkdir -p
    TARGET_EXTENSION=.exe
    RM_DIR = rm -rf
    EXE_PREFIX=./
  endif
else
  # Linux, macOS, etc.
  CLEANUP = rm -f
  MKDIR = mkdir -p
  TARGET_EXTENSION=
  RM_DIR = rm -rf
  EXE_PREFIX=./
endif

# Compiler and Linker
CC = gcc
LINK = gcc

# Directories
DIR_SRC = src
DIR_TEST = test
DIR_UNITY_SRC = unity/src
DIR_INCLUDE = include

DIR_BIN = bin
DIR_OBJ = obj
DIR_OBJ_MAIN = $(DIR_OBJ)/main
DIR_OBJ_TEST = $(DIR_OBJ)/test
DIR_TEST_RESULTS = test_results

# Main Program
TARGET_MAIN_NAME = simulator
TARGET_MAIN = $(DIR_BIN)/$(TARGET_MAIN_NAME)$(TARGET_EXTENSION)

SRCS_MAIN := $(wildcard $(DIR_SRC)/*.c)
HDRS := $(wildcard $(DIR_INCLUDE)/*.h) $(wildcard $(DIR_SRC)/*.h)
OBJS_MAIN := $(patsubst $(DIR_SRC)/%.c,$(DIR_OBJ_MAIN)/%.o,$(SRCS_MAIN))

# Unity Framework
SRC_UNITY := $(DIR_UNITY_SRC)/unity.c
HDR_UNITY := $(DIR_UNITY_SRC)/unity.h
OBJ_UNITY_FOR_TEST := $(DIR_OBJ_TEST)/unity.o

# Test Sources and Executables
SRCS_TEST_FILES := $(wildcard $(DIR_TEST)/Test*.c)
TEST_EXECS := $(patsubst $(DIR_TEST)/Test%.c,$(DIR_BIN)/Test%$(TARGET_EXTENSION),$(SRCS_TEST_FILES))
TEST_RESULTS_FILES := $(patsubst $(DIR_BIN)/Test%$(TARGET_EXTENSION),$(DIR_TEST_RESULTS)/Test%.txt,$(TEST_EXECS))

# Compiler Flags
CFLAGS_COMMON = -W -Wall -g
LDFLAGS_COMMON =
LDFLAGS := $(LDFLAGS_COMMON) -lm
LDFLAGS_TEST := $(LDFLAGS_COMMON) -lm
CFLAGS_MAIN = $(CFLAGS_COMMON) -I$(DIR_INCLUDE)
CFLAGS_TEST = $(CFLAGS_COMMON) -I$(DIR_INCLUDE) -I$(DIR_UNITY_SRC) -I$(DIR_SRC) -DTEST

BUILD_DIRS = $(DIR_BIN) $(DIR_OBJ_MAIN) $(DIR_OBJ_TEST) $(DIR_TEST_RESULTS)

# Default target: Build the main program
.PHONY: all
all: $(TARGET_MAIN)

$(TARGET_MAIN): $(OBJS_MAIN) | $(DIR_BIN)
	@echo "Linking main program: $@"
	$(LINK) $(OBJS_MAIN) -o $@ $(LDFLAGS)


$(DIR_OBJ_MAIN)/%.o: $(DIR_SRC)/%.c $(HDRS) | $(DIR_OBJ_MAIN)
	@echo "Compiling for main: $< -> $@"
	$(CC) $(CFLAGS_MAIN) -c $< -o $@

.PHONY: test test-build test-run summarize-tests

test: $(BUILD_DIRS) summarize-tests

test-build: $(TEST_EXECS)

test-run: $(TEST_RESULTS_FILES)

# Summarize test results
summarize-tests: test-run
	@echo "-------------------------------------------------------"
	@echo "UNITY TEST SUMMARY"
	@echo "-------------------------------------------------------"
	@echo "Gathering results from $(DIR_TEST_RESULTS)..."
	@echo ""
	@echo "----------------------- IGNORES -----------------------"
	@grep -sh "^.*IGNORE" $(DIR_TEST_RESULTS)/*.txt || echo "No ignores found."
	@echo "----------------------- FAILURES ----------------------"
	@grep -sh "^.*FAIL" $(DIR_TEST_RESULTS)/*.txt || echo "No failures found."
	@echo "------------------------ PASSED -----------------------"
	@grep -sh "^.*PASS" $(DIR_TEST_RESULTS)/*.txt || echo "No tests passed or no pass messages found."
	@echo "-------------------------------------------------------"
	@if grep -sq "^.*FAIL" $(DIR_TEST_RESULTS)/*.txt; then \
		echo "ERROR: Some tests FAILED!"; \
		exit 1; \
	else \
		echo "SUCCESS: All tests passed (or were ignored and no failures)."; \
	fi


$(DIR_TEST_RESULTS)/Test%.txt: $(DIR_BIN)/Test%$(TARGET_EXTENSION) | $(DIR_TEST_RESULTS)
	@echo "Running test: $< -> $@"
	-$(EXE_PREFIX)$< > $@ 2>&1


$(DIR_BIN)/Test%$(TARGET_EXTENSION): $(DIR_OBJ_TEST)/Test%.o $(DIR_OBJ_TEST)/src_%.o $(OBJ_UNITY_FOR_TEST)  $(DIR_OBJ_TEST)/src_utils.o  $(DIR_OBJ_TEST)/src_output.o $(DIR_OBJ_TEST)/src_config.o $(DIR_OBJ_TEST)/src_modulation.o $(DIR_OBJ_TEST)/src_boxmuller.o | $(DIR_BIN)
	@echo "Linking test executable: $@"
	$(LINK) $^ -o $@ $(LDFLAGS_TEST)


$(DIR_OBJ_TEST)/Test%.o: $(DIR_TEST)/Test%.c $(HDRS) $(HDR_UNITY) | $(DIR_OBJ_TEST)
	@echo "Compiling for test: $< -> $@"
	$(CC) $(CFLAGS_TEST) -c $< -o $@


$(DIR_OBJ_TEST)/src_%.o: $(DIR_SRC)/%.c $(HDRS) | $(DIR_OBJ_TEST)
	@echo "Compiling for test (from src): $< -> $@"
	$(CC) $(CFLAGS_TEST) -c $< -o $@


$(OBJ_UNITY_FOR_TEST): $(SRC_UNITY) $(HDR_UNITY) | $(DIR_OBJ_TEST)
	@echo "Compiling Unity framework: $< -> $@"
	$(CC) $(CFLAGS_TEST) -c $< -o $@


$(BUILD_DIRS):
	@echo "Ensuring directory exists: $@"
	$(MKDIR) $(@)


.PHONY: clean
clean:
	@echo "Cleaning up project..."
	-$(CLEANUP) $(TARGET_MAIN)
	-$(CLEANUP) $(DIR_OBJ_MAIN)/*.o
	-$(CLEANUP) $(DIR_OBJ_TEST)/*.o
	-$(CLEANUP) $(DIR_OBJ_TEST)/src_*.o # Cleanup src objects compiled for test
	-$(CLEANUP) $(DIR_BIN)/Test*$(TARGET_EXTENSION)
	-$(CLEANUP) $(DIR_TEST_RESULTS)/*.txt
	@echo "Removing directories..."
	-$(RM_DIR) $(DIR_OBJ_MAIN) >nul 2>&1 || true
	-$(RM_DIR) $(DIR_OBJ_TEST) >nul 2>&1 || true
	-$(RM_DIR) $(DIR_OBJ) >nul 2>&1 || true
	-$(RM_DIR) $(DIR_TEST_RESULTS) >nul 2>&1 || true
	-$(RM_DIR) $(DIR_BIN) >nul 2>&1 || true # This removes the main target and test executables' directory
	@echo "Cleanup complete."
