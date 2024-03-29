##
# Building apk-tools

-include config.mk

PACKAGE := apk-tools
include version.mk

##
# Default directories

DESTDIR		:=
SBINDIR		:= /usr/bin
LIBDIR		:= /usr/lib
CONFDIR		:= /etc/apk
MANDIR		:= /usr/share/man
DOCDIR		:= /usr/share/doc/apk
INCLUDEDIR	:= /usr/include
PKGCONFIGDIR	:= /usr/lib/pkgconfig

export DESTDIR SBINDIR LIBDIR CONFDIR MANDIR DOCDIR INCLUDEDIR PKGCONFIGDIR

##
# Top-level subdirs

subdirs		:= libfetch/ src/

##
# Include all rules and stuff

include Make.rules

##
# Top-level targets

install:
	$(INSTALLDIR) $(DESTDIR)$(DOCDIR)
	$(INSTALL) README.md $(DESTDIR)$(DOCDIR)

static:
	$(Q)$(MAKE) STATIC=y

src/: libfetch/
