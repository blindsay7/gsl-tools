CFLAGS+=-I../getcols -Wall
CFLAGS!+=pkg-config --cflags gsl
LDADD!+=pkg-config --libs gsl
DPADD+=${.CURDIR}/../getcols/libgetcols.a
LDADD+=-L${.CURDIR}/../getcols -lgetcols
.PATH: ${.CURDIR}/..
