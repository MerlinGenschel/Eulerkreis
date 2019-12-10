#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// data structure to store graph edges
struct Edge {
	int src, dest;
};

// class to represent a graph object
class Graph
{
public:
	bool GERICHTET;
	// construct a vector of vectors to represent an adjacency list
	vector<vector<int>> adjList;

	// construct a vector of pairs of doubles to save the coordinates of the nodes;
	vector<pair<double,double>> _coordList;

	//Number of Nodes in the graph;
	size_t _numNodes;

	// Graph Kontruktor
	Graph(vector<Edge> const &edges, int N,vector<pair<double,double>> coordList,bool gerichtet = 0)
	:_coordList(coordList),_numNodes(N),GERICHTET(gerichtet)
	{
		// resize the vector to N elements of type vector<int>
		adjList.resize(N);

		// add edges to the directed graph
		for (auto &edge: edges)
		{
			// insert at the end
			adjList[edge.src].push_back(edge.dest);

			if(!GERICHTET)
				adjList[edge.dest].push_back(edge.src);
		}
	}




	//Methoden


	//füge neuen KNoten mit (x,y) Koordinaten hinzu
	bool addNode(double x, double y)
	{
	_numNodes++;
	adjList.resize(_numNodes);
	_coordList.push_back(make_pair(x,y));

	return true;
	}

	//entferne den Knoten mit der Nummer index
	bool removeNode(size_t index)
	{
		if (index > _numNodes || index < 0)
			return false;

		//prüfe ob es eingehende Kanten gibt
		for (int i = 0; i < _numNodes;i++)
			for (int k= adjList[i].size()-1; k>=0;k--)
			{
				if(adjList[i][k]==index)
					adjList[i].erase(adjList[i].begin()+k);

				//nachrücken
				if(adjList[i][k]>index)
					adjList[i][k]--;
				//cout << adjList[i][k];
			}
		adjList.erase(adjList.begin()+index);
		_coordList.erase(_coordList.begin()+index);
		_numNodes--;


		return true;
	}


	//füge Kante zwischen src und dest hinzu
	bool addEdge(size_t src, size_t dest)
	{
		//prüfe ob KNoten vorhanden sind
		if (max(src,dest) > _numNodes)
			return false;

		adjList[src].push_back(dest);

		if (!GERICHTET)
			adjList[dest].push_back(src);
		return true;
	}

	//gib Anzahl der Knoten
	int getSize() const
	{
		return adjList.size();
	}

	//gib die koordinaten zu dem i-ten Knoten
	pair<double,double> getCoord(size_t i) const
	{
		return _coordList[i];
	}

	//verschiebt den Knoten mit der Nummer "index" (sofern er existiert)
	//um (deltaX,deltaY)
	bool moveNode(size_t index, double deltaX, double deltaY)
	{
		if (index >= _numNodes)
			return false;
		_coordList[index].first += deltaX;
		_coordList[index].second+= deltaY;
		return true;
	}

};




// print adjacency list representation of graph
void printGraph(Graph const& graph)
{
	int N = graph.getSize();
	for (int i = 0; i < N; i++)
	{
		// print current vertex number
		cout << i << " --> ";

		// print all neighboring vertices of vertex i
		for (int v : graph.adjList[i])
			cout << v << " ";
		cout << setfill('_');

		//print coordinates

		cout <<  setw(7)<< "x= " <<  graph.getCoord(i).first << setw(10)<<"y= " << graph.getCoord(i).second;
		cout <<endl;
	}
}

// Graph Implementation using STL
int main()
{
	// vector of graph edges as per above diagram.
	// Please note that initialization vector in below format will
	// work fine in C++11, C++14, C++17 but will fail in C++98.
	vector<Edge> edges =
	{
		{ 0, 1 }, { 1, 2 }, { 2, 0 }, 
		{ 3, 2 }, { 5, 4 }
	};

	//vector of pairs of doubles for the coordinates
	vector<pair<double,double>> coordList =
	{
		std::make_pair ( 0.245, 0.1 ),std::make_pair  ( 0.51, 0.42 ),
		std::make_pair ( 0.32, 0.73 ),std::make_pair  ( 0.32, 0.1 ),
		std::make_pair ( 0.63, 0.12 ),std::make_pair  ( 0.34, 0.75 )
	};

	// Number of nodes in the graph
	int N = 6;

	// construct graph
	Graph graph(edges,N,coordList,false);



	// print adjacency list representation of graph

	
	printGraph(graph);
	
	return 0;
}
