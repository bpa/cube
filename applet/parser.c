#include "cube.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct parser_state {
	GList *moves;
	struct move *current;
	void (*text_action)(struct move *, const gchar *text, gsize text_len);
};

void ignore_text(struct move *current, const gchar *text, gsize text_len) { }

void start_element (GMarkupParseContext *context,
    const gchar         *element_name,
    const gchar        **attribute_names,
    const gchar        **attribute_values,
    gpointer             user_data,
    GError             **error) {

  const gchar **name_cursor = attribute_names;
  const gchar **value_cursor = attribute_values;
  struct parser_state *state = user_data;

  if (g_strcmp0(element_name, "move") == 0) {
	state->current = g_new(struct move, 1);
    state->moves = g_list_append(state->moves, state->current);
	  while (*name_cursor) {
		if (g_strcmp0(*name_cursor, "phase") == 0)
			state->current->phase = g_strdup(*value_cursor);
		if (g_strcmp0(*name_cursor, "group") == 0)
			state->current->group = g_strdup(*value_cursor);
		name_cursor++;
		value_cursor++;
	  }
  }
  else if (g_strcmp0(element_name, "image") == 0) {
	  while (*name_cursor) {
		if (g_strcmp0(*name_cursor, "src") == 0)
			state->current->image = g_strdup(*value_cursor);
		name_cursor++;
		value_cursor++;
	  }
  }
}

void text_element(GMarkupParseContext *context,
    const gchar         *text,
    gsize                text_len,
    gpointer             user_data,
    GError             **error)
{
	struct parser_state *state = user_data;
	state->text_action(state->current, text, text_len);
}

void end_element (GMarkupParseContext *context,
    const gchar         *element_name,
    gpointer             user_data,
    GError             **error)
{
	((struct parser_state *)user_data)->text_action = &ignore_text;
}

static GMarkupParser parser = {
  start_element,
  end_element,
  text_element,
  NULL,
  NULL
};

void move_print(gpointer data, gpointer user_data) {
	if (data != NULL) {
		struct move *m = data;
		printf("Move: %s %s %s\n", m->phase, m->group, m->image);
	}
	else {
		printf("NULL;");
	}
}

int main() {
	struct parser_state state;
	state.moves = g_list_alloc();
	state.text_action = &ignore_text;

    char *text;
    gsize length;
    GMarkupParseContext *context = g_markup_parse_context_new (
      &parser,
      0,
      (gpointer*)&state,
	  NULL);

  if (g_file_get_contents ("../data/cfop.xml", &text, &length, NULL) == FALSE) {
    printf("Couldn't load XML\n");
    exit(255);
  }

  if (g_markup_parse_context_parse (context, text, length, NULL) == FALSE) {
    printf("Parse failed\n");
    exit(255);
  }

  g_free(text);
  g_markup_parse_context_free (context);
  g_list_foreach(state.moves, move_print, NULL);
  return 0;
}

