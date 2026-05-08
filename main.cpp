#include "grafo.h"
#include "dijkstra.h"
#include "eventos.h"
#include <queue>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

int main(){

    inicializar();

    //Creamos la cola, para eventos
    priority_queue<Evento, vector<Evento>, CompareEventos> cola;

    //Se define el inicio y el destino de el camino
    Nodes direction = defineNodes();
    
    //Busca el camino mas corto
    Resultado res = Dijkstra(direction.nI, direction.nF, grafo);
    auto ruta = res.camino;

    Package p;
    p.indexNode = 0;
    p.route = ruta;

    Evento e0;
    e0.package = p;
    e0.time = 0;
    e0.type = EventosType::PACKAGESEND;

    cola.push(e0);
    
    //proximo guardado en csv
    ofstream archivo("csvEventos.csv");

    while(!cola.empty()){

        Evento e = cola.top();
        cola.pop();

        Info event = getInfoEvent(e);
        
        if(!(event.type == "PACKAGESEND")){
            cout << "Evento: " << event.type << "  "
            <<"Tiempo: " << e.time  << "  "
            <<"Nodo: " << event.node << "  "
            << endl;
        }
        else{
            cout << "Evento: " << event.type << "  "
            <<"Tiempo: " << e.time  << "  "
            <<"Nodo: " <<  event.node << "-" << event.next_node
            << endl;
        }
        
        procesarEvento(e, cola, grafo); 
    }

    return 0;
}