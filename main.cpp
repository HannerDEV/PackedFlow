#include "grafo.h"
#include "dijkstra.h"
#include "eventos.h"
#include <stdexcept>
#include <queue>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc, char* argv[]){

    if(argc < 3){
        throw std::runtime_error("argumentos faltantes");
    }

    inicializar(argc, argv);


    long long ni = std::stoll(argv[1]);
    long long nf = std::stoll(argv[2]);

    //Creamos la cola, para eventos
    priority_queue<Evento, vector<Evento>, CompareEventos> cola;

    //Se define el inicio y el destino de el camino
    Nodes direction = defineNodes(ni, nf);
    


    //Busca el camino mas corto
    Resultado res = Dijkstra(direction.nI, direction.nF, grafo);

    auto ruta = res.camino;
    for(int i = 0; i < ruta.size() ; i++){
        cout << ruta[i];
    }

    Package p;
    p.indexNode = 0;
    p.route = ruta;

    Evento e0;
    e0.package = p;
    e0.time = 0;
    e0.type = EventosType::PACKAGESEND;

    cola.push(e0);
    
    //proximo guardado en csv
    ofstream archivo("Eventos.csv");
    archivo << "Evento,Tiempo,Nodo"<<endl;


    while(!cola.empty()){

        Evento e = cola.top();
        cola.pop();

        cout << "ANTES DE getInfoEvent" << endl;

        Info event = getInfoEvent(e);

        cout << "DESPUES DE getInfoEvent" << endl;

        if(!(event.type == "PACKAGESEND")){
            archivo << event.type << "," << e.time  << "," << event.node+1 << endl;
        }
        else{
            archivo << event.type << "," << e.time  << "," <<  event.node+1 << "-" << event.next_node + 1<< endl;
        }
        cout << "ANTES DE procesarEvento" << endl;
        procesarEvento(e, cola, grafo); 
        cout << "DESPUES DE getInfoEvent" << endl;

    }

    return 0;
}