#include "cube.h"
#include <stdio.h>

void solution_print(gpointer data, gpointer user_data) {
	if (data != NULL) {
		printf("  %s\n", (gchar*)data);
	}
	else {
		printf("  NULL\n");
	}
}

void move_print(gpointer data, gpointer user_data) {
	if (data != NULL) {
		struct move *m = data;
		printf("Move: %s %s\nImage: %s\n", m->phase, m->group, m->image);
		printf("Setup: %s\nSolutions:\n", m->setup);
		g_slist_foreach(m->solutions, solution_print, NULL);
	}
	else {
		printf("NULL;");
	}
}

void g_string_add_solution(gpointer solution, gpointer str) {
	g_string_append_printf(str, "\n%s", (gchar*)solution);
}

GString *g_string_new_from_move(struct move *m) {
	GString *str = g_string_new("Setup: ");
	g_string_append_printf(str, "%s\nSolutions:", m->setup);
	g_slist_foreach(m->solutions, g_string_add_solution, str);
	return str;
}
