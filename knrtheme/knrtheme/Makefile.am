####### kdevelop will overwrite this part!!! (begin)##########
kde_module_LTLIBRARIES = libkcm_knrtheme.la


INCLUDES = $(all_includes)


LDFLAGS =   

libkcm_knrtheme_la_METASOURCES=AUTO

libkcm_knrtheme_la_SOURCES = theme.cpp newthemedlg.cpp krdb.cpp knrtheme.cpp 
libkcm_knrtheme_la_LIBADD =  $(LIB_KFILE) $(LIB_KDEUI) $(LIB_KDECORE) $(LIB_QT)

libkcm_knrtheme_la_LDFLAGS = $(all_libraries) -module $(KDE_PLUGIN)    



EXTRA_DIST = knrtheme.cpp knrtheme.h krdb.cpp krdb.h newthemedlg.cpp newthemedlg.h theme.cpp theme.h knrtheme.desktop 

install-data-local:
	$(mkinstalldirs) $(kde_appsdir)/Settings/LookNFeel/
	$(INSTALL_DATA) $(srcdir)/knrtheme.desktop $(kde_appsdir)/Settings/LookNFeel/knrtheme.desktop

uninstall-local:
	-rm -f $(kde_appsdir)/Settings/LookNFeel/knrtheme.desktop

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

messages:
	$(XGETTEXT) $(libkcm_knrtheme_la_SOURCES) -o $(podir)/knrtheme.pot

