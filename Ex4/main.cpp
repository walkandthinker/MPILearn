#include <iostream>
#include <vector>
#include <chrono>
#include <set>
#include <mpi.h>

using namespace std;

typedef int ElmtType;
typedef int MateType;

int main(int args,char *argv[]){
	int size,rank;

	// _MeshElmtInfoList
	// _BulkElmtDofIndexList


	vector<pair<ElmtType,pair<MateType,int>>> _MeshElmtInfoList;
	vector<vector<int>> _BulkElmtDofIndexList;

	const int n=10;
	const int m=2;
	int istart,iend,rankn;

	_MeshElmtInfoList.resize(n);
	_BulkElmtDofIndexList.resize(n,vector<int>(m));
	

	auto starttime=chrono::high_resolution_clock::now();

	MPI_Init(&args,&argv);

	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	rankn=n/size;
	istart=rank*rankn;
	iend=istart+rankn;
	if(rank==size-1) iend=n;
	for(int i=istart;i<iend;++i){
		// vector<pair<ElmtType,pair<MateType,int>>>
		_MeshElmtInfoList[i].first=1;
		_MeshElmtInfoList[i].second.first=2;
		_MeshElmtInfoList[i].second.second=-1;



		for(int j=1;j<=m;++j){
			_BulkElmtDofIndexList[i][j-1]=j;
		}
		if(rank!=0){
			MPI_Send(&_MeshElmtInfoList[i].first,1,MPI_INT,0,11,MPI_COMM_WORLD);
			MPI_Send(&_MeshElmtInfoList[i].second.first,1,MPI_INT,0,12,MPI_COMM_WORLD);
			MPI_Send(&_MeshElmtInfoList[i].second.second,1,MPI_INT,0,13,MPI_COMM_WORLD);
			MPI_Send(&_BulkElmtDofIndexList[i][0],m,MPI_INT,0,2,MPI_COMM_WORLD);
		}
	}
	
	

	if(rank==0){
		for(int i=1;i<size;i++){
			istart=i*rankn;
			iend=istart+rankn;
			if(i==size-1) iend=n;
			for(int j=istart;j<iend;j++){
				MPI_Recv(&_MeshElmtInfoList[j].first,1,MPI_INT,i,11,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				MPI_Recv(&_MeshElmtInfoList[j].second.first,1,MPI_INT,i,12,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				MPI_Recv(&_MeshElmtInfoList[j].second.second,1,MPI_INT,i,13,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				MPI_Recv(&_BulkElmtDofIndexList[j][0],m,MPI_INT,i,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			}
		}
		auto endtime=chrono::high_resolution_clock::now();
		//MPI_Recv(&MyReceiveMessage,1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Duration time=%14.6e\n",chrono::duration_cast<std::chrono::microseconds>(endtime-starttime).count()/1.0e6);
	}
	
	if(rank==0){
	for (int i = 0; i < n; i++){
		cout << "e=" << i + 1 << ": elmttype=" << _MeshElmtInfoList[i].first
				 << "-->matetype=" << _MeshElmtInfoList[i].second.first
				 << ", mateindex=" << _MeshElmtInfoList[i].second.second << endl;
			cout << "   MeshIndex=:";
			for (int j = 0; j < m; j++){
				cout << _BulkElmtDofIndexList[i][j] << " ";
			}
			cout << endl;
		}
	
	}
	MPI_Finalize();

	return 0;
}