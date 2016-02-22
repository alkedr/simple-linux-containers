BUILD_DIR := build
HEADERS := hmlc.h
SOURCES := hmlc.c
TEST_HEADERS := test_framework.h
TEST_SOURCES := $(wildcard test_*.c)
TEST_EXECUTABLES := $(addprefix $(BUILD_DIR)/,$(patsubst %.c,%,$(TEST_SOURCES)))

test: $(BUILD_DIR) compile-tests run-tests

$(BUILD_DIR):
	mkdir -p $@

compile-tests: $(TEST_EXECUTABLES)

run-tests: $(addprefix run-,$(TEST_EXECUTABLES))

run-$(BUILD_DIR)/test_%: $(BUILD_DIR)/test_%
	@echo "RUN $<"
	@rm -Rf $(BUILD_DIR)/test_dir && ./$< | sed -e 's/^/  /' && rm -Rf $(BUILD_DIR)/test_dir

$(BUILD_DIR)/test_%: test_%.c $(HEADERS) $(SOURCES) $(TEST_HEADERS) Makefile
	@echo "CC  $@"
	@gcc -Wall -Wextra -Wno-unused-parameter -Wno-unused-function $< $(SOURCES) -o $@

