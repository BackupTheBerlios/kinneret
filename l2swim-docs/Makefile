# Swimming Guide documents Makefile,
# Written by Nir Misgav, Dec 2003.
# All Rights Reserved to GNU/Linux Kinneret
# Version 0.3
#
# Available rules :
# make (or make newer) : make only new documents
# make all 
# make install
# make clean : clean all documents from source.
# make uninstall 

destdir = $(DESTDIR)/opt/kinneret
docdirs = he en ar ru
extradirs = image audio samples pdf
stylesheet = etc/l2swim.xsl
menufile = etc/swim_menu.txt etc/swim_menu.xml
cssfile = etc/l2swim.css

srcxml = $(patsubst src/%.xml,%,$(wildcard src/*/*.xml))
srchtml = $(wildcard doc/*/*.html)
srcdoc = $(patsubst doc/CVS/%,,$(wildcard doc/*/*.*))
srcimages = $(patsubst etc/image/%,%,$(wildcard etc/image/*.*))

.PHONY: newer all clean install uninstall
	
newer:
	(for i in $(docdirs); do \
		mkdir ./doc/$$i -p; \
	done; )

# make only newer xml's.
	(for i in $(srcxml); do \
	if [[  src/$$i.xml -nt doc/$$i.html || etc/l2swim.xsl -nt doc/$$i.html ]]; then \
		if xsltproc -o ./doc/$$i.html \
		$(stylesheet) ./src/$$i.xml; then \
			echo "$$i.xml parsed. success."; \
		fi; \
	fi; \
	done; )

all:
	(for i in $(docdirs); do \
		mkdir doc/$$i -p; \
	done; )
	
	(for i in $(srcxml); do \
	if xsltproc -o ./doc/$$i.html \
	$(stylesheet) ./src/$$i.xml; then \
		echo "$$i.xml parsed. success."; \
	fi; \
	done; )
	
install:
#Make all directories
	mkdir $(destdir)/l2swim/etc -p
	mkdir $(destdir)/images -p
	(for i in $(docdirs) $(extradirs); do \
		mkdir $(destdir)/l2swim/doc/$$i -p; \
	done; )

#Copy all docs
	(for i in $(srcdoc); do \
		cp -f $$i $(destdir)/l2swim/$$i; \
	done; )

#Copy the images file outside l2swim
	(for i in $(srcimages); do \
		cp -f etc/image/$$i $(destdir)/images; \
	done; )

#Copy the menu file
	cp -f $(menufile) $(cssfile) $(destdir)/l2swim/etc;

uninstall:
	rm -r -f $(destdir)/l2swim $(destdir)/images;

clean:
	rm -f $(srchtml);
	



