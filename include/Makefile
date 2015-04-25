includedir=$(prefix)/include

build:

install: $(includedir)/aTime.H

$(includedir)/aTime.H: aTime.H
	cp aTime.H $(includedir)

uninstall:
	- rm -f $(includedir)/aTime.H

clean:
