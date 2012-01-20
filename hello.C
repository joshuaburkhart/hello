
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

#include <string.h> //memset

int main(int argc, char *argv[])
{
  MPI_Init(&argc,&argv);

  int nprocs;
  int myid;

  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  const int MAX_MSG_SIZE = 100;
  char buf[MAX_MSG_SIZE];
  MPI_Status s;

  // Process 0 sends a message, other processes wait for the message
  // and print it when they receive it.

  if (myid == 0) {
    string numbers[] = {"", "unos", "dos", "tres", "catorce"};
    int n = (sizeof(numbers) / sizeof(string *) );
    char buf2[MAX_MSG_SIZE]="";
    for (int i = 1; i < nprocs; i++) {
      string msg = ((i < n) ? numbers[i] : "!");
      msg += '\0';
      msg.copy(buf,msg.length());
      MPI_Send(buf,msg.length(),MPI_CHAR,i,0,MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    printf("I'm at a place called vertigo\n");
    for (int i = 1; i < nprocs; i++) {
      memset(buf,0,10);
      MPI_Recv(buf,MAX_MSG_SIZE,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&s);
      cout << buf << endl;
    }
  }
  else {
    MPI_Recv(buf,MAX_MSG_SIZE,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&s);
    cout << buf << endl; //asynchronous push to stdout
    string msg="yeah";
    msg.copy(buf,msg.length());
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Send(buf,msg.length(),MPI_CHAR,0,0,MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
