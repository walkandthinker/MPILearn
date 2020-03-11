#include <iostream>
#include <mpi.h>

using namespace std;

int main(int args,char *argv[]){
	int rank,size;

	MPI_Init(&args,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	for(int i=1;i<=size;++i){
		if(i==rank+1){
			cout<<" Hello from rank-"<<i<<" of size="<<size<<endl;
		}
		MPI_Barrier(MPI_COMM_WORLD);// only insiede the loop works, otherwise the order is not correct
	}

	MPI_Finalize();
	return 0;
}