#include <iostream>
#include <cmath>
#include <mpi.h>

using namespace std;

double integral(const double &a,const int &n,const double &h){
	double h2,aij,integ;

	integ=0.0;
	h2=h*0.5;
	for(int j=0;j<n;++j){
		aij=a+j*h;
		integ+=cos(aij+h2)*h;
	}
	return integ;
}

int main(int args,char *argv[]){
	int rank,size,tag;

	const double pi=acos(-1.0);
	double a=0.0,b=0.5*pi;
	int n=5000000,num;
	double result,localresult;
	double h;
	double alocal,blocal,hlocal;


	MPI_Status status;
	MPI_Init(&args,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	h=(b-a)/n;
	num=n/size;

	hlocal=(b-a)/size;
	alocal=a+rank*hlocal;
	localresult=integral(alocal,num,h);

	cout<<"result from rank-"<<rank+1<<" is:"<<localresult<<endl;
	MPI_Barrier(MPI_COMM_WORLD);


	MPI_Reduce(&localresult,&result,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0){
		cout<<" final result is:"<<result<<endl;
	}

	MPI_Finalize();
	return 0;
}