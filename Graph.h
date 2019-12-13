#ifndef GRAPH_H
#define GRAPH_H


#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <fstream>

#include <QObject>
using namespace std;

// data structure to store graph edges
struct Edge {
    int src, dest;
};

// class to represent a graph object
class Graph:public QObject
{
    Q_OBJECT

    bool GERICHTET;
    // construct a vector of vectors to represent an adjacency list
    vector<vector<int>> adjList;

    // construct a vector of pairs of doubles to save the coordinates of the nodes;
    vector<pair<double,double>> _coordList;

    //Number of Nodes in the graph;
    size_t _numNodes=0;

    //Number of Edges in the graph;
    size_t _numEdges=0;
public:


    //Standard Konstruktor
    Graph()
    {

    }

    // Graph Kontruktor
    Graph(vector<Edge> const &edges, int N,vector<pair<double,double>> coordList,bool gerichtet = 0)
    :_coordList(coordList),_numNodes(N),GERICHTET(gerichtet)
    {
        // resize the vector to N elements of type vector<int>
        adjList.resize(N);

        // add edges to the directed graph
        for (auto &edge: edges)
            addEdge(edge.src,edge.dest);
    }


    //Graph Konsturktor zum laden mit Datei
    // Initialisierungskonstruktor von Datei
Graph( string const& dateiName, bool gerichtet = false )
:GERICHTET(gerichtet)
{
    ifstream fin( dateiName.c_str() ) ;

    if ( ! fin )
        throw "Graph::Graph(): Datei kann nicht geoeffnet werden!" ;

/***  lese Graphparameter aus  ***/

    size_t nKnoten, nKanten ;
    string dummy ;				// zum Lesen und Ignorieren

    fin >> nKnoten ;
    getline( fin, dummy ) ;		// ignoriere Rest der Zeile
    fin >> nKanten ;
    getline( fin, dummy ) ;		// ignoriere Rest der Zeile

    _coordList.resize( nKnoten ) ;
    adjList.resize( nKnoten ) ;

    _numNodes=nKnoten;
    _numEdges=nKanten;
/***  lese Knoten aus  ***/

    for ( size_t i = 0 ;  i < nKnoten ;  ++i )
    {
        double x,y;
        fin >> x ;
        fin >> y ;
        _coordList[i]=make_pair(x,y);
        getline( fin, dummy ) ;		// ignoriere Rest der Zeile
    }


/***  lese Kanten aus  ***/
    cout << "nKanten = "<<nKanten<<endl;
    for ( size_t i = 0 ;  i < nKanten ;  ++i )
    {
        string fuss, kopf;
        fin >> fuss >> kopf ;

        int src = stoi(fuss);
        int dest= stoi(kopf);

        //Füge Kante hinzu
        addEdge(src,dest);
    }  // for ( i )

    fin.close() ;

}  // Graph::Graph()





//Methoden

    //Liefert vektor mit den indizes Knoten die mit i per Kante verbunden sind.
    vector<int> getEdges(int i);

    bool writeToFile(string const& dateiName)
    {
        ofstream fout( dateiName.c_str() ) ;
        fout << _numNodes<<endl;

        fout << _numEdges<<endl;

        //Koordinaten der Knoten
        for(int i = 0; i < _numNodes;i++)
        {
            fout << _coordList[i].first << " ";
            fout << _coordList[i].second << endl;
        }

        //Kanten
        for(int i = 0; i < _numNodes;i++)
        {
            // print all neighboring vertices of vertex i
            for (int v : adjList[i])
                fout << v << " ";
            fout << endl;
        }
        fout.close();
    }

    //füge neuen KNoten mit (x,y) Koordinaten hinzu
    bool addNode(double x, double y)
    {
    _numNodes++;
    adjList.resize(_numNodes);
    _coordList.push_back(make_pair(x,y));
    cout << "Knoten erstellt bei: " << x << "  " << y << endl;
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
        _numEdges++;

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


    //Liefert den Index des Knotens der an den übergebenen Koordinaten liegt
    //Dafür wird für jeden Knoten geprüft, ob die übergebenen Koordinaten (_x,_y) in dem Kreis
    //mit Radius "nodeRadius" um den Mittelpunkt des Knotens (x,y) liegt
    //Es wird der index des "geklickten" Knotens zurückgegeben
    //Wird keiner gefunden wird "-1" als SIgnalwert zurückgegeben
    int clickedOnNode(double _x, double _y, double nodeRadius = 0.01)
    {
        for(int index= 0;index< _numNodes;index++)
        {
            double x = _coordList[index].first;
            double y = _coordList[index].second;

            //liegt übergebener Punkt im Kreis?
            if( pow((_x-x),2) + pow((_y-y),2) < pow(nodeRadius,2) )
                return index;
        }
        return -1;
    }



// print adjacency list representation of graph
    void printGraph()
    {
        int N = getSize();
        for (int i = 0; i < N; i++)
        {
            // print current vertex number
            cout << i << " --> ";

            // print all neighboring vertices of vertex i
            for (int v : adjList[i])
                cout << v << " ";
            cout << setfill('_');

            //print coordinates

            cout <<  setw(7)<< "x= " <<  getCoord(i).first << setw(10)<<"y= " << getCoord(i).second;
            cout <<endl;
        }
    }


signals:
    void graphChanged(); // Dieses Signal wird immer dann gesendet (durch einen Funktionsaufruf in der Klasse), wenn sich die Daten geändert haben
    // dies kann sicher bestimmt werden, da die Daten privat, also gekapselt sind. Ein schreibener Zugriff erfolgt also ausschließlich durch die Methoden.

};

#endif // GRAPH_H


/*
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
    cout<< "graph1" << endl;
    graph.printGraph();


    // print adjacency list representation of graph


    //write Graph to file
    graph.writeToFile("test.txt");

    //construct Graph from file
    Graph graph2("test.txt");
    cout << "graph2" << endl;
    graph2.printGraph();
    return 0;
}
*/
