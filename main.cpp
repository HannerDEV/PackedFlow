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

    cout << "ID origen: " << ni << endl;
    cout << "ID destino: " << nf << endl;

    cout << "Indice origen: " << direction.nI << endl;
    cout << "Indice destino: " << direction.nF << endl;

    cout << "Cantidad de nodos en grafo: " << grafo.size() << endl;
    cout << "Vecinos del origen: " << grafo[direction.nI].size() << endl;
    cout << "Vecinos del destino: " << grafo[direction.nF].size() << endl;

    cout << "Aristas del origen: ";
    for(auto arista : grafo[direction.nI]){
        cout << arista.second << " ";
    }
    cout << endl;

    cout << "Aristas del destino: ";
    for(auto arista : grafo[direction.nF]){
        cout << arista.second << " ";
    }
    cout << endl;
    


    //Busca el camino mas corto
    Resultado res = Dijkstra(direction.nI, direction.nF, grafo);

    
    auto ruta = res.camino;
    cout << "RUTA INTERNA: ";
    for(long long nodo : ruta){
        cout << nodo << " ";
    }
    cout << endl;

    cout << "DESTINO ESPERADO: " << direction.nF << endl;
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


        Info event = getInfoEvent(e);


        if(!(event.type == "PACKAGESEND")){
            archivo << event.type << "," << e.time  << "," << event.node << endl;
        }
        else{
            archivo << event.type << "," << e.time  << "," <<  event.node<< "-" << event.next_node<< endl;
        }
        procesarEvento(e, cola, grafo); 

    }

    return 0;
}