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
    size_t src, dest;
};

// Klasse die einen Graphen representiert
class Graph:public QObject
{
    Q_OBJECT

    bool GERICHTET = false;

    //Konstruiere einen Verktor mit double-paaren um die Koordinaten zu speichern
    vector<pair<double,double>> _coordList;

    //Anzahl der Knoten in dem Graph;
    size_t _numNodes = 0;

    //Anzahl der Kanten im Graph - evtl unnötig;
    size_t _numEdges = 0;

    //vector of edges for the eulercircle
    vector<Edge> eulerPath;

    // Vector von vectoren von ints - die Adjazenzliste
    vector<vector<int>> adjList;

    // Kopie der Adjazenzliste welche später im Algorithmus modifiziert wird
    vector<vector<int>> adjList_Algo;

    //Vector von bools um im Algo festzustellen, ob alle Knoten besucht wurden (evtl mehr als eine ZHK)
    vector<bool> _besucht;

public:
    int edgeToColor = -1;

    //Standard Konstruktor
    Graph(QObject* parent){}

    // Graph Kontruktor
    Graph(vector<Edge> const &edges, size_t N, vector<pair<double,double>> coordList, bool gerichtet = 0)
        : GERICHTET(gerichtet)
        , _coordList(coordList)
        , _numNodes(N)
    {
        // ändere Größe von der adjazenzliste
        adjList.resize(N);

        // Füge die kanten hinzu
        for (auto &edge: edges)
            addEdge(edge.src,edge.dest);
    }

    //Hier sollen 2 Indizes gespeichert werden von zu verbindenden Knoten
    int toConnect[2] = {-1,-1} ;

    // Graph Konsturktor zum laden mit Datei
    // Initialisierungskonstruktor von Datei
    Graph( string const& dateiName, bool gerichtet = false );

//Methoden

    //Soll den eulerPfad wieder löschen, wenn der Graph seit dem letzten durchlauf des Algos
    //wieder geändert wurde
    void resetPath()
    {
        eulerPath.clear();
        edgeToColor = -1;
    }

    //Algo zur bestimmung ob es sich um einen Eulerkreis handelt
    //gibt einen Vector mit den Indizes der Knoten wieder, so wie der Algo von Fleury es bestimmt hat
    //Wenn es kein Eulerkreis ist, dann ist der erste Eintrag vom vector = -1 als Signalwert
    vector<int> pruefeEulerKreis() const;

    //Liefert constante referenz auf den vector mit den Kanten für den EulerPfad.
    std::vector<Edge>const & getPath()const
    {
        return eulerPath;
    }

    //Liefert den Grad des Knotens mit index i
    int getDegree(size_t i);

    //gibt für debugginzwecke die nummer der edges aus
    size_t getNumEdges()
    {
        return _numEdges;
    }

    //Liefert vektor mit den indizes Knoten die mit i per Kante verbunden sind.
    vector<int> getEdges(size_t i) const
    {
        if (/*i<0 || */i > _numNodes)
            qDebug()<< "Fehler bei getEdges()";
        return adjList[i];
    }

    //Die ind der Animation zu färbende Kante wird geändert
    void newEdgeToColor()
    {
        emit(graphChanged());
        edgeToColor++;

        if(edgeToColor == int(eulerPath.size()))
            edgeToColor -= eulerPath.size();

        ////qDebug()<< "In newEdgetoColor";
        ////edgeToColor= (edgeToColor+1)%3;
    }

    //Schreibe den Graphen in eine Datei
    //Es wird davon ausgegangen, dass die Datei erstellt/ überschrieben werden darf
    void writeToFile(string const& dateiName);

    //Überschreibt den aktuellen Graphen mit dem der in der übergebenen Datei gespeichert ist.
    //Es wird davon ausgegangen, dass der aktuelle Graph überschrieben werden darf
    void readFromFile(string const& dateiName);

    //füge neuen KNoten mit (x,y) Koordinaten hinzu
    void addNode(double x, double y);

    //entferne den Knoten mit der Nummer index
    void removeNode(size_t index);

    //Entfernt eine Kante - wird nur im Algo benutzt
    void rmvEdgeAlgo(size_t src, size_t dest);

    //Entfernt eine Kante
    void rmvEdge(size_t src, size_t dest);

    //füge Kante zwischen src und dest hinzu, löscht Kante, falls sie Bereits existiert
    void addEdge(size_t src, size_t dest);

    //wue addEdge(), bloß ohne das Löschen
    //Wird nur in der Funktion "ReadFromFile" benutzt
    void addEdgeReadFromFile(size_t src, size_t dest);

    //füge Kante zwischen src und dest hinzu, operiert auf der Kopie der Adjazenzliste und wird nur im Algo benutzt
    void addEdge_Algo(size_t src, size_t dest)
    {
        if((max(src,dest) >= _numNodes) )
        {
            adjList_Algo[src].push_back(int(dest));
            if(!GERICHTET)
                adjList_Algo[dest].push_back(int(src));
        }
        else
            qDebug()<< "addedge_Algo hat ungültge Parameter bekommen";
    }

    //gib Anzahl der Knoten
    size_t getSize() const
    {
        return _numNodes;
    }

    //gib die koordinaten zu dem i-ten Knoten
    pair<double,double> getCoord(size_t i) const
    {
        return _coordList[i];
    }

    //verschiebt den Knoten mit der Nummer "index" (sofern er existiert)
    //nach (X,Y)
    void moveNodeTo(size_t index, double X, double Y);

    //Liefert den Index des Knotens der an den übergebenen Koordinaten liegt
    //Dafür wird für jeden Knoten geprüft, ob die übergebenen Koordinaten (_x,_y) in dem Kreis
    //mit Radius "nodeRadius" um den Mittelpunkt des Knotens (x,y) liegt
    //Es wird der index des "geklickten" Knotens zurückgegeben
    //Wird keiner gefunden wird "-1" als SIgnalwert zurückgegeben
    int clickedOnNode(double _x, double _y, double nodeRadius = 0.03);

    // Methoden zur Ausgabe des Eulerwegs
    bool printEulerWeg();
    void printEulerUtil(int u);

    // Zähle die von v erreichbaren Knoten mit Tiefensuche
    size_t Tiefensuche(size_t v, vector<bool>& besucht);

    // Finde heraus ob src-dest eine gültige nächste Kante ist
    bool gueltigeNaechsteKante(size_t src, size_t dest);

    vector<Edge> const& getPath()
    {
        return eulerPath;
    }

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
