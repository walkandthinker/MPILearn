#include <iostream>
#include <mpi.h>

using namespace std;

int main(int args,char *argv[]){
	int rank,size;
	int MySendMessage;
	int MyReceiveMessage;

	MPI_Init(&args,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0){
		MySendMessage=42;
		MPI_Send(&MySendMessage,1,MPI_INT,2,1,MPI_COMM_WORLD);
		cout<<"Sending message is: "<<MySendMessage<<endl;
		MySendMessage=55;// this dosent influence the result we received
	}
	else if(rank==2){
		// where run it, size must>=3, otherwise it will give you error!!!
		MPI_Recv(&MyReceiveMessage,1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		cout<<"Received message is:"<<MyReceiveMessage<<endl;
	}

	MPI_Finalize();
	return 0;
}