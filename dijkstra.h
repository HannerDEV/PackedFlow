#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>

using namespace std;

struct Resultado {
    double distancia;
    vector<long long> camino;
};


Resultado Dijkstra(long long origen, long long destino, const vector<vector<pair<double, long long>>>& grafo);

struct Nodes{
    long long nI;
    long long nF;
};

Nodes defineNodes(long long NodoInicial, long long NodoFinal);



#endif