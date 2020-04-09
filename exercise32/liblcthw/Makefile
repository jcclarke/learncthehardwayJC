# moved these lines to the top
SRC_DIR=./src
# added the line below
SUB_SRC_DIR_1=$(SRC_DIR)/lcthw
BUILD_DIR=./build
TESTS_DIR=./tests

CC=gcc
# added INCLUDES line on line 10 and put $(INLUCDES) before $(OPTFLAGS) on line 11 to ensure that our new libraries are added
INCLUDES=-I$(SRC_DIR) -I$(SUB_SRC_DIR_1)
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(INCLUDES) $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJECTS=$(SOURCES:%.c=%.o)

TEST_SRC=$(wildcard $(TESTS_DIR)/*_tests.c)
# changed tests to have a .tst extension when compiled
TESTS=$(patsubst %.c,%.tst,$(TEST_SRC))

# changed TARGET to SLIB_TARGET & SO_TARGET to DLIB_TARGET
SLIB_TARGET=$(BUILD_DIR)/liblcthw.a
DLIB_TARGET=$(patsubst %.a,%.so,$(SLIB_TARGET))

# The Target Build
all: target tests
	
target: build $(SLIB_TARGET) $(DLIB_TARGET) 

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(SLIB_TARGET): CFLAGS += -fPIC
$(SLIB_TARGET): $(OBJECTS) 
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(DLIB_TARGET): $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

# changed to compile *tests.c to *tests.tst
$(TESTS_DIR)/%.tst: $(TESTS_DIR)/%.c 
	$(CC) $(CFLAGS) $< $(SLIB_TARGET) -o $@ $(LIBS) #added $(SLIB_TARGET) here instead

build:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(TESTS_DIR)

# The Unit Tests
.PHONY: tests 
#tests: CFLAGS += $(SLIB_TARGET)							#removed $(SLIB_TARGET)
tests: $(TESTS) $(LIBS)
	sh ./tests/runtests.sh

valgrind:
	VARGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
# removed OSX cleanup stuff
clean:
	rm -rf $(BUILD_DIR) $(OBJECTS) $(TESTS)
	rm -f tests/tests.log

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(SLIB_TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous funtions.
	@egrep $(BADFUNCS) $(SOURCES) || true
