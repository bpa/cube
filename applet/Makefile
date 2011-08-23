OPTS=`pkg-config --cflags --libs libpanelappletmm-2.6`

cube: cube.c parser.c
	gcc $(OPTS) -o parser parser.c
	gcc $(OPTS) -o cube cube.c

install: cube
	cp cube /usr/lib/gnome-panel/
	cp cube.png /usr/share/pixmaps/
	cp cube.server /usr/lib/bonobo/servers/
