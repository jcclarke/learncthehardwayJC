SRC_DIR=./src
SUB_SRC_DIR_1=$(SRC_DIR)/lcthw
BUILD_DIR=./build
# exercise 45 - added BIN_DIR to setup compilation of TCP/IP and other programs
BIN_DIR=./bin
TESTS_DIR=./tests

CC=gcc
INCLUDES=-I$(SRC_DIR) -I$(SUB_SRC_DIR_1)
CFLAGS=-g -O2 -Wall -Wextra -Isrc $(shell pkg-config --cflags libbsd) -rdynamic -DNDEBUG $(INCLUDES) $(OPTFLAGS)
LIBS= $(shell pkg-config --libs libbsd) -ldl $(OPTLIBS)
LDLIBS=-$(LIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJECTS=$(SOURCES:%.c=%.o)

TEST_SRC=$(wildcard $(TESTS_DIR)/*_tests.c)
TESTS=$(patsubst %.c,%.tst,$(TEST_SRC))

# exercise 45 - added to setup compilation of TCP/IP and other programs
PROGRAMS_SRC=$(wildcard bin/*.c)
PROGRAMS=$(patsubst %.c, %.exe, $(PROGRAMS_SRC))

SLIB_TARGET=$(BUILD_DIR)/liblcthw.a
DLIB_TARGET=$(patsubst %.a,%.so,$(SLIB_TARGET))

# exercise 45 - added $(PROGRAMS) to run TCP/IP program
# The Target Build
all: target tests 
	
target: build $(SLIB_TARGET) $(DLIB_TARGET) $(PROGRAMS)

dev: CFLAGS=-g -Wall -Wextra -Isrc $(shell pkg-config --cflags libbsd) $(OPTFLAGS)
dev: all

$(SLIB_TARGET): CFLAGS += -fPIC
$(SLIB_TARGET): $(OBJECTS) 
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(DLIB_TARGET): $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) -lm

# exercise 45 - added to compile TCP/IP and other programs
$(BIN_DIR)/%.exe: $(BIN_DIR)/%.c
	$(CC) $(CFLAGS) $< $(SLIB_TARGET) -o $@ 

$(TESTS_DIR)/%.tst: $(TESTS_DIR)/%.c 
	$(CC) $(CFLAGS) $< $(SLIB_TARGET) -o $@ $(LIBS) -lm

build:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(TESTS_DIR)

# The Unit Tests
.PHONY: tests
tests: $(TESTS) $(LIBS)
	sh ./tests/runtests.sh

valgrind:
	VARGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
# exercise 45 - added rm -rf $(PROGRAMS) to remove TCP/IP program
clean:
	rm -rf $(BUILD_DIR) $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	rm -rf $(PROGRAMS)

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(SLIB_TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous funtions.
	@egrep $(BADFUNCS) $(SOURCES) || true
