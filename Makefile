# Makefile for the MPI Hello World project
# CIS 455/555
# updated Jan 2012 for OpenMPI

CXX = mpic++

hello:	hello.o	
	${LINK.cc} -o hello hello.o

hello.o:	hello.C

.PHONY:	clean

clean:
	-/bin/rm -f *.o *~ core

