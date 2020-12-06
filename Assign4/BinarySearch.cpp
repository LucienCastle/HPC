#include <iostream>
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#define N 10000000

using namespace std;
int a[N];

int parBinarySearch(int a[],int low,int high,int key){
  int loc = -1;
  int mid;
  while(low<=high){
    mid = (high + low )/2;
    if (a[mid] == key) {
      loc = mid;
      break;
    }
    else {
      #pragma omp parallel sections num_threads(2)
      {
        #pragma omp section
        {
          if(a[mid]<key){
            low = mid+1;
          }
        }
        #pragma omp section
        {
          if(a[mid]>key){
            high = mid-1;
          }
        }
      }
    }
  }
  return loc;
}

int seqBinarySearch(int arr[], int low, int high, int key)
{
    int mid;
    int loc=-1;
    while(low <= high)
    {
        mid = (low+high)/2;
        if(arr[mid]==key) {
          loc = mid;
          break;
        }
        else {
          if(arr[mid]<key)
            low = mid+1;
          if(arr[mid]>key)
            high = mid-1;
        }
    }
    return loc;
}

int main(){
  double start,end;
  int key =8451274;
  int loc;
  for (int i = 0; i < N; i++) {
    a[i] = i;
  }
  
  start = omp_get_wtime();
  loc = parBinarySearch(a,0,N,key);
  end = omp_get_wtime();
  if (loc == -1) {
    cout<<"Not Found";
  } else {
    cout<<"Found at index = "<<loc<<endl;
  }
  cout<<"The time taken for Parallel Binary Search : "<<(end-start)<<endl;
  cout<<endl;

  double starts,ends;
  starts = omp_get_wtime();
  int idx = seqBinarySearch(a,0,N,key);
  ends = omp_get_wtime();
  if (idx == -1) {
    cout<<"Not Found";
  } else {
    cout<<"Found at index = "<<idx<<endl;
  }
  cout<<"The time taken for Serial Binary Search : "<<(ends-starts)<<endl;
  cout<<endl;

  return 0 ;
}