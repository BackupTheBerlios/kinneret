AC_DEFUN([AC_CHECK_PTHREAD_FOR_XERCES],
[
AC_CHECK_LIB([pthread], [pthread_mutexattr_destroy])
AC_CHECK_LIB([pthread], [pthread_mutexattr_settype])
AC_CHECK_LIB([pthread], [pthread_mutexattr_init])
])

AC_DEFUN([AC_CHECK_XERCES],
[
AC_REQUIRE([AC_CHECK_PTHREAD_FOR_XERCES])
AC_MSG_CHECKING([Xerces-C++ >= 2.6.0])
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
ac_libs_safe="$LIBS"
LIBS="-lxerces-c -lpthread"

cat > conftest.$ac_ext <<EOF
#include <xercesc/dom/DOM.hpp>
#if XERCES_VERSION_MAJOR >= 2
    #if XERCES_VERSION_MINOR < 6
        #error 1
    #endif
#else
    #error 1
#endif

int main() {
    return 0;
}
EOF

if AC_TRY_EVAL(ac_link) && test -s conftest; then
    have_xerces="yes"
else
    have_xerces="no"
fi

rm -f conftest*
LIBS="$ac_libs_safe"
AC_LANG_RESTORE

if test "$have_xerces" = "yes"; then
    LDFLAGS="$LDFLAGS -lxerces-c -lpthread"
    AC_MSG_RESULT([yes])
else
    AC_MSG_ERROR([
    !!! Xerces-C++ is not installed or is older than 2.6.0!
    !!! Please install/update it from: http://xml.apache.org/xerces-c/
    !!! Xerces-C++ is required at version 2.6.0 or above.])
fi
])

AC_DEFUN([AC_CHECK_XALAN],
[
AC_MSG_CHECKING([Xalan-C++ >= 1.7.0])
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
ac_libs_safe="$LIBS"
LIBS="-lxalan-c"

cat > conftest.$ac_ext <<EOF
#include <xalanc/Include/XalanVersion.hpp>
#if XALAN_VERSION_MAJOR >= 1
    #if XALAN_VERSION_MINOR < 7
        #error 1
    #endif
#else
    #error 1
#endif

int main() {
    return 0;
}
EOF

if AC_TRY_EVAL(ac_link) && test -s conftest; then
    have_xalan="yes"
else
    have_xalan="no"
fi

rm -f conftest*
LIBS="$ac_libs_safe"
AC_LANG_RESTORE

if test "$have_xalan" = "yes"; then
    LDFLAGS="$LDFLAGS -lxalan-c"
    AC_MSG_RESULT([yes])
else
    AC_MSG_ERROR([
    !!! Xalan-C++ is not installed or is older than 1.7.0!
    !!! Please install/update it from: http://xml.apache.org/xalan-c/
    !!! Xalan-C++ is required at version 1.7.0 or above.])
fi
])
