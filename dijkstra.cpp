#include "dijkstra.h"
#include "grafo.h"
#include <algorithm>
#include <float.h>
#include <queue>
#include <fstream>
#include <sstream>

#define DIRECCION "csvDireccion.csv" 


Nodes defineNodes(){

    ifstream archivo(DIRECCION);
    string linea;
    char delimitador = ',';

    //Se ignora la primera linea, y pasa a la siguiente
    getline(archivo, linea);
    getline(archivo, linea);


    stringstream stream(linea);
    string NodoInicial, NodoFinal;

    //Se guarda el nodo inicial y el final
    getline(stream, NodoInicial ,delimitador);
    getline(stream, NodoFinal ,delimitador);
    
    //Nodo
    Nodes destiny;

    //Se pasa el nodoInicial a entero
    destiny.nI = stoi(NodoInicial)-1;
    destiny.nF = stoi(NodoFinal)-1;

    return destiny;
}


Resultado Dijkstra(int origen, int destino, const vector<vector<pair<double, int>>>& grafo){
    int numNodos = grafo.size();
    vector<double> latencias(numNodos, DBL_MAX);
    vector<int> padre(numNodos, -1);

    latencias[origen] = 0;

    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> siguiente;
    siguiente.push({0, origen});

    while(!siguiente.empty()){
        double latencia = siguiente.top().first;
        int nodo = siguiente.top().second;
        siguiente.pop();

        if(latencia > latencias[nodo])    continue;

        for(pair<int, double> arista : grafo[nodo]){
            double latencia = arista.first;
            int vecino = arista.second;
            if(latencias[vecino] > latencias[nodo] + latencia){
               latencias[vecino] = latencias[nodo] + latencia;
                padre[vecino] = nodo;
                siguiente.push({latencias[vecino], vecino});
            }
        }        
    }

    vector<int> camino;
    for(int v = destino; v != -1; v = padre[v]){
        camino.push_back(v);
    }
    reverse(camino.begin(), camino.end());

    Resultado res;
    res.distancia = latencias[destino];
    res.camino = camino;

    return res;
}