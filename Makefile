all:    TServer pais
TServer:
	gcc -g -O2 -Wall -o  TServer  ./libfcgi/.libs/libfcgi.so -lnsl -Wl,--rpath -Wl,/usr/local/lib  getpais.c TServer.c  
pais:
	gcc -g -O2 -Wall -o pais getpais.c testpais.c
clean:
	rm -f TServer
	rm -f pais
	rm -f *.o
