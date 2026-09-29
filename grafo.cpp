#include "grafo.h"
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

#define GRAFO "grafo.csv" 

vector<vector<pair<double, int>>> grafo;

void dirigidoAd(int n, int n2, double p2){
    grafo[n-1].emplace_back(p2, n2-1);
}
void inicializar(int argc, char* argv[]){

    vector<tuple<int,int,double>> aristas;
    int maxNodo = 0;


// leer todo y encontrar nodo máximo
    for(int i = 3; i < argc; i++){
        string conexion = argv[i];
        int maxnodo = 0;

        stringstream ss(conexion);
        string dato;

        getline(ss, dato, ',');
        int origen = stoi(dato);

        getline(ss, dato, ',');
        int destino = stoi(dato);

        getline(ss, dato, ',');
        double peso = stod(dato);

        if(origen > maxNodo) maxNodo = origen;
        if(destino > maxNodo) maxNodo = destino;

        tuple<int, int, double> conexionR;

        get<0>(conexionR) = origen;
        get<1>(conexionR) = destino;
        get<2>(conexionR) = peso;

        aristas.push_back(conexionR);
    }


    // redimensionar grafo
    grafo.resize(maxNodo);

    // insertar aristas
    for(tuple<int,int,double>& arista : aristas){
        int u = get<0>(arista);
        int v = get<1>(arista);
        double w = get<2>(arista);
        dirigidoAd(u, v, w);
    }
}