#ifndef CUBE_APPLET_H
#define CUBE_APPLET_H

#include <glib.h>

struct move {
	gchar *phase;
	gchar *group;
	gchar *image;
	gchar *setup;
	GSList *solutions;
};

#endif
