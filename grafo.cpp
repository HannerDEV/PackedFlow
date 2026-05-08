#include "grafo.h"
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

#define GRAFO "csvGrafo.csv" 

vector<vector<pair<double, int>>> grafo;

void dirigidoAd(int n, int n2, double p2){
    grafo[n-1].emplace_back(p2, n2-1);
}
void inicializar(){
    //abre el csv Grafo
    ifstream archivo(GRAFO);

    //Define linea
    string linea;
    char delimitador = ',';

    // descartar encabezado
    getline(archivo, linea); 

    //crea vector de aristas
    vector<tuple<int,int,double>> aristas;
    int maxNodo = 0;

    // leer todo y encontrar nodo máximo
    while(getline(archivo, linea)){
        stringstream stream(linea);
        string NodoInicial, NodoFinal, PesoArista;

        getline(stream, NodoInicial ,delimitador);
        getline(stream, NodoFinal ,delimitador);
        getline(stream, PesoArista,delimitador);

        int u = stoi(NodoInicial);
        int v = stoi(NodoFinal);
        double w = stod(PesoArista);

        aristas.emplace_back(u, v, w);

        if(u > maxNodo) maxNodo = u;
        if(v > maxNodo) maxNodo = v;
    }

    archivo.close();

    // redimensionar grafo
    grafo.resize(maxNodo);

    // insertar aristas
    for(tuple<int,int,double>& arista : aristas){
        int u = get<0>(arista);
        int v = get<1>(arista);
        int w = get<2>(arista);
        dirigidoAd(u, v, w);
    }
}