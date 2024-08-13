#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include "ResourceType.hpp"
#include "Road.hpp"
#include "Corner.hpp"
#include "Tile.hpp"
using namespace std;




class Board
{
public:
    Board() {};
    void initializeBoard();
    void printBoard() const;
    void setRobber(int row, int col);
    void setRoad(int row, int col, int roadIndex, int playerID); // we will use row and col to determine the requseted tile, than we will use the roadIndex to determine the requested road
    void isValidRoad(int row, int col, int roadIndex, int playerID) const;
    void setCorner(int row, int col, int cornerIndex, string homeType, int playerID); // we will use row and col to determine the requseted tile, than we will use the cornerIndex to determine the requested corner
    void setFirstSettlements(int row, int col, int cornerIndex, int playerID);
    void isValidCorner(int row, int col, int cornerIndex, int playerID) const;
    void updateNeighbors(int row, int col, int cornerIndex);
    int getCornerId(int row, int col, int cornerIndex);
    int getRoadId(int row, int col, int roadIndex);
    void dealResource(int diceSum);
    Tile* getTile(int row, int col);
    ~Board() {};

    array<array<Tile, 5>, 5> board;
    array<Corner *, 53> boardCorners;
    array<Road *, 71> boardRoads;

    string resourceTypeToString(ResourceType resourceType) const;
};

#endif // BOARD_HPP