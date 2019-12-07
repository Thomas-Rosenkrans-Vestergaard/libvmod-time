#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cache/cache.h"

#include "vtim.h"
#include "vcc_time_if.h"

/* Varnish < 6.2 compat */
#ifndef VPFX
#define VPFX(a) vmod_##a
#define VARGS(a) vmod_##a##_arg
#define VENUM(a) vmod_enum_##a
#define VEVENT(a) a
#else
#define VEVENT(a) VPFX(a)
#endif

const size_t infosz = 64;
char *info;

/*
 * handle vmod internal state, vmod init/fini and/or varnish callback
 * (un)registration here.
 *
 * malloc'ing the info buffer is only indended as a demonstration, for any
 * real-world vmod, a fixed-sized buffer should be a global variable
 */

int
	VEVENT(event_function)(VRT_CTX, struct VPFX(priv) * priv, enum vcl_event_e e)
{
	char ts[VTIM_FORMAT_SIZE];
	const char *event = NULL;

	(void)ctx;
	(void)priv;

	switch (e)
	{
	case VCL_EVENT_LOAD:
		info = malloc(infosz);
		if (!info)
			return (-1);
		event = "loaded";
		break;
	case VCL_EVENT_WARM:
		event = "warmed";
		break;
	case VCL_EVENT_COLD:
		event = "cooled";
		break;
	case VCL_EVENT_DISCARD:
		free(info);
		return (0);
		break;
	default:
		return (0);
	}
	AN(event);
	VTIM_format(VTIM_real(), ts);
	snprintf(info, infosz, "vmod_time %s at %s", event, ts);

	return (0);
}

VCL_STRING
VPFX(info)(VRT_CTX)
{
	(void)ctx;

	return (info);
}

VCL_INT
VPFX(get_unix)(VRT_CTX)
{	
	return (unsigned long)time(NULL);
}

VCL_INT
VPFX(next_day)(VRT_CTX, VCL_INT time)
{
	struct tm *ts;
    ts = localtime(&time);
    ts->tm_mday++;
    ts->tm_hour = 0;
    ts->tm_min = 0;
    ts->tm_sec = 0;
    return (int)mktime(ts);
}

VCL_DURATION
VPFX(duration_s)(VRT_CTX, VCL_INT time)
{
	return (double) time;
}