OPTS=`pkg-config --cflags --libs libpanelappletmm-2.6`

cube: cube.o parser.o
	gcc $(OPTS) -o cube cube.o parser.o

.c.o:
	gcc $(OPTS) -c $<

install: cube
	cp cube /usr/lib/gnome-panel/
	cp cube.png /usr/share/pixmaps/
	cp cube.server /usr/lib/bonobo/servers/
