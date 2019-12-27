#include "Graph.h"
#include <QDebug>
#include <vector>
#include <sstream>
#include <string>

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

    for ( int i = 0 ;  i < nKnoten ;  ++i )
    {
        double x,y;
        fin >> x ;
        fin >> y ;
        _coordList.at(i)=make_pair(x,y);
        getline( fin, dummy ) ;		// ignoriere Rest der Zeile
    }


    /***  lese Kanten aus  ***/
    for ( int i = 0 ;  i < nKanten ;  ++i )
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

int Graph::getDegree(int i)
{
    if(i >= _numNodes || i < 0)
          return -1;
    //qDebug()<< "getdegree von" << i << " = "<<adjList.at(i).size();;


    return adjList.at(i).size();
}

void Graph::writeToFile(const string &dateiName)
{

    //TODO:: Evtl Noch auf gültigen Dateinamen prüfen etc
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
        // Schreibe die Nachbarkanten von Knoten i
        for (int v : adjList[i])
            fout << v << " ";
        fout << endl;
    }
    fout.close();

}

//Überschreibt den aktuellen Graphen mit dem der in der übergebenen Datei gespeichert ist.
//Es wird davon ausgegangen, dass der aktuelle Graph überschrieben werden darf
void Graph::readFromFile(const string &dateiName)
{ifstream fin( dateiName.c_str() ) ;
    qDebug()<< "readFromFole()";
    if ( ! fin )
        throw "Graph::Graph(): Datei kann nicht geoeffnet werden!" ;

    /***  lese Graphparameter aus  ***/

    size_t nKnoten, nKanten ;
    string dummy ;				// zum Lesen und Ignorieren

    fin >> nKnoten ;
    qDebug()<<"nKnoten= "<<nKnoten;
    getline( fin, dummy ) ;		// ignoriere Rest der Zeile
    fin >> nKanten ;
    qDebug()<<"nKanten= "<<nKanten;
    getline( fin, dummy ) ;		// ignoriere Rest der Zeile

    _coordList.clear();
    _coordList.resize( nKnoten ) ;
    adjList.resize( nKnoten ) ;

    _numNodes=nKnoten;
    _numEdges=0;
    /***  lese Knoten aus  ***/

    for ( int i = 0 ;  i < nKnoten ;  ++i )
    {
        double x,y;
        fin >> x ;
        fin >> y ;
        _coordList.at(i)=make_pair(x,y);
        getline( fin, dummy ) ;		// ignoriere Rest der Zeile
    }

    std::string line;

    /***  lese Kanten aus  ***/
    for ( int i = 0 ;  i < nKnoten ;  ++i )
    {
        std::getline(fin,line);
       std::istringstream iss(line);
        string desti;
        while(iss >> desti)
        {

        //Füge Kante hinzu
        addEdge(i,stoi(desti));
        qDebug()<<"addEdge("<<i<<","<<stoi(desti)<<")";

        }
    } // for ( i )


    fin.close() ;
}



void Graph::addNode(double x, double y)
{
    _numNodes++;
    adjList.resize(_numNodes);
    _coordList.push_back(make_pair(x,y));
    emit(graphChanged());

}
void Graph::removeNode(int index)
{
    //Prüfe, ob Index gültig ist
    if (!(index >= _numNodes) && index >= 0)
    {
    //eingehende Kanten?
    for (int i = 0; i < _numNodes;i++)
    {
        for(int j = int(getDegree(i))-1; j>= 0 ;j--)
         {
             if (adjList.at(i).at(j) == index)
             {
                 adjList.at(i).erase(adjList.at(i).begin()+j);
                 _numEdges--;
             }


           }

        //Schleife zum nachrücken
        for(int j = int(getDegree(i))-1; j>= 0 ;j--)
            if(adjList.at(i).at(j)>index)
        {
                adjList.at(i).at(j)--;
        }
        }
             //if(!GERICHTET)
             //    _numEdges -= adjList.at(index).size();

             //Lösche ausgehende Kanten
             _numEdges-= adjList[index].size();
             adjList.erase(adjList.begin()+index);
             //Lösche Knoten in der Koordinatenliste
             _coordList.erase(_coordList.begin()+index);
             _numNodes--;

    //Graph hat sich geändert
    emit(graphChanged());

    }
    else
        qDebug()<< "RemoveNode() hat ungültige index übergeben bekommen";
}


