HEADERS := hmlc.h
SOURCES := hmlc.c
TEST_HEADERS := test_framework.h
TEST_SOURCES := $(wildcard test_*.c)
TEST_EXECUTABLES := $(patsubst %.c,%,$(TEST_SOURCES))

run-tests: $(addprefix run-,$(TEST_EXECUTABLES)) Makefile

run-test_%: test_% Makefile
	@echo "RUN $@"
	@rm -Rf test_dir && ./$< | sed -e 's/^/  /' && rm -Rf test_dir

test_%: test_%.c $(HEADERS) $(SOURCES) $(TEST_HEADERS) Makefile
	@echo "CC  $@"
	@gcc -Wall -Wextra -Wno-unused-parameter -Wno-unused-function $< $(SOURCES) -o $@

