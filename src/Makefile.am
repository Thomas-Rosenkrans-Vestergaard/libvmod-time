AM_CFLAGS = $(VARNISHAPI_CFLAGS) -Wall -Werror
AM_LDFLAGS = $(VARNISHAPI_LIBS) $(VMOD_LDFLAGS)

vmod_LTLIBRARIES = libvmod_time.la

libvmod_time_la_SOURCES = \
	vmod_time.c

nodist_libvmod_time_la_SOURCES = \
	vcc_time_if.c \
	vcc_time_if.h

dist_man_MANS = vmod_time.3

@BUILD_VMOD_TIME@

AM_TESTS_ENVIRONMENT = \
	PATH="$(VMOD_TEST_PATH)" \
	LD_LIBRARY_PATH="$(VARNISH_LIBRARY_PATH)"
TEST_EXTENSIONS = .vtc
VTC_LOG_COMPILER = varnishtest -v
AM_VTC_LOG_FLAGS = -Dvmod_time="$(VMOD_TIME)"

TESTS = @VMOD_TESTS@

EXTRA_DIST = \
	vmod_time.vcc \
	$(VMOD_TESTS)
