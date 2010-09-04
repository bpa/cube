OPTS=`pkg-config --cflags --libs libpanelapplet-2.0`

cube: cube.c
	gcc $(OPTS) -o cube cube.c

install: cube
	cp cube /usr/lib/gnome-panel/
	cp cube.png /usr/share/pixmaps/
	cp cube.server /usr/lib/bonobo/servers/
