#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#define N 1024
using namespace std;

double A[N][N];
double B[N][N];
double C[N][N];

void iteration1(double A[N][N],double B[N][N],double C[N][N]){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      C[i][j]=0;
      for(int k=0;k<N;k++){
	C[i][j] += A[i][k] * B[k][j];	
      }
    }
  }
}

void iteration2(double A[N][N],double B[N][N],double C[N][N]){
  for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
      for(int i=0;i<N;i++){
	C[i][j] += A[i][k] * B[k][j];	
      }
    }  
  }
}

void iteration3(double A[N][N],double B[N][N],double C[N][N]){
  for(int i=0;i<N;i++){
    for(int k=0;k<N;k++){
      for(int j=0;j<N;j++){
	C[i][j] += A[i][k] * B[k][j];	
      }
    }  
  }
}

void tiling(double A[N][N],double B[N][N],double C[N][N]){
  for(int i=0;i<N;i+=64){
    for(int j=0;j<N;j+=64){
      for(int k=0;k<N;k+=64){
	for(int ii=i;ii<i+64;ii++){
	  for(int jj=j;jj<j+64;jj++){
	    for(int kk=k;kk<k+64;kk++){
	      C[ii][jj] += A[ii][kk] * B[kk][jj];
	    }
	  }
	}
      }
    }
  }
}

double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;
  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

int main(){
  struct timespec start_time, end_time;
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      A[i][j] = rand()%10;
    }
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      B[i][j] = rand()%10;
    }
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      C[i][j] = 0;
    }
  }
  cout<<"Please enter your choice for iteration: (1,2,3,4)"<<endl;
  int choice;
  cin>>choice;
  if(choice==1){
    printf("you choose i,j,k option.\n");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    iteration1(A,B,C);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
  }
  else if(choice==2){
    printf("you choose j,k,i option.\n");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    iteration2(A,B,C);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
  }
  else if(choice==3){
    printf("you choose i,k,j option.\n");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    iteration3(A,B,C);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
  }
  else if(choice==4){
    printf("you choose i,j,k tiling option.\n");
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    tiling(A,B,C);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
  }
  double elapsed_ns = calc_time(start_time, end_time);
  printf("Time=%f\n", elapsed_ns/1000000000);
  return 0;
}


