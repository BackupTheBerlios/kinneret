AC_DEFUN([AC_CHECK_XERCES],
[
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
