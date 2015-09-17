#include "Graph.h"
#include <iostream>

MatrixWDigraph graph;

int main(void)
{
	for(int i=0; i<=5; ++i)
		graph.InsertVertex();
	graph.InsertEdge(0,1,50);
	graph.InsertEdge(0,2,45);
	graph.InsertEdge(0,3,10);
	graph.InsertEdge(1,2,10);
	graph.InsertEdge(1,3,15);
	graph.InsertEdge(2,4,30);
	graph.InsertEdge(3,0,20);
	graph.InsertEdge(3,4,15);
	graph.InsertEdge(4,1,20);
	graph.InsertEdge(4,2,35);
	graph.InsertEdge(5,4,3);

	//for(int i=0; i<4; ++i)
	//	graph.InsertVertex();
	//graph.InsertEdge(0,1,10);
	//graph.InsertEdge(1,2,10);
	//graph.InsertEdge(0,3,30);

	int buffer[10];

	int start=-1, target=-1;
	do
	{
		cout << "start, target : ";
		cin >> start >> target;
	}while(start<0 && start>=graph.NumberOfVertices() && target<0 && target>=graph.NumberOfVertices());
	cout << "cost : " << graph.ShortestPath(start,target,buffer) << endl << "path : ";
	for(int i=0; i<10&&buffer[i]>=0; ++i)
		cout << buffer[i] << ' ';

	system("pause");
	return 0;
}