#ifndef GRAPH_H
#define GRAPH_H


#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <fstream>
#include <QString>
#include <QDebug>

#include <QObject>
using namespace std;

//Datenstruktur für die Kanten
struct Edge {
    int src, dest;
};

// Klasse die einen Graphen representiert
class Graph:public QObject
{
    Q_OBJECT

    bool GERICHTET = false;


    //Kontruiere einen Verktor mit double-paaren um die Koordinaten zu speichern
    vector<pair<double,double>> _coordList;

    //Anzahl der Knoten in dem Graph;
    int _numNodes=0;

    //Anzahl der Kanten im Graph - evtl unnötig;
    int _numEdges=0;

    // Vector von vectoren von ints - die Adjazenzliste
    vector<vector<int>> adjList;

    // Kopie der Adjazenzliste welche später im Algorithmus modifiziert wird
    vector<vector<int>> adjList_Algo;

public:



    //Standard Konstruktor
    Graph(QObject* parent)
    {

    }

    // Graph Kontruktor
    Graph(vector<Edge> const &edges, int N,vector<pair<double,double>> coordList,bool gerichtet = 0)
    :_coordList(coordList),_numNodes(N),GERICHTET(gerichtet)
    {
        // ändere Größe von der adjazenzliste
        adjList.resize(N);

        // Füge die kanten hinzu
        for (auto &edge: edges)
            addEdge(edge.src,edge.dest);
    }

    //Hier sollen 2 Indizes gespeichert werden von zu verbindenden KNoten
    int toConnect[2] = {-1,-1} ;

    //Graph Konsturktor zum laden mit Datei
    // Initialisierungskonstruktor von Datei
Graph( string const& dateiName, bool gerichtet = false );  // Graph::Graph()





//Methoden

    //Algo zur bestimmung ob es sich um einen Eulerkreis handelt
    //gibt einen Vector mit den Indizes der Knoten wieder, so wie der Algo von Fleury es bestimmt hat
    //Wenn es kein Eulerkreis ist, dann ist der erste Eintrag vom vector = -1 als Signalwert
    vector<int> pruefeEulerKreis() const;

    //Liefert den Grad des Knotens mit index i
    int getDegree(int i);

    //gibt für debugginzwecke die nummer der edges aus
    int getNumEdges()
    {
        return _numEdges;
    }
    //Liefert vektor mit den indizes Knoten die mit i per Kante verbunden sind.
    vector<int> getEdges(int i) const
    {
        if (i<0|| i> _numNodes)
            qDebug()<< "Fehler bei getEdges()";
        return adjList[i];
    }

    //Schreibe den Graphen in eine Datei
    //Es wird davon ausgegangen, dass die Datei erstellt/ überschrieben werden darf
    void writeToFile(string const& dateiName);

    //Überschreibt den aktuellen Graphen mit dem der in der übergebenen Datei gespeichert ist.
    //Es wird davon ausgegangen, dass der aktuelle Graph überschrieben werden darf
    void readFromFile(string const& dateiName);

    //füge neuen KNoten mit (x,y) Koordinaten hinzu
    int addNode(double x, double y);

    //entferne den Knoten mit der Nummer index
    int removeNode(int index);

    //Entfernt eine Kante - wird nur im Algo benutzt
    void rmvEdge(int src, int dest);

    //füge Kante zwischen src und dest hinzu
    void addEdge(int src, int dest);

    //füge Kante zwischen src und dest hinzu, operiert auf der Kopie der Adjazenzliste und wird nur im Algo benutzt
    void addEdge_Algo(int src, int dest)
    {
        if(!((src <0 || dest< 0)
                ||(abs(max(src,dest))>=_numNodes) ))
        {
        adjList_Algo[src].push_back(dest);
        if(!GERICHTET)
            adjList_Algo[dest].push_back(src);
        }
        else
            qDebug()<< "addedge_Algo hat ungültge Parameter bekommen";
    }

    //gib Anzahl der Knoten
    int getSize() const
    {
        return _numNodes;
    }

    //gib die koordinaten zu dem i-ten Knoten
    pair<double,double> getCoord(int i) const
    {
        if (i >= _numNodes || i<0)
           qDebug() << "Fehler bei get Coord, denn i="<<i<<" >= _numNodes="<<_numNodes  ;
        //qDebug() << _numEdges << " " << i;
        else
            return _coordList[i];
    }

    //verschiebt den Knoten mit der Nummer "index" (sofern er existiert)
    //nach (X,Y)
    void moveNodeTo(int index, double X, double Y);




    //Liefert den Index des Knotens der an den übergebenen Koordinaten liegt
    //Dafür wird für jeden Knoten geprüft, ob die übergebenen Koordinaten (_x,_y) in dem Kreis
    //mit Radius "nodeRadius" um den Mittelpunkt des Knotens (x,y) liegt
    //Es wird der index des "geklickten" Knotens zurückgegeben
    //Wird keiner gefunden wird "-1" als SIgnalwert zurückgegeben
    int clickedOnNode(double _x, double _y, double nodeRadius = 0.03);


    // Methoden zur Ausgabe des Eulerwegs
      void printEulerWeg();
      void printEulerUtil(int u);

      // Zähle die von v erreichbaren Knoten mit Tiefensuche
      int Tiefensuche(int v, vector<bool>& besucht);

      // Finde heraus ob src-dest eine gültige nächste Kante ist
      bool gueltigeNaechsteKante(int src, int dest);



// gebe die Anjazenzliste des Graphen aus
    void printGraph();

// leere Modell
    void clear();


    // gebe die Anjazenzliste des Graphen im Algo aus
        void printGraphAlgo();

signals:
    void graphChanged(); // Dieses Signal wird immer dann gesendet (durch einen Funktionsaufruf in der Klasse), wenn sich die Daten geändert haben
    // dies kann sicher bestimmt werden, da die Daten privat, also gekapselt sind. Ein schreibener Zugriff erfolgt also ausschließlich durch die Methoden.

};

#endif // GRAPH_H
