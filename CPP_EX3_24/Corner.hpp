#include <iostream>
#include <vector>
#include "Road.hpp"
#include "Tile.hpp"
using namespace std;


class Corner
{
    public:
    Corner(int cornerId) : cornerId(cornerId) {};

    Corner(const Corner &other) {}; // copy constructor

    ~Corner() {};
    int cornerId;
    int playerID = -1;
    bool isOccupied = false;
    bool isNeighborCornerOccupied = false;
    bool isCity = false;
    bool isSettlement = false;
    string homeType;
    vector<Corner *> neighbors;
    vector<Road *> neighborRoads;
    vector<Tile *> neighborTiles;
    bool isNeighbor(Corner *corner);
    bool isNeighborRoad(Road *road);
};