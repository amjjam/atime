libdir=$(prefix)/lib

CPPFLAGS=-Wall -g -fPIC
CPP=g++

ATIME_SRC=aTime.C
ATIME_OBJ=$(ATIME_SRC:.C=.o)

build: libaTime.a libaTime.so

libaTime.a: $(ATIME_OBJ)
	ar rc $@ $^

libaTime.so: $(ATIME_OBJ)
	$(CPP) -shared -Wl,-soname,$@ -o $@ $^

install: $(libdir)/libaTime.a $(libdir)/libaTime.so

$(libdir)/libaTime.a $(libdir)/libaTime.so: libaTime.a libaTime.so
	cp libaTime.a libaTime.so $(libdir)

uninstall:
	- rm -f $(libdir)/libaTime.a $(libdir)/libaTime.so

clean:
	- rm -f libaTime.a libaTime.so $(ATIME_OBJ)
