PKG_CONFIG		?= pkg-config

OPENSSL_CFLAGS		:= $(shell $(PKG_CONFIG) --cflags openssl)
OPENSSL_LIBS		:= $(shell $(PKG_CONFIG) --libs openssl)

ZLIB_CFLAGS		:= $(shell $(PKG_CONFIG) --cflags zlib)
ZLIB_LIBS		:= $(shell $(PKG_CONFIG) --libs zlib)

# Dynamic library
libapk_soname		:= $(VERSION)
libapk_so		:= $(obj)/libapk.so.$(libapk_soname)
libapk.so.$(libapk_soname)-objs := \
	adb.o common.o context.o database.o package.o commit.o solver.o \
	trust.o version.o atom.o blob.o hash.o print.o \
	io.o io_url.o io_gunzip.o io_archive.o

libapk.so.$(libapk_soname)-libs := libfetch/libfetch.a

shlibs-y		+= libapk.so.$(libapk_soname)
LDFLAGS_libapk.so.$(libapk_soname) += -Wl,-soname,libapk.so.$(libapk_soname)

install-libapk_so	:= $(INSTALLDIR) $(DESTDIR)$(LIBDIR) && \
			   $(INSTALL) $(libapk_so) $(DESTDIR)$(LIBDIR) && \
			   $(LN) libapk.so.$(libapk_soname) $(DESTDIR)$(LIBDIR)/libapk.so

# Static library
libapk.a-objs		:= $(libapk.so.$(libapk_soname)-objs)
libapk.a-libs		:= $(libapk.so.$(libapk_soname)-libs)

libs-y			+= libapk.a
libapk_a		:= $(obj)/libapk.a

install-libapk_a	:= $(INSTALLDIR) $(DESTDIR)$(LIBDIR) && \
			   $(INSTALL) $(libapk_a) $(DESTDIR)$(LIBDIR)
apk-static-libs		:= $(libapk.a-libs) $(obj)/libapk.a

# Apk utility
progs-y			+= apk
apk-objs		:= apk.o applet.o \
			   app_add.o app_del.o app_fix.o app_update.o app_upgrade.o \
			   app_info.o app_list.o app_search.o app_manifest.o \
			   app_policy.o app_stats.o \
			   app_cache.o app_version.o \
			   app_index.o app_fetch.o app_verify.o app_dot.o \
			   app_audit.o

ifeq ($(ADB),y)
libapk.so.$(libapk_soname)-objs += apk_adb.o
apk-objs		+= app_adbdump.o app_adbsign.o app_mkndx.o \
			   app_convdb.o app_convndx.o
endif

LIBS_apk		:= -lapk
LIBS_apk-test		:= -lapk
LIBS_apk.so		:= -L$(obj) -lapk

CFLAGS_ALL		+= -D_ATFILE_SOURCE -Ilibfetch
CFLAGS_apk.o		:= -DAPK_VERSION=\"$(VERSION)\"
CFLAGS_apk-static.o	:= -DAPK_VERSION=\"$(VERSION)\" -DOPENSSL_NO_ENGINE
CFLAGS_apk-test.o	:= -DAPK_VERSION=\"$(VERSION)\" -DOPENSSL_NO_ENGINE -DTEST_MODE

progs-$(STATIC)		+= apk.static
apk.static-objs		:= $(filter-out apk.o,$(apk-objs)) apk-static.o
apk.static-libs		:= $(apk-static-libs)
LDFLAGS_apk.static	:= -static
LIBS_apk.static		:= -Wl,--as-needed -ldl -Wl,--no-as-needed
LDFLAGS_apk		+= -L$(obj)
LDFLAGS_apk-test	+= -L$(obj)

CFLAGS_ALL		+= $(OPENSSL_CFLAGS) $(ZLIB_CFLAGS)
LIBS			:= -Wl,--as-needed \
				$(OPENSSL_LIBS) $(ZLIB_LIBS) \
			   -Wl,--no-as-needed

# Test build
ifeq ($(TEST),y)
progs-y			+= apk-test
apk-test-objs		:= apk-test.o $(filter-out apk.o, $(apk-objs))
endif

$(obj)/apk: $(libapk_so)

$(obj)/apk-test: $(libapk_so)

$(obj)/apk.so: $(libapk_so)

generate-y	+= libapk.so

$(obj)/libapk.so:
	$(LN) libapk.so.$(libapk_soname) $(obj)/libapk.so

generate-y	+= apk.pc

install: $(obj)/apk $(libapk_so) $(libapk_a)
	$(INSTALLDIR) $(DESTDIR)$(SBINDIR)
	$(INSTALL) $(obj)/apk $(DESTDIR)$(SBINDIR)
	$(install-libapk_so)
	$(install-libapk_a)
	$(INSTALLDIR) $(DESTDIR)$(INCLUDEDIR)/apk
	$(INSTALL) -m644 src/*.h $(DESTDIR)$(INCLUDEDIR)/apk
	$(INSTALLDIR) $(DESTDIR)$(PKGCONFIGDIR)
	$(INSTALL) -m644 $(obj)/apk.pc $(DESTDIR)$(PKGCONFIGDIR)

