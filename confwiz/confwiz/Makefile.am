####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = confwiz

## INCLUDES were found outside kdevelop specific part

confwiz_SOURCES = help.ui pleasewait.ui confwiz.cpp dirview.cpp configwizard.ui main.cpp 
confwiz_LDADD   =  $(LIB_KHTML) $(LIB_KDEUI) $(LIB_KDECORE) $(LIB_QT) $(LIBSOCKET)


EXTRA_DIST = main.cpp confwiz.desktop configwizard.ui dirview.cpp dirview.h configwizard.ui.h confwiz.cpp confwiz.h pleasewait.ui confwiz-128.png confwiz-22.png confwiz-32.png confwiz-48.png confwiz-64.png confwiz-16.png pleasewait.ui.h help.ui 

install-data-local:
	$(mkinstalldirs) /etc/skel/.kde/Autostart/
	$(INSTALL_DATA) $(srcdir)/confwiz.desktop /etc/skel/.kde/Autostart/confwiz.desktop
	$(mkinstalldirs) $(kde_icondir)/kinneret/128x128/apps/
	$(INSTALL_DATA) $(srcdir)/confwiz-128.png $(kde_icondir)/kinneret/128x128/apps/confwiz.png
	$(mkinstalldirs) $(kde_icondir)/kinneret/22x22/apps/
	$(INSTALL_DATA) $(srcdir)/confwiz-22.png $(kde_icondir)/kinneret/22x22/apps/confwiz.png
	$(mkinstalldirs) $(kde_icondir)/kinneret/32x32/apps/
	$(INSTALL_DATA) $(srcdir)/confwiz-32.png $(kde_icondir)/kinneret/32x32/apps/confwiz.png
	$(mkinstalldirs) $(kde_icondir)/kinneret/48x48/apps/
	$(INSTALL_DATA) $(srcdir)/confwiz-48.png $(kde_icondir)/kinneret/48x48/apps/confwiz.png
	$(mkinstalldirs) $(kde_icondir)/kinneret/64x64/apps/
	$(INSTALL_DATA) $(srcdir)/confwiz-64.png $(kde_icondir)/kinneret/64x64/apps/confwiz.png
	$(mkinstalldirs) $(kde_icondir)/kinneret/16x16/apps/
	$(INSTALL_DATA) $(srcdir)/confwiz-16.png $(kde_icondir)/kinneret/16x16/apps/confwiz.png

uninstall-local:
	-rm -f /etc/skel/.kde/Autostart/confwiz.desktop
	-rm -f $(kde_icondir)/kinneret/128x128/apps/confwiz.png
	-rm -f $(kde_icondir)/kinneret/22x22/apps/confwiz.png
	-rm -f $(kde_icondir)/kinneret/32x32/apps/confwiz.png
	-rm -f $(kde_icondir)/kinneret/48x48/apps/confwiz.png
	-rm -f $(kde_icondir)/kinneret/64x64/apps/confwiz.png
	-rm -f $(kde_icondir)/kinneret/16x16/apps/confwiz.png

####### kdevelop will overwrite this part!!! (end)############
# These paths are KDE specific. Use them:
# kde_appsdir         Where your application's menu entry (.desktop) should go to.
# kde_icondir         Where your icon should go to - better use KDE_ICON.
# kde_sounddir        Where your sounds should go to.
# kde_htmldir         Where your docs should go to. (contains lang subdirs)
# kde_datadir         Where you install application data. (Use a subdir)
# kde_locale          Where translation files should go to. (contains lang subdirs)
# kde_cgidir          Where cgi-bin executables should go to.
# kde_confdir         Where config files should go to (system-wide ones with default values).
# kde_mimedir         Where mimetypes .desktop files should go to.
# kde_servicesdir     Where services .desktop files should go to.
# kde_servicetypesdir Where servicetypes .desktop files should go to.
# kde_toolbardir      Where general toolbar icons should go to (deprecated, use KDE_ICON).
# kde_wallpaperdir    Where general wallpapers should go to.
# kde_templatesdir    Where templates for the "New" menu (Konqueror/KDesktop) should go to.
# kde_bindir          Where executables should go to. Use bin_PROGRAMS or bin_SCRIPTS.
# kde_libdir          Where shared libraries should go to. Use lib_LTLIBRARIES.
# kde_moduledir       Where modules (e.g. parts) should go to. Use kde_module_LTLIBRARIES.
# kde_styledir        Where Qt/KDE widget styles should go to (new in KDE 3).
# kde_designerdir     Where Qt Designer plugins should go to (new in KDE 3).

# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

METASOURCES = AUTO

# the library search path. 
confwiz_LDFLAGS = $(all_libraries) $(KDE_RPATH)

# Uncomment the following two lines if you add a ui.rc file for your application to make use of
# KDEs XML GUI builing
#rcdir = $(kde_datadir)/confwiz
#rc_DATA = confwizui.rc

#WARNING: if you use a ui.rc file above, use:

# messages: rc.cpp

# instead of 

# messages:

messages: 
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/confwiz.pot; \
	fi

