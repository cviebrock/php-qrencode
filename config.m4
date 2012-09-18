dnl
dnl $ Id: $
dnl

PHP_ARG_WITH(qrencode, whether qrencode is available,[  --with-qrencode[=DIR] With qrencode support])


if test "$PHP_QRENCODE" != "no"; then


  if test -r "$PHP_QRENCODE/include/qrencode.h"; then
	PHP_QRENCODE_DIR="$PHP_QRENCODE"
  else
	AC_MSG_CHECKING(for qrencode in default path)
	for i in /usr /usr/local; do
	  if test -r "$i/include/qrencode.h"; then
		PHP_QRENCODE_DIR=$i
		AC_MSG_RESULT(found in $i)
		break
	  fi
	done
	if test "x" = "x$PHP_QRENCODE_DIR"; then
	  AC_MSG_ERROR(not found)
	fi
  fi

  PHP_ADD_INCLUDE($PHP_QRENCODE_DIR/include)

  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_QRENCODE"
  AC_CHECK_HEADER([qrencode.h], [], AC_MSG_ERROR('qrencode.h' header not found))
  PHP_SUBST(QRENCODE_SHARED_LIBADD)

  PHP_ADD_LIBRARY_WITH_PATH(qrencode, $PHP_QRENCODE_DIR/lib, QRENCODE_SHARED_LIBADD)
  export CPPFLAGS="$OLD_CPPFLAGS"

  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_QRENCODE"
  export CPPFLAGS="$OLD_CPPFLAGS"


  PHP_SUBST(QRENCODE_SHARED_LIBADD)
  AC_DEFINE(HAVE_QRENCODE, 1, [ ])
  PHP_NEW_EXTENSION(qrencode, qrencode.c , $ext_shared)

fi

