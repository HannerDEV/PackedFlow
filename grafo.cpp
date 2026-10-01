#include "grafo.h"
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

#define GRAFO "grafo.csv" 

vector<vector<pair<double, long long>>> grafo;

void dirigidoAd(long long n, long long n2, double p2){
    grafo[n-1].emplace_back(p2, n2-1);
}
void inicializar(int argc, char* argv[]){

    vector<tuple<long long,long long,double>> aristas;
    int maxNodo = 0;


// leer todo y encontrar nodo máximo
    for(int i = 3; i < argc; i++){
        string conexion = argv[i];
        long long maxnodo = 0;

        stringstream ss(conexion);
        string dato;

        getline(ss, dato, ',');
        long long origen = stoll(dato);

        getline(ss, dato, ',');
        long long destino = stoll(dato);

        getline(ss, dato, ',');
        double peso = stod(dato);

        if(origen > maxNodo) maxNodo = origen;
        if(destino > maxNodo) maxNodo = destino;

        tuple<long long, long long, double> conexionR;

        get<0>(conexionR) = origen;
        get<1>(conexionR) = destino;
        get<2>(conexionR) = peso;

        aristas.push_back(conexionR);
    }


    // redimensionar grafo
    grafo.resize(maxNodo);

    // insertar aristas
    for(tuple<long long,long long,double>& arista : aristas){
        long long u = get<0>(arista);
        long long v = get<1>(arista);
        double w = get<2>(arista);
        dirigidoAd(u, v, w);
    }
}