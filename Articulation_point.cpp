#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int graph[10000][10000];

void dfs(int n ,int src ,int &timer ,int visited[] ,int point[] ,int low[] ,int discovary[] ,int parent[])
{
	visited[src] = 1;
	low[src] =  timer;
	discovary[src] = timer;
	timer++;

	int c = 0;

	for(int i=0 ;i<n ;i++)
	{
		if( visited[i] == 0 && graph[src][i] == 1 )
		{
			c++;

			parent[i] = src;

			dfs(n,i,timer,visited,point,low,discovary,parent);

			low[src] = min(low[src],low[i]);

			if( (parent[src] == -1 && c>1) || (parent[src] != -1 && low[i] >= discovary[src]) )
			{
				point[src] = 1;
			}
		}
		else 
		{
			if( graph[src][i] == 1 && i!=parent[src] )
			{
				low[src] = min(low[src] ,discovary[i]);
			}
		}	

	}
}

void dfs_main(int n)
{
	int visited[n] = {0};
	int parent[n] = {0};

	for(int i=0 ;i<n ;i++)
	{
		parent[i] = -1;
	}

	int point[n] = {0};
	int low[n] = {0};
	int discovary[n] = {0};
	int timer = 0;

	for(int i=0 ;i<n ;i++)
	{
		if( visited[i] == 0 )
		{
			dfs(n ,i ,timer ,visited ,point ,low ,discovary ,parent);
		}
	}

	cout<<"Points"<<endl;

	for(int i=0 ;i<n ;i++)
	{
		if( point[i] == 1 )
		{
			cout<<i<<" ";
		}
	}

}

main()
{
	cout<<"Node :";
	int n;
	cin>>n;

	cout<<endl<<"Edges :";
	int e;
	cin>>e;

	for(int i=0 ;i<n ;i++)
	{
		for(int j=0 ;j<n ;j++)
		{
			graph[i][j] = 0;

		}
	}

	for(int i=0 ;i<e ;i++)
	{
		int src ,des;
		cin>>src>>des;

		graph[src][des] = 1;
		graph[des][src] = 1;
	}

	dfs_main(n);
}