# Makefile for the MPI Hello World project
# CIS 455/555
# updated Jan 2006

MPI = /opt/absoft_hpcsdk/mpich2-64-1.0.1
CXX = xlC
CXXFLAGS += -I${MPI}/include -q64
LDFLAGS += -L${MPI}/lib

hello:	hello.o
	${LINK.cc} -o hello hello.o -lmpich

hello.o:	hello.C

.PHONY:	clean

clean:
	-/bin/rm -f *.o *~ core

