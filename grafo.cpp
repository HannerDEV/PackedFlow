#include "grafo.h"
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

#define GRAFO "grafo.csv" 

vector<vector<pair<double, long long>>> grafo;
unordered_map<long long, int> indiceNodo;
vector<long long> idNodo;

int obtenerIndice(long long id){
    return indiceNodo[id];
}

long long obtenerId(int indice){
    return idNodo[indice];
}

void dirigidoAd(long long n, long long n2, double p2){
    int indiceOrigen = obtenerIndice(n);
    int indiceDestino = obtenerIndice(n2);
    grafo[indiceOrigen].emplace_back(p2, indiceDestino);
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

        if(indiceNodo.find(origen) == indiceNodo.end()){
            int indice = idNodo.size();
            indiceNodo[origen] = indice;
            idNodo.push_back(origen);
        }

        if(indiceNodo.find(destino) == indiceNodo.end()){
            int indice = idNodo.size();
            indiceNodo[destino] = indice;
            idNodo.push_back(destino);
        }

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
    grafo.resize((idNodo.size()));

    // insertar aristas
    for(tuple<long long,long long,double>& arista : aristas){
        long long u = get<0>(arista);
        long long v = get<1>(arista);
        double w = get<2>(arista);
        dirigidoAd(u, v, w);
    }
}