noinst_LTLIBRARIES = libcore.la

libcore_la_SOURCES = dummy.cpp
libcore_la_LIBADD = \
		core/resolvers/lib.la \
		core/utils/lib.la
libcore_la_INCLUDES = -I$(top_srcdir)/src

SUBDIRS = core . tests
