# Compiler and flags
CC = gcc
CFLAGS = -lm

# Target executables
TARGETS = convertTo6bit compress expand convertToASCII

# Output directory
OUT_DIR = out

# Default target: build all executables
all: $(TARGETS)

# Build each executable with its dependencies and place it in the output directory
$(OUT_DIR)/%: %.c usefulTools.c
	mkdir -p $(OUT_DIR)  # Create the output directory if it doesn't exist
	$(CC) $(CFLAGS) -o $@ $^

# Targets for running the executables (note the paths to executables in the out directory)
run_convertTo6bit: $(OUT_DIR)/convertTo6bit
	$(OUT_DIR)/convertTo6bit -d

run_compress: $(OUT_DIR)/convertTo6bit $(OUT_DIR)/compress
	$(OUT_DIR)/convertTo6bit | $(OUT_DIR)/compress -d

run_expand: $(OUT_DIR)/convertTo6bit $(OUT_DIR)/compress $(OUT_DIR)/expand
	$(OUT_DIR)/convertTo6bit | $(OUT_DIR)/compress | $(OUT_DIR)/expand -d

run_all: $(OUT_DIR)/convertTo6bit $(OUT_DIR)/compress $(OUT_DIR)/expand $(OUT_DIR)/convertToASCII
	$(OUT_DIR)/convertTo6bit | $(OUT_DIR)/compress | $(OUT_DIR)/expand | $(OUT_DIR)/convertToASCII -d

# Clean up target (removes executables from the output directory)
clean:
	rm -f $(OUT_DIR)/*
