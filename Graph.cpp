#include "Graph.h"
#include <QDebug>

Graph::Graph(const string &dateiName, bool gerichtet)
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

}

bool Graph::writeToFile(const string &dateiName)
{
    //TODO:
    //Evtl Prüfen, ob damit etwas überschrieben wird
    //qDebug() << "write to file, jetzt printgraph";
    //printGraph();
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

    return true;
}

bool Graph::addNode(double x, double y)
{
    _numNodes++;
    adjList.resize(_numNodes);
    _coordList.push_back(make_pair(x,y));
    emit(graphChanged());
    return true;
}

bool Graph::removeNode(size_t index)
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
    emit(graphChanged());


    return true;
}

bool Graph::addEdge(size_t src, size_t dest)
{
    //prüfe ob KNoten vorhanden sind
    if (max(src,dest) > _numNodes
            || src == dest)
        return false;


    adjList[src].push_back(dest);
    _numEdges++;

    if (!GERICHTET)
        adjList[dest].push_back(src);
    emit(graphChanged());

    return true;
}

bool Graph::moveNodeTo(size_t index, double X, double Y)
{
    if (index >= _numNodes)
        return false;
    _coordList[index].first =X;
    _coordList[index].second=Y;
    emit(graphChanged());

    return true;
}


int Graph::clickedOnNode(double _x, double _y, double nodeRadius)
{
   // qDebug() << "clickedOnNode" << _x << " " << _y << endl;
    for(int index= 0;index< _numNodes;index++)
    {
        double x = _coordList[index].first;
        double y = _coordList[index].second;
        //qDebug() << x << " " << y << endl;
        //liegt übergebener Punkt im Kreis?
        if( pow((_x-x),2) + pow((_y-y),2) < pow(nodeRadius,2) )
        {
         //                                                                                                                                             qDebug() << "gefunden";
            return index;
        }
    }
    return -1;
}

void Graph::printGraph()
{
    int N = getSize();
    for (int i = 0; i < N; i++)
    {
        // print current vertex number
        qDebug() << i << " --> ";

        // print all neighboring vertices of vertex i
        for (int v : adjList[i])
            qDebug() << v << " ";


        //print coordinates

        qDebug() <<  "x= " <<  getCoord(i).first <<"y= " << getCoord(i).second;
        qDebug() <<endl;
    }
}
