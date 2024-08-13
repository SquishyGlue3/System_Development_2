#include "Corner.hpp"
#include <iostream>
#include <vector>

using namespace std;

    Corner::Corner(int cornerId) : cornerId(cornerId) {};

    Corner::Corner(const Corner &other) // copy constructor
    {
        cornerId = other.cornerId;
        playerID = other.playerID;
        isOccupied = other.isOccupied;
        isNeighborCornerOccupied = other.isNeighborCornerOccupied;
        isCity = other.isCity;
        isSettlement = other.isSettlement;
        homeType = other.homeType;
        neighbors = other.neighbors;
        neighborRoads = other.neighborRoads;
    }
    bool Corner::isNeighbor(Corner *corner)
    {
        for (Corner *neighbor : neighbors)
        {
            if (neighbor == corner)
            {
                return true;
            }
        }
        return false;
    }

    bool Corner::isNeighborRoad(Road *road)
    {
        for (Road *neighbor : neighborRoads)
        {
            if (neighbor == road)
            {
                return true;
            }
        }
        return false;
    }