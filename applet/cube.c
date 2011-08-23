#include <string.h>
#include <panel-applet.h>
#include <gtk/gtklabel.h>

#include "cube.h"

GtkWidget *label = NULL;
GtkWidget *icon = NULL;

static gboolean on_move_press(GtkWidget *event_box, GdkEventButton *event, gpointer data) {
    gtk_label_set_text(GTK_LABEL(label), (long)data ? "next" : "prev");
    return TRUE;
}

GtkWidget *button(const gchar *stock_image, const GCallback func, gpointer forward) {
    GtkWidget *image = gtk_image_new_from_stock(stock_image, GTK_ICON_SIZE_SMALL_TOOLBAR);
    GtkWidget *event_box = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(event_box), image);
    g_signal_connect (G_OBJECT (event_box), "button_press_event", func, forward);
    return event_box;
}

/*
void draw_cube(Case *c) {
    gdk_draw_rectangle (buff,
            widget->style->white_gc,
            TRUE,
            0, 0,
            widget->allocation.width,
            widget->allocation.height);

    printf("New size: %i x %i\n", widget->allocation.width, widget->allocation.height);
}
*/

static gboolean configure_event_callback (GtkWidget *widget, GdkEventConfigure *event, gpointer data) {
    if ( widget->allocation.width != widget->allocation.height ) {
        gtk_widget_set_size_request(widget, widget->allocation.height, widget->allocation.height);
    }
    //if (buff != NULL) {
        //g_object_unref(buff);
    //}
    //buff = gdk_pixmap_new(widget->window, widget->allocation.width, widget->allocation.height, -1);
    return TRUE;
}

static gboolean cube_applet_fill (PanelApplet *applet, const gchar *iid, gpointer data) {
	GtkWidget *hbox;
	GdkPixbuf *img, *scaled;
	GError *err = NULL;
	gint size;

	if (strcmp (iid, "OAFIID:CubeApplet") != 0)
		return FALSE;

	size = panel_applet_get_size(applet);

	img = gdk_pixbuf_new_from_file("/home/ARBFUND/bruce/projects/cube/gadget/images/2.png", &err);
	scaled = gdk_pixbuf_scale_simple(img, size, size, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(scaled);
	
	gtk_widget_set_size_request(icon, size, size);
    g_signal_connect (G_OBJECT (icon), "configure_event", G_CALLBACK (configure_event_callback), NULL);

	hbox = gtk_hbox_new (FALSE, 3);
    gtk_box_pack_start(GTK_BOX(hbox), icon, FALSE, FALSE, 0);
	gtk_container_add (GTK_CONTAINER (applet), GTK_WIDGET(hbox));

	gtk_widget_show_all (GTK_WIDGET (applet));
	return TRUE;
}

PANEL_APPLET_BONOBO_FACTORY ("OAFIID:CubeApplet_Factory",
                             PANEL_TYPE_APPLET,
                             "Cube Applet",
                             "0",
                             cube_applet_fill,
                             NULL);
