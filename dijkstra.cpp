#include <dijkstra.h>
#include <algorithm>
#include <float.h>
#include <queue>
#include <fstream>
#include <sstream>

#define DIRECCION "csvDireccion.txt" 


Nodes defineNodes(){
    ifstream archivo(DIRECCION);
    string linea;
    char delimitador = ',';

    getline(archivo, linea);

    stringstream stream(linea);
    string NodoInicial, NodoFinal;

    getline(stream, NodoInicial ,delimitador);
    getline(stream, NodoFinal ,delimitador);

    Nodes destiny;

    destiny.nI = stoi(NodoInicial);
    destiny.nF = stoi(NodoFinal);

    return destiny;
}

Resultado Dijkstra (int nodoOrigen, int nodoFinal, vector<vector<pair<double, int>>> grafo){
    int numNodos = grafo.size();
    vector<double> latencias(numNodos, DBL_MAX);
    vector<int> padre(numNodos, -1);

    latencias[nodoOrigen] = 0;

    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> siguiente;
    siguiente.push({0, nodoOrigen});

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
    for(int v = nodoFinal; v != -1; v = padre[v]){
        camino.push_back(v);
    }
    reverse(camino.begin(), camino.end());

    Resultado res;
    res.distancia = latencias[nodoFinal];
    res.camino = camino;

    return res;
}