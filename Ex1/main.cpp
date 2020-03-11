#include <iostream>
#include <mpi.h>

using namespace std;

int main(int args,char *argv[]){
	int rank,size;

	MPI_Init(&args,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	cout<<"Hello world from rank-"<<rank+1<<endl;

	if(rank==0){
		cout<<"MPI World size= "<<size<<" processes"<<endl;
	}

	MPI_Finalize();
	return 0;
}