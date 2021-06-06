/* help.c - Alpine Package Keeper (APK)
 *
 * Copyright (C) 2020 Timo Teräs <timo.teras@iki.fi>
 * All rights reserved.
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <zlib.h>
#include "apk_applet.h"
#include "apk_print.h"

static struct list_head apk_applet_list;

#define apk_applet_foreach(iter) list_for_each_entry(iter, &apk_applet_list, node)

void apk_applet_register(struct apk_applet *applet)
{
	list_init(&applet->node);
	list_add_tail(&applet->node, &apk_applet_list);
}

void apk_applet_register_builtin(void)
{
	extern apk_init_func_t __start_initapplets[], __stop_initapplets[];
	apk_init_func_t *p;

	list_init(&apk_applet_list);
	for (p = __start_initapplets; p < __stop_initapplets; p++)
		(*p)();
}

struct apk_applet *apk_applet_find(const char *name)
{
	struct apk_applet *a;

	apk_applet_foreach(a) {
		if (strcmp(name, a->name) == 0)
			return a;
	}
	return NULL;
}

static inline int is_group(struct apk_applet *applet, const char *topic)
{
	if (!applet) return strcasecmp(topic, "apk") == 0;
	if (strcasecmp(topic, applet->name) == 0) return 1;
	for (int i = 0; applet->optgroups[i] && i < ARRAY_SIZE(applet->optgroups); i++)
		if (strcasecmp(applet->optgroups[i]->desc, topic) == 0) return 1;
	return 0;
}
