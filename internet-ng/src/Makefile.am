noinst_LTLIBRARIES = libcore.la

libcore_la_SOURCES = dummy.cpp
libcore_la_LIBADD = \
	core/resolvers/Resolver.lo \
	core/utils/Log.lo \
	core/utils/Config.lo \
	core/xml/xml.lo \
	core/xml/CoreErrorHandler.lo \
	core/utils/utils.lo
libcore_la_LDFLAGS = -static
libcore_la_INCLUDES = -I$(top_srcdir)/src

SUBDIRS = core . tests
