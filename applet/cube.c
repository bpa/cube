#include <string.h>

#include <panel-applet.h>
#include <gtk/gtklabel.h>

GtkWidget *label = NULL;
GtkWidget *icon = NULL;
GdkPixmap *buff = NULL;

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

void draw_cube(Case *c) {
    gdk_draw_rectangle (buff,
            widget->style->white_gc,
            TRUE,
            0, 0,
            widget->allocation.width,
            widget->allocation.height);

    printf("New size: %i x %i\n", widget->allocation.width, widget->allocation.height);
}

static gboolean configure_event_callback (GtkWidget *widget, GdkEventConfigure *event, gpointer data) {
    if ( widget->allocation.width != widget->allocation.height ) {
        gtk_widget_set_size_request(widget, widget->allocation.height, widget->allocation.height);
    }
    if (buff != NULL) {
        g_object_unref(buff);
    }
    buff = gdk_pixmap_new(widget->window, widget->allocation.width, widget->allocation.height, -1);
    return TRUE;
}

static gboolean expose_event_callback (GtkWidget *widget, GdkEventExpose *event, gpointer data) {
    printf("Exposed\n");
    gdk_draw_pixmap(widget->window,
            widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
            buff,
            event->area.x, event->area.y,
            event->area.x, event->area.y,
            event->area.width, event->area.height);

    return FALSE;
}

static gboolean cube_applet_fill (PanelApplet *applet, const gchar *iid, gpointer data) {
	GtkWidget *hbox;

	if (strcmp (iid, "OAFIID:CubeApplet") != 0)
		return FALSE;

	hbox = gtk_hbox_new (FALSE, 3);
    icon = gtk_drawing_area_new();
    g_signal_connect (G_OBJECT (icon), "configure_event", G_CALLBACK (configure_event_callback), NULL);
    g_signal_connect (G_OBJECT (icon), "expose_event", G_CALLBACK (expose_event_callback), NULL);
	label = gtk_label_new ("Cube goes here");
    gtk_box_pack_start(GTK_BOX(hbox), button(GTK_STOCK_GO_BACK, G_CALLBACK(on_move_press), (gpointer)0), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), icon, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button(GTK_STOCK_GO_FORWARD, G_CALLBACK(on_move_press), (gpointer)1), FALSE, FALSE, 0);
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
