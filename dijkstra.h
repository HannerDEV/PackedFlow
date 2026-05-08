#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>

using namespace std;

struct Resultado {
    double distancia;
    vector<int> camino;
};


Resultado Dijkstra(int origen, int destino, const vector<vector<pair<double, int>>>& grafo);

struct Nodes{
    int nI;
    int nF;
};

Nodes defineNodes();



#endif