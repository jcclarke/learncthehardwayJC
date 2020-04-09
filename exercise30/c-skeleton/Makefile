CC=gcc
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SRC_DIR=./src
OBJ_DIR=./objs
BUILD_DIR=./build
TESTS_DIR=./tests

SOURCES=$(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJECTS=$(SOURCES:%.c=%.o)

TEST_SRC=$(wildcard $(TESTS_DIR)/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=$(BUILD_DIR)/libex30.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: target tests
	
target: build $(TARGET) $(SO_TARGET) 

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): $(OBJECTS) 
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(TESTS_DIR)/%: $(TESTS_DIR)/%.c 
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

build:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(TESTS_DIR)

# The Unit Tests
.PHONY: tests 
tests: CFLAGS += $(TARGET)
tests: $(TESTS) $(LIBS)
	sh ./tests/runtests.sh

valgrind:
	VARGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR) $(OBJECTS) $(TESTS)
	rm -f tests/test
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous funtions.
	@egrep $(BADFUNCS) $(SOURCES) || true
