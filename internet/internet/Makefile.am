####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = internet

## INCLUDES were found outside kdevelop specific part

internet_SOURCES = analogmodem.cpp lan.cpp manage.cpp info.cpp internet.cpp config.cpp cmdline.cpp error.cpp hardware.cpp help.cpp wizard.cpp parse.cpp authentication.cpp connection.cpp dialer.cpp usb.cpp xml.cpp ethernet.cpp isp.cpp db.cpp main.cpp 
internet_LDADD   = -lxml2

SUBDIRS = docs 

EXTRA_DIST = main.cpp isp.h dialer.h authentication.h hardware.h db.h db.cpp isp.cpp ethernet.cpp xml.h xml.cpp usb.cpp dialer.cpp connection.h connection.cpp authentication.cpp parse.h parse.cpp wizard.h wizard.cpp help.h help.cpp hardware.cpp internet.conf mklib.sh internet.h error.cpp cmdline.cpp config.cpp internet.cpp info.cpp manage.cpp lan.cpp analogmodem.cpp 

install-data-local:
	$(mkinstalldirs) /etc/
	$(INSTALL_DATA) $(srcdir)/internet.conf /etc/internet.conf

uninstall-local:
	-rm -f /etc/internet.conf

####### kdevelop will overwrite this part!!! (end)############
# set the include path found by configure
INCLUDES= $(all_includes)
 
# the library search path.
internet_LDFLAGS = $(all_libraries) 
                                                                                
