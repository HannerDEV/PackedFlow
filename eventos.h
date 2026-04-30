#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Package{
    int origenNode;
    vector<int> route;
    double peso;
    int indexNode = 0;
};

enum class EventosType{
    PACKAGESEND,
    PACKAGEARRIVED
};

struct Evento{
    double time;
    EventosType type;
    Package package;
};

struct Info{
    string type;
    int node;
};