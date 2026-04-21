#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <float.h>
#include <fstream>
#include <sstream>

#define CSV "csv.txt" 

using namespace std;

int nodoI;
int nodoF;
int nNodos;



vector<vector<pair<double, int>>> grafo;

struct Package{
    int origenNode;
    vector<int> route;
    double peso;
    int indexNode = 0;
};

enum class EventosType{
    PACKAGESEND,
    PACKAGEARRIVED
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

double obtenerLatencia(int u, int v){
    for (auto n:grafo[u]){
        if(n.second == v) return n.first;
    }
    return 0;
}

Resultado Dijkstra (int nodoOrigen, int nodoFinal){
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

struct CompareEventos{
    bool operator()(const Evento& a, const Evento& b){
        return a.time > b.time;
    }
};

void procesarEvento(const Evento& e, 
    priority_queue<Evento, vector<Evento>, CompareEventos>& cola){

        if(e.type == EventosType::PACKAGESEND){

            int idx = e.package.indexNode;
            int u = e.package.route[idx];
            int v = e.package.route[idx + 1];

            double lat = obtenerLatencia(u, v);

            Evento next;

            next.type = EventosType::PACKAGEARRIVED;
            next.time = e.time + lat;
            next.package = e.package;

            cola.push(next);
        }

        else if(e.type == EventosType::PACKAGEARRIVED){
            
            Evento next;
            next.package = e.package;
            next.time == e.time;
            next.package.indexNode++;

            if(next.package.indexNode < next.package.route.size() - 1){
                next.type = EventosType::PACKAGESEND;
                cola.push(next);
            }

        }
};

int main(){
    
    inicializar();

    ifstream archivo(CSV);
    string linea;
    char delimitador =',';
    
    //Lee el encabezado para descartarlo
    getline(archivo, linea);

    while(getline(archivo, linea)){

        stringstream stream(linea);
        string NodoInicial, NodoFinal, PesoArista;

        getline(stream, NodoInicial ,delimitador);
        getline(stream, NodoFinal ,delimitador);
        getline(stream, PesoArista,delimitador);

        dirigidoAd(stoi(NodoInicial), stoi(NodoFinal), stod(PesoArista));
    }

    archivo.close();

    defineNodes();

    priority_queue<Evento, vector<Evento>, CompareEventos> cola;

    Resultado res = Dijkstra(0, 5);
    auto ruta = res.camino;

    Package p;
    p.indexNode = 0;
    p.route = ruta;

    Evento e0;
    e0.package = p;
    e0.time = 0;
    e0.type = EventosType::PACKAGESEND;

    cola.push(e0);
    

    while(!cola.empty()){

        Evento e = cola.top();
        cola.pop();

        cout << "Evento: " << (e.type == EventosType::PACKAGEARRIVED ? "ARRIVED" : "SEND")
        <<"Tiempo: " << e.time
        <<"Nodo: " << e.package.route[e.package.indexNode]
        << endl;

        procesarEvento(e, cola);
    }

    return 0;
}