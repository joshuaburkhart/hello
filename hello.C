
// C++/MPI version of "Hello, World"
//
// John Conery
// CIS 455/555
// Jan 2006

// In this demo, process 0 sends a message to every other
// process.  When those processes receive the message, they
// print it.

// The programming exercise is to add code so that after the
// other processes receive a message they return a new message
// to process 0.

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "mpi.h"

#include <sstream>
using std::ostringstream;

int main(int argc, char *argv[])
{
  MPI_Init(&argc,&argv);

  int nprocs;
  int myid;

  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  const int MAX_MSG_SIZE = 100;
  char buf[MAX_MSG_SIZE];

  // Process 0 sends a message, other processes wait for the message
  // and print it when they receive it.

  if (myid == 0) {
    const char *numbers[] = {"", "unos", "dos", "tres", "catorce"};
    int n = (sizeof(numbers)/sizeof(char *));
    for (int i = 1; i < nprocs; i++) {
      string msg = ((i < n) ? numbers[i] : "!");
      msg += '\0';
      msg.copy(buf,msg.length());
      MPI_Send(buf,msg.length(),MPI_CHAR,i,0,MPI_COMM_WORLD);
    }
  ostringstream os1;
  MPI_Barrier(MPI_COMM_WORLD); //wait for slaves to finish printing to stdout
  for(int i=1; i < nprocs; i++){
      MPI_Status t;
      MPI_Recv(buf,MAX_MSG_SIZE,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&t);
      os1 << buf << "\n";
    }
  printf("I'm at a place called vertigo\n");
  cout << os1.str() << endl;  
  }
  else {
    MPI_Status s;
    MPI_Recv(buf,MAX_MSG_SIZE,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&s);
    cout << buf << endl; //unsynchronous push to stdout
    ostringstream oss;
    oss << myid;
    string msg="yeah from ";
    msg+= oss.str();
    msg+='\0';
    msg.copy(buf,msg.length());
    MPI_Barrier(MPI_COMM_WORLD); /*
				 MPI_Barrier here fixes cout racing issue.. 
                                 I think what this is doing in the background is
                                 forcing each thread to push it's private string
                                 stream to stdout?
				 */
    MPI_Send(buf,msg.length(),MPI_CHAR,0,0,MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
