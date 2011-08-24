#include <string.h>
#include <panel-applet.h>
#include <gtk/gtklabel.h>

#include "cube.h"

GList *moves;
GList *current;
GtkWidget *icon = NULL;
GdkPixbuf *image;
gint size;

static const char Context_menu_xml [] =
   "<popup name=\"button3\">\n"
   "   <menuitem name=\"Properties Item\" "
   "             verb=\"ExampleProperties\" "
   "           _label=\"_Preferences...\"\n"
   "          pixtype=\"stock\" "
   "          pixname=\"gtk-properties\"/>\n"
   "   <menuitem name=\"About Item\" "
   "             verb=\"ExampleAbout\" "
   "           _label=\"_About...\"\n"
   "          pixtype=\"stock\" "
   "          pixname=\"gnome-stock-about\"/>\n"
   "</popup>\n";

/*
static void display_properties_dialog (BonoboUIComponent *uic, struct MultiRes *applet) {
}

static void display_about_dialog (BonoboUIComponent *uic, struct MultiRes *applet) {
}
*/

static const BonoboUIVerb myexample_menu_verbs [] = {
        //BONOBO_UI_VERB ("ExampleProperties", display_properties_dialog),
        //BONOBO_UI_VERB ("ExampleAbout", display_about_dialog),
        BONOBO_UI_VERB_END
};

void update_icon() {
	GdkPixbuf *scaled;
	GError *err = NULL;
	move_print(current->data, NULL);
	GString *path = g_string_new("/home/ARBFUND/bruce/projects/cube/gadget/");
	g_string_append(path, ((struct move*)current->data)->image);
	image = gdk_pixbuf_new_from_file(path->str, &err);
	g_string_free(path, TRUE);
	scaled = gdk_pixbuf_scale_simple(image, size, size, GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf((GtkImage*)icon, scaled);
}

void cmd_next() {
	current = g_list_next(current);
	if (current == NULL) {
		current = g_list_first(moves);
	}
	update_icon();
}

static gboolean on_left_click(GtkWidget *event_box, GdkEventButton *event, gpointer data) {
	printf("click\n");
	cmd_next();
	return FALSE;
}

GtkWidget *button(const gchar *stock_image, const GCallback func, gpointer forward) {
	GtkWidget *image = gtk_image_new_from_stock(stock_image, GTK_ICON_SIZE_SMALL_TOOLBAR);
	GtkWidget *event_box = gtk_event_box_new();
	gtk_container_add(GTK_CONTAINER(event_box), image);
	g_signal_connect (G_OBJECT (event_box), "button_press_event", func, forward);
	return event_box;
}

//static gboolean configure_event_callback (GtkWidget *widget, GdkEventConfigure *event, gpointer data) {
//	if ( widget->allocation.width != widget->allocation.height ) {
//		gtk_widget_set_size_request(widget, widget->allocation.height, widget->allocation.height);
//	}
	//if (buff != NULL) {
	//g_object_unref(buff);
	//}
	//buff = gdk_pixmap_new(widget->window, widget->allocation.width, widget->allocation.height, -1);
	//return TRUE;
//}

static gboolean cube_applet_fill (PanelApplet *applet, const gchar *iid, gpointer data) {
	GtkWidget *event_box;

	if (strcmp (iid, "OAFIID:CubeApplet") != 0)
		return FALSE;

	panel_applet_setup_menu (PANEL_APPLET (applet),
                         Context_menu_xml,
                         myexample_menu_verbs,
                         NULL);
	size = panel_applet_get_size(applet);
	icon = gtk_image_new();
	event_box = gtk_event_box_new();
	gtk_event_box_set_visible_window((GtkEventBox*)event_box, FALSE);
	gtk_widget_set_size_request(icon, size, size);
	//gtk_widget_set_events (event_box, GDK_BUTTON_PRESS_MASK);
	//g_signal_connect (G_OBJECT (icon), "configure_event", G_CALLBACK (configure_event_callback), NULL);
	g_signal_connect (G_OBJECT (event_box), "button_press_event", G_CALLBACK (on_left_click), NULL);

	gtk_container_add (GTK_CONTAINER (event_box), GTK_WIDGET(icon));
	gtk_container_add (GTK_CONTAINER (applet), GTK_WIDGET(event_box));

	moves = parse_moves();
	current = g_list_first(moves);
	update_icon();

	gtk_widget_show_all (GTK_WIDGET (applet));
	return TRUE;
}

PANEL_APPLET_BONOBO_FACTORY ("OAFIID:CubeApplet_Factory",
		PANEL_TYPE_APPLET,
		"Cube Applet",
		"0",
		cube_applet_fill,
		NULL);
