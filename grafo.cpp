#include "grafo.h"
#include <utility>
#include <fstream>
#include <sstream>

#define GRAFO "csvGrafo.txt" 

vector<vector<pair<double, int>>> grafo;

void dirigidoAd(int n, int n2, double p2){
    grafo[n-1].emplace_back(p2, n2-1);
}

void inicializar(){
    ifstream archivo(GRAFO);
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
}