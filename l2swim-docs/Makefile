destdir = /opt/kinneret
docdirs = he en ar ru
extradirs = image audio
stylesheet = ./etc/l2swim.xsl

srcxml = $(patsubst src/%.xml,%,$(wildcard src/*/*.xml))
srcdoc = $(wildcard doc/*/*.*)
srcimages = $(patsubst etc/image/%,%,$(wildcard etc/image/*.*))

html:
	(for i in $(docdirs); do \
		mkdir ./doc/$$i -p; \
	done; )

	(for i in $(srcxml); do \
		xsltproc -o ./doc/$$i.html \
		$(stylesheet) ./src/$$i.xml; \
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
		cp ./$$i $(destdir)/l2swim/$$i -f; \
	done; )

#Copy the images file outside l2swim
	(for i in $(srcimages); do \
		cp ./etc/image/$$i $(destdir)/images -f; \
	done; )

#Copy the menu file
	cp ./etc/swim_menu.txt $(destdir)/l2swim/etc -f;

uninstall:
	rm -r $(destdir)/l2swim;
	rm -r $(destdir)/images;

clean:
	(for i in $(docdirs); do \
		rm -r ./doc/$$i; \
	done; )


