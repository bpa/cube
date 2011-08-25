#include "cube.h"
#include <stdio.h>
#include <stdlib.h>

struct parser_state {
	GList *moves;
	struct move *current;
	gchar **field;
	void (*text_action)(struct parser_state*, const gchar *text, gsize len);
};

void ignore(struct parser_state *state, const gchar *text, gsize text_len) { }

void set(struct parser_state *state, const gchar *text, gsize text_len) {
	*state->field = g_strndup(text, text_len);
}

void append_solution(struct parser_state *state, const gchar *text, gsize text_len) {
	gchar *solution = g_strndup(text, text_len);
	state->current->solutions = g_slist_append(state->current->solutions, solution);
}

void push(struct parser_state *state, const gchar *text, gsize text_len) {
}

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
	state->current->setup = NULL;
	state->current->solutions = NULL;
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
  else if (g_strcmp0(element_name, "setup") == 0) {
		state->field = &state->current->setup;
		state->text_action = set;
  }
  else if (g_strcmp0(element_name, "solution") == 0) {
		state->text_action = append_solution;
  }
}

void text_element(GMarkupParseContext *context,
    const gchar         *text,
    gsize                text_len,
    gpointer             user_data,
    GError             **error)
{
	struct parser_state *state = user_data;
	state->text_action(state, text, text_len);
}

void end_element (GMarkupParseContext *context,
    const gchar         *element_name,
    gpointer             user_data,
    GError             **error)
{
	((struct parser_state *)user_data)->text_action = ignore;
}

static GMarkupParser parser = {
  start_element,
  end_element,
  text_element,
  NULL,
  NULL
};

GList *parse_moves() {
	struct parser_state state;
	state.moves = NULL;
	state.text_action = &ignore;

    char *text;
    gsize length;
    GMarkupParseContext *context = g_markup_parse_context_new (
      &parser,
      0,
      (gpointer*)&state,
	  NULL);

  if (g_file_get_contents ("/home/ARBFUND/bruce/projects/cube/data/cfop.xml", &text, &length, NULL) == FALSE) {
    printf("Couldn't load XML\n");

    exit(255);
  }

  if (g_markup_parse_context_parse (context, text, length, NULL) == FALSE) {
    printf("Parse failed\n");
    exit(255);
  }

  g_free(text);
  g_markup_parse_context_free (context);
  return state.moves;
}

