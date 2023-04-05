


commSerie :  commSerie.o  libserie.o
	cc -o commSerie commSerie.o  libserie.o

commSerie.o :  libserie.o  libserie.h
	cc -c commSerie.c

libserie.o : libserie.c libserie.h
	cc -c libserie.c

clean :
	rm -f ex? *.o


