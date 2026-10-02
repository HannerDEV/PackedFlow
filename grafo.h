#ifndef GRAFO_H
#define GRAFO_H
#include <unordered_map>

#include <vector>

using namespace std;

extern vector<vector<pair<double, long long>>> grafo;

extern unordered_map<long long, int> indiceNodo;
extern vector<long long> idNodo;

int obtenerIndice(long long id);
long long obtenerId(int indice);



void inicializar(int argc, char* argv[]);
#endif