# Kinneret wallpapers packege Makefile
# Written by Gai Shaked, Sep 2005.
# All Rights Reserved to GNU/Linux Kinneret
# Version 0.1
#
# Available rules :
# make (or make newer) : make only new documents
# make all 
# make install
# make clean : clean all documents from source.
# make uninstall 

destdir = $(DESTDIR)/usr/share/wallpapers

srcfiles = *.jpg *.png

.PHONY: all clean install uninstall
	
all:
	(echo "Nothing to do. Run \'make install\'" )
	
install:
#Make all directories
	mkdir $(destdir) -p
	(for i in $(srcfiles); do \
		cp -f $$i $(destdir)/; \
	done; )

uninstall:
	(for i in $(srcfiles); do \
		rm -f $$i $(destdir)/; \
	done; )

clean:
	



