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

GList *parse_moves();
void move_print(gpointer data, gpointer user_data);
GString *g_string_new_from_move(struct move *mv);

#endif
