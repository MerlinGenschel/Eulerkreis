#ifndef GRAPH_H
#define GRAPH_H


#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <fstream>
#include <QString>

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


    // construct a vector of pairs of doubles to save the coordinates of the nodes;
    vector<pair<double,double>> _coordList;

    //Number of Nodes in the graph;
    size_t _numNodes=0;

    //Number of Edges in the graph;
    size_t _numEdges=0;

    // construct a vector of vectors to represent an adjacency list
    vector<vector<int>> adjList;

public:



    //Standard Konstruktor
    Graph(QObject* parent)
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
Graph( string const& dateiName, bool gerichtet = false );  // Graph::Graph()





//Methoden

    //Algo zur bestimmung ob es sich um einen Eulerkreis handelt
    //gibt einen Vector mit den Indizes der Knoten wieder, so wie der Algo von Fleury es bestimmt hat
    //Wenn es kein Eulerkreis ist, dann ist der erste Eintrag vom vector = -1 als Signalwert
    vector<int> pruefeEulerKreis() const;



    //Liefert vektor mit den indizes Knoten die mit i per Kante verbunden sind.
    vector<int> getEdges(size_t i) const
    {
        vector<int> edges = adjList[i];
        return edges;
    }

    bool writeToFile(string const& dateiName);

    bool readFromFile(string const& dateiName);

    //füge neuen KNoten mit (x,y) Koordinaten hinzu
    bool addNode(double x, double y);

    //entferne den Knoten mit der Nummer index
    bool removeNode(size_t index);


    //füge Kante zwischen src und dest hinzu
    bool addEdge(size_t src, size_t dest);

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
    //nach (X,Y)
    bool moveNodeTo(size_t index, double X, double Y);




    //Liefert den Index des Knotens der an den übergebenen Koordinaten liegt
    //Dafür wird für jeden Knoten geprüft, ob die übergebenen Koordinaten (_x,_y) in dem Kreis
    //mit Radius "nodeRadius" um den Mittelpunkt des Knotens (x,y) liegt
    //Es wird der index des "geklickten" Knotens zurückgegeben
    //Wird keiner gefunden wird "-1" als SIgnalwert zurückgegeben
    int clickedOnNode(double _x, double _y, double nodeRadius = 0.01);



// print adjacency list representation of graph
    void printGraph();


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
