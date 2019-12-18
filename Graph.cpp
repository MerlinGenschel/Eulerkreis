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

    for ( int i = 0 ;  i < nKnoten ;  ++i )
    {
        double x,y;
        fin >> x ;
        fin >> y ;
        _coordList.at(i)=make_pair(x,y);
        getline( fin, dummy ) ;		// ignoriere Rest der Zeile
    }


    /***  lese Kanten aus  ***/
    cout << "nKanten = "<<nKanten<<endl;
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
    //_coordList.resize(_numNodes);
    _coordList.push_back(make_pair(x,y));
    emit(graphChanged());
    //printGraph();
    return true;
}

bool Graph::removeNode(int index)
{
    //qDebug()<<"remove node with index "<<index <<" and degree "<<getDegree(index)<<", insgesamt gibt es (vor dem Löschen) "<<_numNodes<<"Knoten";
    if (index >= _numNodes)
        return false;
    //printGraph();
    //eingehende Kanten?
   // qDebug() << "numNodes " << _numNodes<< " adjList.size() " << adjList.size();
    for (int i = 0; i < _numNodes;i++)
    {

        //size_t y = adjList.size();
        //qDebug() << i<<"te Zeile der Adjazenzliste durchsuchen, diese hat eine Länge von "<< getDegree(i);
        for(int j = int(getDegree(i))-1; j>= 0 ;j--)
         {
            //qDebug()<< adjList.at(i).size();


            //qDebug() << "i="<< i << "j=" << j<< "adjList.at(i).at(j)= "<<adjList.at(i).at(j) ;
             if (adjList.at(i).at(j) == index)
             {
                 //qDebug()<<"An "<<j<<"ter Stelle Eintrag mit adjList.at(i).at(j)=index= "<<index<<"gefunden";
                 int adj_i_size= adjList.at(i).size();
                 adjList.at(i).erase(adjList.at(i).begin()+j);
                 _numEdges--;
                 //qDebug()<<"Löschen (hier) erfolgreich";
             }
             //


           }

        //Schleife zum nachrücken
        for(int j = int(getDegree(i))-1; j>= 0 ;j--)
            if(adjList.at(i).at(j)>index)
        {
            qDebug()<<"es wird nachgerückt";
            adjList.at(i).at(j)--;
        }
      }
             if(!GERICHTET)
                 _numEdges -= adjList.at(index).size();

             adjList.erase(adjList.begin()+index);
             _coordList.erase(_coordList.begin()+index);
             _numNodes--;
             //printGraph();


    emit(graphChanged());


             return true;
}

void Graph::rmvEdge(int u, int v)
{
    // Find v in adjacency list of u and replace it with -1
     vector<int>::iterator iv = find(adjList_Algo[u].begin(), adjList_Algo[u].end(), v);
     *iv = -1;

     // Find u in adjacency list of v and replace it with -1
     vector<int>::iterator iu = find(adjList_Algo[v].begin(), adjList_Algo[v].end(), u);
     *iu = -1;
}

bool Graph::addEdge(int src, int dest)
{
    //prüfe ob KNoten vorhanden sind
    if (max(src,dest) > _numNodes
            || src == dest)
        return false;


    adjList.at(src).push_back(dest);
    _numEdges++;
    //qDebug()<< "src ="<<src<<" adjList(src).size()=" << adjList[src].size();

    if (!GERICHTET)
        adjList.at(dest).push_back(src);
    emit(graphChanged());
    //printGraph();
    return true;
}

bool Graph::moveNodeTo(int index, double X, double Y)
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
        double x = _coordList.at(index).first;
        double y = _coordList.at(index).second;
        //qDebug() << x << " " << y << endl;
        //liegt übergebener Punkt im Kreis?
        if( pow((_x-x),2) + pow((_y-y),2) < pow(nodeRadius,2) )
        {
         //                                                                                                                                             qDebug() << "gefunden";
            qDebug()<< "clicked on node liefert index "<< index;
            return index;
        }
    }
    return -1;
}

void Graph::printEulerWeg()
{
    qDebug() << "in printeEulerWeg()";
    //Kopiere AdjazenzListe
    adjList_Algo=adjList;

    // Finde Knoten mit ungeradem Grad
     size_t u = 0;
     for (size_t i = 0; i < _numNodes; i++)
         if (adjList_Algo[i].size() & 1)
           {   u = i; break;  }

     // Print tour starting from oddv
     printEulerUtil(u);
     cout << endl;
}

void Graph::printEulerUtil(int u)
{
        qDebug() << "in printeEulerUtil()";
    // Recur for all the vertices adjacent to this vertex
      //list<int>::iterator i;
      for (auto i = adjList_Algo[u].begin(); i != adjList_Algo[u].end(); ++i)
      {
          int v = *i;

          // If edge u-v is not removed and it's a a valid next edge
          if (v != -1 && gueltigeNaechsteKante(u, v))
          {
              cout << u << "-" << v << "  ";
              rmvEdge(u, v);
              printEulerUtil(v);
          }
      }
}

int Graph::Tiefensuche(int v, vector<bool> besucht)
{

    // Mark the current node as visited
      besucht[v] = true;
      int count = 1;

      // Recur for all vertices adjacent to this vertex

      for (vector<int>::iterator i = adjList_Algo[v].begin(); i != adjList_Algo[v].end(); ++i)
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
        qDebug() << "in gueltigeNaechsteKante()";
    // The edge u-v is valid in one of the following two cases:

    // 1) If v is the only adjacent vertex of u
    int count = 0;  // To store count of adjacent vertices
    //list<int>::iterator i;
    for (auto i = adjList_Algo[src].begin(); i != adjList_Algo[src].end(); ++i)
       if (*i != -1)
          count++;
    if (count == 1)
    {
        qDebug()<< "nextEdge return: true";
        return true;
    }


    // 2) If there are multiple adjacents, then u-v is not a bridge
    // Do following steps to check if u-v is a bridge

    // 2.a) count of vertices reachable from u
    vector<bool> visited;
    visited.resize(_numNodes);
    std::fill(visited.begin(), visited.end(),false);
    int count1 = Tiefensuche(src, visited);

    // 2.b) Remove edge (u, v) and after removing the edge, count
    // vertices reachable from u
    rmvEdge(src, dest);
    std::fill(visited.begin(), visited.end(),false);
    int count2 = Tiefensuche(src, visited);

    // 2.c) Add the edge back to the graph
    addEdge_Algo(src, dest);

        qDebug()<< "nextEdge return:  bool(count1 <= count2)  count1 =" << count1 << " count2= "<< count2;
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
