#ifndef EVENTOS_H
#define EVENTOS_H

#include <queue>
#include <vector>
#include <string>

using namespace std;

enum class EventosType{
    PACKAGESEND,
    PACKAGEARRIVED
};

struct Package{
    long long origenNode;
    vector<long long> route;
    double peso;
    int indexNode;
};

struct Evento{
    double time;
    EventosType type;
    Package package;
};

struct Info{
    string type;
    long long node;
    long long next_node;
};

struct CompareEventos{
    bool operator()(const Evento& a, const Evento& b){
        return a.time > b.time;
    }
};

void procesarEvento(const Evento& e, 
    priority_queue<Evento, vector<Evento>, CompareEventos>& cola, 
    const vector<vector<pair<double, long long>>>& grafo);

Info getInfoEvent(Evento e);

#endif