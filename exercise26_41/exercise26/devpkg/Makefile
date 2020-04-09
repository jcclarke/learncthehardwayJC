
PREFIX?=/usr/local

# Add the apr-1 and apr-util-1 libraries when compiling
CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1 -I${PREFIX}/apr/include/apr-util-1
LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1
LDLIBS= -lapr-1 -laprutil-1

all: devpkg

# devpkg depends on the following files
devpkg: bstrlib.o db.o shell.o commands.o

install: all
	install -d $(DESTDIR)$(PREFIX)/bin/
	install devpkg $(DESTDIR)$(PREFIX)/bin/

clean:
	rm -f *.o
	rm -f devpkg
	rm -rf *.dSYM
