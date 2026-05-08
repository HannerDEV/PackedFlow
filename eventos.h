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
    int origenNode;
    vector<int> route;
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
    int node;
    int next_node;
};

struct CompareEventos{
    bool operator()(const Evento& a, const Evento& b){
        return a.time > b.time;
    }
};

void procesarEvento(const Evento& e, 
    priority_queue<Evento, vector<Evento>, CompareEventos>& cola, 
    const vector<vector<pair<double, int>>>& grafo);

Info getInfoEvent(Evento e);

#endif