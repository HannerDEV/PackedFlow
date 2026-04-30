int main(){
    
    
    priority_queue<Evento, vector<Evento>, CompareEventos> cola;

    Resultado res = Dijkstra(0, 5);
    auto ruta = res.camino;

    Package p;
    p.indexNode = 0;
    p.route = ruta;

    Evento e0;
    e0.package = p;
    e0.time = 0;
    e0.type = EventosType::PACKAGESEND;

    cola.push(e0);
    
    ofstream archivo("csvEventos.csv");

    while(!cola.empty()){

        Evento e = cola.top();
        cola.pop();

        Info event = getInfoEvent(e);

        cout << "Evento: " << event.type
        <<"Tiempo: " << e.time
        <<"Nodo: " << event.node
        << endl;



        procesarEvento(e, cola);
    }

    return 0;
}