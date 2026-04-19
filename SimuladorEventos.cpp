#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <float.h>

int nodoI;
int nodoF;
int nNodos;

using namespace std;

vector<vector<pair<double, int>>> grafo;

struct Package{
    int origenNode;
    vector<int> route;
    double peso;
    int indexNode;
};

enum class EventosType{
    PACKAGESEND = 1,
    PACKAGEARRIVED = 2
};

struct Evento{
    double time;
    EventosType type;
    Package package;
};


struct Resultado {
    double distancia;
    vector<int> camino;
};


void inicializar(){
    for(int i = 0; i<nNodos; i++){
        vector<pair<double, int>> nodo = {};
        grafo.push_back(nodo);
    }
}

void dirigidoAd(int n, int n2, double p2){
    grafo[n-1].emplace_back(p2, n2-1);
}


void printGrafo(){
     for (int i = 0; i < nNodos; i++){
        cout << "Nodo" << i + 1 <<": ";
        for (int j = 0; j < grafo[i].size(); j++){
            cout << "[" << grafo[i][j].first << ", " << grafo[i][j].second <<"]" <<" ";
        }  
        cout << endl;
    }
}

void defineNodes(){
    cout << "Ingrese el nodo inicial";
    cin >> nodoI;
    nodoI--;
    cout << "Ingrese el nodo final";
    cin >> nodoF;
    nodoF--;
}

void printCamino(){
    cout << "La distancia mas cercana del nodo" << nodoI << " al nodo" << nodoF << "es:" << res.distancia <<endl;
    cout << "El camino es este: ";
    for (int i: res.camino)
    {
        cout << i << " ";
    }
}


Resultado dijkstra (int nodoOrigen, int nodoFinal){
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

Resultado res;

int main(){
    
    cout << "Ingrese el numero de nodos " << endl;
    cin >> nNodos;

    inicializar();

    defineNodes();

do{
    Evento event1;

    event1.type = EventosType::PACKAGESEND;
    event1.package.origenNode = nodoI;
    event1.package.indexNode = nodoI;
    event1.package.route = res.camino;
    event1.time = 0;
    
    Evento event2;

    event2.type = EventosType::PACKAGEARRIVED;
    event2.package.origenNode = nodoI;
    event2.package.route = res.camino;
    event2.package.indexNode = event1.package.indexNode + 1;

    int u = event1.package.route[event1.package.indexNode];
    int v = event1.package.route[event1.package.indexNode + 1];

    double latencia = 0;

    for (auto n:grafo[u]){
        if(n.second != v) continue;
        latencia = n.first;
        break;
    }
    

    event2.time = event1.time + latencia;
}while(event2.package.indexNode == nodoF);

    return 0;
}