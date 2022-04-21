#INCLUDE = -I/usr/include/mysql
#LIBDIR  = -L/usr/lib -L/usr/lib/mysql
#LIBS    = -lmysqlclient

INCLUDE =
LIBDIR  = -L/usr/lib
LIBS    =

SOURCES = index.c ltoa.c
DEST    = crl
GCC     = gcc -x c -O3 -Wall -s -foptimize-strlen

all:
	@$(GCC) $(INCLUDE) $(LIBDIR) $(LIBS) $(SOURCES) -o $(DEST)

clean:
	rm *.o $(DEST)

install:
	@#cp $(DEST) /usr/lib/cgi-bin
	cp $(DEST) /var/www/cgi
