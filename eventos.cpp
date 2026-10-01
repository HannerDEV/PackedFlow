#include "grafo.h"
#include "dijkstra.h"
#include "eventos.h"
#include <queue>

Info getInfoEvent(Evento e){

    auto type(e.type == EventosType::PACKAGEARRIVED ? "PACKAGEARRIVED" : "PACKAGESEND");
    long long node = e.package.route[e.package.indexNode];
    long long next_node = -1;

    if(e.package.indexNode + 1 < e.package.route.size()){
        next_node = e.package.route[e.package.indexNode + 1];
    }

    Info info;

    info.node = node;
    info.next_node = next_node;
    info.type = type;

    return info;
}

double getLatency(long long u, long long v, const vector<vector<pair<double, long long>>>& grafo){
    for (auto n:grafo[u]){
        if(n.second == v) return n.first;
    }
    return 0;
}

void procesarEvento(const Evento& e, 
    priority_queue<Evento, vector<Evento>, CompareEventos>& cola, 
    const vector<vector<pair<double, long long>>>& grafo){

    if(e.type == EventosType::PACKAGESEND){

        int idx = e.package.indexNode;

        if(idx < e.package.route.size()-1){
            int u = e.package.route[idx];
            int v = e.package.route[idx + 1];

            double lat = getLatency(u, v, grafo);

            Evento next;
            
            next.type = EventosType::PACKAGEARRIVED;
            next.time = e.time + lat;
            next.package = e.package;
            next.package.indexNode++;

            cola.push(next);
        }
    }

    else if(e.type == EventosType::PACKAGEARRIVED){
           
        if(e.package.indexNode < e.package.route.size() - 1){ 
            Evento next;
            next.package = e.package;
            next.time = e.time;
            next.type = EventosType::PACKAGESEND;
    
            cola.push(next);   
        }

    }
};