# LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

CXX = mpic++

hello:	hello.o	
	${LINK.cc} -o hello hello.o

hello.o:	hello.C
	${LINK.cc} -c hello.C

.PHONY:	clean

clean:
	-/bin/rm -f *.o *~ core

