#include <iostream>
using namespace std;
#ifndef __GRAPH__
#define __GRAPH__

#define LARGE 50000

class Graph
{
protected:
	int n; //버텍스 수
	int e; //엣지 수
public:
	Graph();
	virtual ~Graph();
	bool IsEmpty() const;
	int NumberOfVertices() const;
	int NumberOfEdges() const;
	virtual int Degree(int u) const=0;
	virtual bool ExistsEdge(int u, int v) const = 0;
//	virtual void InsertVertex(int v) = 0;
//	virtual void InsertEdge(int u, int v) = 0;
	virtual void DeleteVertex(int v) = 0;
	virtual void DeleteEdge(int u, int v) = 0;
};
Graph::Graph() : n(0), e(0)
{
}
Graph::~Graph()
{
}
bool Graph::IsEmpty() const
{
	return n==0;
}
int Graph::NumberOfVertices() const
{
	return n;
}
int Graph::NumberOfEdges() const
{
	return e;
}


class MatrixWDigraph : public Graph
{
private:
	int** length;
	int* dist;
	bool* s;
public:
	MatrixWDigraph();
	virtual ~MatrixWDigraph();
	virtual int Degree(int u) const;
	virtual bool ExistsEdge(int u, int v) const;
	virtual void InsertVertex();
	virtual void InsertEdge(int u, int v, int weight);
	virtual void DeleteVertex(int v);
	virtual void DeleteEdge(int u, int v);

	int Choose();
	int ShortestPath(const int u, const int v, int* buffer);
};

MatrixWDigraph::MatrixWDigraph()
{
	n = 0;
	e = 0;
}
MatrixWDigraph::~MatrixWDigraph()
{
	delete []length;
	delete dist;
	delete s;
}
int MatrixWDigraph::Degree(int u) const
{
	int deg=0;
	for(int i=0; i<n; ++i)
		if(length[i][u] || length[u][i])
			deg++;

	return deg;
}
bool MatrixWDigraph::ExistsEdge(int u, int v) const
{
	return length[u][v]>0;
}
void MatrixWDigraph::InsertVertex()
{
	int** temp = new int*[++n];
	for(int i=0; i<n-1; ++i)
	{
		temp[i] = new int[n];
		for(int j=0; j<n-1; ++j)
			temp[i][j] = length[i][j];
	}
	temp[n-1] = new int[n];
	for(int i=0; i<n; ++i)
	{
		temp[i][n-1] = LARGE;
		temp[n-1][i] = LARGE;
	}

	delete[] length;
	length = temp;
}
void MatrixWDigraph::InsertEdge(int u, int v, int weight)
{
	length[u][v] = weight;
	e++;
}
void MatrixWDigraph::DeleteVertex(int v)
{
	if(v>n || v<0)
		return;

	int** temp = (int**)(new int[(n-1)*(n-1)]);
	for(int i=0; i<v; i++)
	{
		for(int j=0; j<v; j++)
			temp[i][j] = length[i][j];
		for(int j=v+1; j<n; j++)
			temp[i][j] = length[i][j];
	}
	for(int i=v+1; i<n; i++)
	{
		for(int j=0; j<v; j++)
			temp[i][j] = length[i][j];
		for(int j=v+1; j<n; j++)
			temp[i][j] = length[i][j];
	}

	delete length;
	length = temp;
}
void MatrixWDigraph::DeleteEdge(int u, int v)
{
	length[u][v] = LARGE;
}
int MatrixWDigraph::Choose()
{
	int min=LARGE;
	int minIdx=0;
	for(int i=0; i<n; ++i)
	{
		if(!s[i] && dist[i]<min)
		{
			min = dist[i];
			minIdx = i;
		}
	}
	return minIdx;
}
int MatrixWDigraph::ShortestPath(const int beg, const int end, int* buffer)
{
	//초기화
	delete s;
	delete dist;
	s = new bool[n];
	dist = new int[n];
	int* prev = new int[n]; // vertex n의 바로 직전 vertex를 저장
	for(int i=0; i<n; i++)
	{
		s[i] = false;
		dist[i] = length[beg][i];
		prev[i] = beg;
	}
	s[beg] = true;
	dist[beg] = 0;

	for(int i=0; i<n-2; i++)
	{
		int u = Choose();
		s[u] = true;

		for(int w=0; w<n;w++)
			if(!s[w] && dist[u]+length[u][w] < dist[w])
			{
				dist[w] = dist[u] + length[u][w];
				prev[w] = u;
			}
	}
	
	//경로를 buffer에 저장
	int curr=end;
	int i=1;
	buffer[0] = end;
	while(curr != beg)
	{
		buffer[i++] = prev[curr];
		curr = prev[curr];
	}
	for(int j=0; j<i/2; ++j)
	{
		int temp = buffer[i-1-j];
		buffer[i-1-j] = buffer[j];
		buffer[j] = temp;
	}
	buffer[i] = -1;

	delete prev;
	return dist[end];
}
#endif