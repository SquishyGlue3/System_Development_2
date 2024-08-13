#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <vector>
#include <array>
#include "ResourceType.hpp"
#include "Corner.hpp"
#include "Road.hpp"

using namespace std;

class Tile
{
    public:
    int diceSumNumber;
    ResourceType resourceType;
    vector<Corner *> corners;
    array<Road *, 6> roads; // the roads in the Tile are represented as an array of 6 roads, each road is represented by a Road object, the index of the road will start from the top left corner and continue clockwise
    bool hasRobber;
    array<Tile *, 6> neighbors; // the neighbors of the Tile are represented as an array of 6 pointers to Tiles, the index of the neighbor will start from the top left corner and continue clockwise
};

#endif // TILE_HPP