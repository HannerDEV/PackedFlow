#include "dijkstra.h"
#include "grafo.h"
#include <algorithm>
#include <float.h>
#include <queue>
#include <fstream>
#include <sstream>

#define DIRECCION "Direccion.csv" 


Nodes defineNodes(long long NodoInicial, long long NodoFinal){
    //Nodo
    Nodes destiny;

    int indiceInicial = obtenerIndice(NodoInicial);
    int indiceFinal = obtenerIndice(NodoFinal);

    //Se pasa el nodoInicial a entero
    destiny.nI = indiceInicial;
    destiny.nF = indiceFinal;

    return destiny;
}


Resultado Dijkstra(long long origen, long long destino, const vector<vector<pair<double, long long>>>& grafo){
    int numNodos = grafo.size();
    vector<double> latencias(numNodos, DBL_MAX);
    vector<long long> padre(numNodos, -1);

    latencias[origen] = 0;

    priority_queue<pair<double,long long>, vector<pair<double,long long>>, greater<pair<double,long long>>> siguiente;
    siguiente.push({0, origen});

    while(!siguiente.empty()){
        double latencia = siguiente.top().first;
        long long nodo = siguiente.top().second;
        siguiente.pop();

        if(latencia > latencias[nodo])    continue;

        for(pair<double, long long> arista : grafo[nodo]){
            double latencia = arista.first;
            long long vecino = arista.second;

            if(latencias[vecino] > latencias[nodo] + latencia){
               latencias[vecino] = latencias[nodo] + latencia;
                padre[vecino] = nodo;
                siguiente.push({latencias[vecino], vecino});
            }
        }        
    }

    vector<long long> camino;
    for(int v = destino; v != -1; v = padre[v]){
        camino.push_back(v);
    }
    reverse(camino.begin(), camino.end());

    Resultado res;
    res.distancia = latencias[destino];
    res.camino = camino;

    return res;
}