void Graph::rmvEdgeAlgo(int src, int dest)
{
    // Finde dest in Adjazenzliste von src und ersetze mit -1
     vector<int>::iterator idest = find(adjList_Algo[src].begin(), adjList_Algo[src].end(), dest);
     *idest = -1;

     if(!GERICHTET)
     {
        //  Finde src in Adjazenzliste von dest und ersetze mit -1
        vector<int>::iterator isrc = find(adjList_Algo[dest].begin(), adjList_Algo[dest].end(), src);
        *isrc = -1;
     }
}

void Graph::rmvEdge(int src, int dest)
{
    // Finde dest in Adjazenzliste von src und lösche
     vector<int>::iterator idest = find(adjList[src].begin(), adjList[src].end(), dest);
     if (idest !=adjList[src].end())
        adjList[src].erase(idest);

     if(!GERICHTET)
     {
        //  Finde src in Adjazenzliste von dest und lösche
        vector<int>::iterator isrc = find(adjList[dest].begin(), adjList[dest].end(), src);
        if (isrc !=adjList[dest].end())
            adjList[dest].erase(isrc);
     }
}

void Graph::addEdge(int src, int dest)
{
    //prüfe ob Knoten vorhanden sind
    if (!(max(src,dest) > _numNodes
            || src == dest))
    {
    //Prüfe ob Kante bereits vorhanden ist
    std::vector<int>::iterator it;
    it = std::find(adjList[src].begin(),adjList[src].end(),dest);

    if(it!=adjList[src].end() && *it == dest)
    {    qDebug()<< "schon drin, lösche kante" << src<<" "<<dest;
        rmvEdge(src,dest);
    }
    else
    {
    adjList.at(src).push_back(dest);
    _numEdges++;

    if (!GERICHTET)
    {
        //Prüfe ob Kante bereits vorhanden ist
        std::vector<int>::iterator it2;
        it2 = std::find(adjList[dest].begin(),adjList[dest].end(),src);

        if(it2!=adjList[dest].end() && *it2 == src)
         {
            qDebug()<< "schon drin(ungerichtet)";
            rmvEdge(dest,src);
        }
        else
        {    adjList.at(dest).push_back(src);
            _numEdges++;
        }
    }

    emit(graphChanged());
    }
    }
    else
        qDebug()<< "addEdge hat ungültige Parameter bekommen";
}

void Graph::moveNodeTo(int index, double X, double Y)
{
    if (!index >= _numNodes)
    {
    _coordList[index].first =X;
    _coordList[index].second=Y;
    emit(graphChanged());
    }
    else
        qDebug()<< "moveNodeTo hat ungültige Parameter bekommen";
}


int Graph::clickedOnNode(double _x, double _y, double nodeRadius)
{
    for(int index= 0;index< _numNodes;index++)
    {
        double x = _coordList.at(index).first;
        double y = _coordList.at(index).second;

        //liegt übergebener Punkt im Kreis?
        if( pow((_x-x),2) + pow((_y-y),2) < pow(nodeRadius,2) )
        {
         //                                                                                                                                             qDebug() << "gefunden";
            return index;
        }
    }
    return -1;
}

void Graph::printEulerWeg()
{
    //Kopiere AdjazenzListe
    adjList_Algo=adjList;

    //Mache speicher frei
    eulerPath.clear();

    // Finde Knoten mit ungeradem Grad
     size_t u = 0;
     for (size_t i = 0; i < _numNodes; i++)
         if (adjList_Algo[i].size() & 1)
           {   u = i; break;  }

     started=u;
     // EUlerweg ausgehend von u
     if(adjList_Algo.size() != 0)
         printEulerUtil(u);
     qDebug()<<"end of weg";
}

void Graph::printEulerUtil(int u)
{

        qDebug() << "in printeEulerUtil() mit u = "<<u;
        // Gehe alle Nachbarn durch




        vector<int>::iterator i;

        //qDebug()<<"adj[u].size()="<<adjList_Algo[u].size();
        for (i = adjList_Algo[u].begin(); i != adjList_Algo[u].end(); ++i)
        {
            //qDebug()<< "in utilschleife mit u = "<<u<<"und i ="<<*i;
            int v = *i;

            // Wenn v noch nicht entfernt wurde (-1) und eine gültige nächste Kante ist
            if (v != -1 && gueltigeNaechsteKante(u, v))
            {
              //cout << u << "-" << v << "  ";
              Edge edge;
              edge.src=u;
              edge.dest=v;
              eulerPath.push_back(edge);
              rmvEdgeAlgo(u, v);
              //qDebug()<<"rufe util auf mit v = "<<v;
              if(u==started && rekursion)
              {
                  qDebug()<<"rekursion";
              }
              else{
              rekursion=true;
              printEulerUtil(v);
              }
            }


        }
                qDebug()<< "util("<<u<<") ende";
        //cout << endl;
        //printGraphAlgo();

}

