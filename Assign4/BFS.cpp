#include <iostream>
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<list>
#include<vector>

using namespace std;

list<int>q;
vector<int>w(7,1000);
int visited[7];

list<int>pq;
vector<int>pw(7,1000);
int pvisited[7];

struct Comp
{
    // Compare 2 Player objects using name
    bool operator ()(const int & a, const int & b)
    {
        return w[a]<w[b];
    }
};

void bfs(int adj_matrix[7][7],  int n_nodes)
{
	if(q.empty())
		return;
    q.sort(Comp());
    int cur_node = q.front();
    q.pop_front();
	
	printf("%d, ", cur_node);
	omp_set_num_threads(6);
	#pragma omp parallel for shared(visited)
	for(int i=0; i<n_nodes; i++)
	{
		if(adj_matrix[cur_node][i]>0 && visited[i]==0)
		{
    	    if(w[i] > adj_matrix[cur_node][i]){
            	w[i] = adj_matrix[cur_node][i];
        	}
			q.push_back(i);
			visited[i]=1;
		}
	}
	bfs(adj_matrix,  n_nodes);
}

void serialbfs(int adj_matrix[7][7],  int n_nodes)
{
	if(pq.empty())
		return;
    pq.sort(Comp());
    int cur_node = pq.front();
    pq.pop_front();
	
	printf("%d, ", cur_node);
	for(int i=0; i<n_nodes; i++)
	{
		if(adj_matrix[cur_node][i]>0 && pvisited[i]==0)
		{
    	    if(pw[i] > adj_matrix[cur_node][i]){
        	    pw[i] = adj_matrix[cur_node][i];
        	}
			pq.push_back(i);
			pvisited[i]=1;
		}
	}
	serialbfs(adj_matrix,  n_nodes);
}

int main()
{
  	int th = omp_get_max_threads();
  	cout<<"Max Threads : "<<th<<endl;
  	double start,end;
	int n_nodes = 7;
	for(int i=0; i<n_nodes; i++)
	{
		visited[i] = 0;
		pvisited[i] = 0;
	}
	int adj_matrix[7][7] = {
							{0,  10  ,20  ,0  ,0  ,0  ,0},
							{10	,0	,30	,30	,0	,0	,0},
							{20	,30	,0	,0	,40	,0	,0},
							{0	,30	,0	,0	,20	,0	,0},
							{0	,0	,40	,20	,0	,10	,0},
							{0	,0	,0	,0	,10	,0	,20},
							{0	,0	,0	,0	,0	,20	,0}
							};

	int start_node = 3;
	q.push_back(start_node);
    w[start_node] = 0;
	visited[start_node] = 1;
	start = omp_get_wtime();
	bfs(adj_matrix,  n_nodes);
	end = omp_get_wtime();
	cout<<"\nThe time taken for Parallel Best First Search : "<<(end-start)<<endl;
  	cout<<endl;

  	pq.push_back(3);
  	pw[3] = 0;
  	pvisited[3] = 1;
  	start = omp_get_wtime();
	serialbfs(adj_matrix,  n_nodes);
	end = omp_get_wtime();
	cout<<"\nThe time taken for Serial Best First Search : "<<(end-start)<<endl;
  	cout<<endl;
	return 0;
}