OPTS=`pkg-config --cflags --libs libpanelapplet-2.0`

cube: cube.o parser.o move.o
	gcc $(OPTS) -o cube cube.o parser.o move.o

.c.o:
	gcc $(OPTS) -c $<

install: cube
	cp cube /usr/lib/gnome-panel/
	cp cube.png /usr/share/pixmaps/
	cp cube.server /usr/lib/bonobo/servers/
	cp -R ../data /usr/share/gnome-applets/cube/

clean:
	rm -f *.o cube
