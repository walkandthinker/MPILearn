#include <iostream>
#include <vector>
#include <chrono>
#include <mpi.h>

using namespace std;


int main(int args,char *argv[]){
	int size,rank;


	const int n=500000;
	const int m=100;
	vector<vector<double>> vec;
	int istart,iend,rankn;

	vec.resize(n,vector<double>(m,0.0));

	auto starttime=chrono::high_resolution_clock::now();

	MPI_Init(&args,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	rankn=n/size;
	istart=rank*rankn;
	iend=istart+rankn;
	if(rank==size-1) iend=n;
	for(int i=istart;i<iend;++i){
		for(int j=0;j<m;++j){
			vec[i][j]=1.0*(j+1);
		}
	}
	if(rank!=0){
		MPI_Send(&vec[istart][0],m,MPI_DOUBLE,0,111,MPI_COMM_WORLD);
	}

	if(rank==0){
		for(int i=1;i<size;i++){
			istart=i*rankn;
			iend=istart+rankn;
			if(i==size-1) iend=n;
			MPI_Recv(&vec[istart][0],m,MPI_DOUBLE,i,111,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
		auto endtime=chrono::high_resolution_clock::now();
		//MPI_Recv(&MyReceiveMessage,1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Duration time=%14.6e\n",chrono::duration_cast<std::chrono::microseconds>(endtime-starttime).count()/1.0e6);
		double sum;
		sum=0.0;
		for(int i=0;i<n;++i){
			for(int j=0;j<m;++j){
				sum+=vec[i][j];
			}
		}
		cout<<"Sum="<<sum<<" , analytical="<<n*(1+m)*1.0*m/2.0<<endl;
	}

	MPI_Finalize();

	return 0;
}