int Graph::Tiefensuche(int v, vector<bool>& besucht)
{
    //qDebug()<<"Tiefensuche anfang";

    // Markiere v als besucht
      besucht[v] = true;
      int count = 1;

      // Für alle nachbarn von v
        vector<int>::iterator i;
      for (i = adjList_Algo[v].begin(); i != adjList_Algo[v].end(); ++i)
        {
          //        qDebug() << "in Tiefensuche() forschleife i = "<< *i<< " besucht[*i]= "<< besucht[*i];
          if (*i != -1 && !besucht[*i])
              count += Tiefensuche(*i,besucht);
        }
      //qDebug()<<"Tiefensuche fertig";
      return count;
}

bool Graph::gueltigeNaechsteKante(int src, int dest)
{
    //qDebug() << "in gueltigeNaechsteKante() mit src= "<<src;;
    // Kante src-dest ist gültig wenn:

    // 1) dest ist einziger Nachbar von src
    int count = 0;  // Bestimmt grad von src
    vector<int>::iterator i;
    for (i = adjList_Algo[src].begin(); i != adjList_Algo[src].end(); ++i)
       if (*i != -1)
          count++;          //Zähle nur kanten (!=-1)
    if (count == 1)
    {
    //    qDebug()<< "nextEdge return: true";
        return true;
    }


    // 2) Wenn es mehrere nachbarn gibt, ist src-dest keine Brücke
    // Prüfe nun ob src-dest eine Brücke ist

    // 2.a) Zähle die von src erreichbaren Knoten (Mit Tiefensuche)
    vector<bool> visited;
    visited.resize(_numNodes);
    std::fill(visited.begin(), visited.end(),false);
    int count1 = Tiefensuche(src, visited);
    //qDebug()<<"count1 "<<count1;
    // 2.b) Entferne (src-dest) und zähle nun nochmal die von src erreichbaren Knoten
    rmvEdgeAlgo(src, dest);
    //printGraphAlgo();

    std::fill(visited.begin(), visited.end(),false);
    int count2 = Tiefensuche(src, visited);
    //qDebug()<<"count2 "<<count2;


    // 2.c) füge die Kante wieder hinzu
    addEdge_Algo(src, dest);
    //printGraphAlgo();

    //qDebug()<< "nextEdge return:  bool(count1 <= count2)  count1 =" << count1 << " count2= "<< count2;
    // 2.d) If count1 is greater, then edge (u, v) is a bridge
    return (count1 > count2)? false: true;
}

void Graph::printGraph()
{
    int N = getSize();
    for (int i = 0; i < N; i++)
    {
        // print current vertex number
       qDebug() << i << " --> "<<  "x= " <<  getCoord(i).first <<"y= " << getCoord(i).second<< "degree= "<<getDegree(i);

        // print all neighboring vertices of vertex i
        for (int v : adjList[i])
            qDebug() << v << " ";


        //print coordinates

       //qDebug() <<  "x= " <<  getCoord(i).first <<"y= " << getCoord(i).second;

    }
    qDebug()<<"___________________ ";
}

void Graph::clear()
{
    _coordList.clear();
    for(int i = 0;i< _numNodes;i++)
        adjList[i].clear();
    adjList.clear();
    _numEdges=0;
    _numNodes=0;
}


void Graph::printGraphAlgo()
{
    int N = getSize();
    for (int i = 0; i < N; i++)
    {
        // print current vertex number
       qDebug() << i<< " --> "<<  "x= " <<  getCoord(i).first <<"y= " << getCoord(i).second<< "degree= "<<getDegree(i);

        // print all neighboring vertices of vertex i
        for (int v : adjList_Algo[i])
            qDebug() << v << " ";


        //print coordinates

       //qDebug() <<  "x= " <<  getCoord(i).first <<"y= " << getCoord(i).second;

    }
    qDebug()<<"___________________ ";

}
