
#include "Board.hpp"

using namespace std;

Board board = Board();
array<int, 25> diceSumNumbers = {10, 2, 9, -1, -1, 12, 6, 4, 10, -1, 9, 11, 0, 3, 8, 8, 3, 4, 5, -1, 5, 6, 11, -1, -1};
int arraycounter = 0;
vector<ResourceType> resourceTypes = {WOOD, SHEEP, BRICK, WHEAT, ORE, WOOD, SHEEP, BRICK, WHEAT, DESERT, ORE, WOOD, SHEEP, BRICK, WHEAT, ORE, WOOD, SHEEP, BRICK};
Tile robbered;

Board::Board()
{
    //initializing the boardRoads array
    for (int i = 0; i < 72; i++)
    {
        Road *road = nullptr;
        boardRoads[i] = road;
    }
    initializeBoard();
}

// the board tile's numbers should look like this:
//   10 2 9 -1 -1
//   12 6 4 10 -1
//   9 11 0 3 8
//   8 3 4 5 -1
//   5 6 11 -1 -1

ResourceType selectResourceType()
{
    //@brief Select a random resource type
    // The resource type is selected randomly from a predefined vector
    // The vector is shuffled and the first element is selected
    // The selected resource type is removed from the vector

    if (resourceTypes.empty())
    {
        throw range_error("Resource types vector is empty, something went wrong!");
    }
    ResourceType selected = resourceTypes[0];
    resourceTypes.erase(resourceTypes.begin()); // remove the selected resource type from the vector
    return selected;
}

void Board::initializeBoard()
{
    //@brief Initialize catan board
    // 0 = desert, -1 = null, as the board is hexagonal, the first and last rows have 2 nulls, the second and fourth have 1 null
    // any other number is a dice sum number, those numbers organized in a predefined order
    // The board is represented as a 2D array
    int cornerCounter = 0;
    int roadCounter = 0;
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (arraycounter == diceSumNumbers.size())
            {
                throw range_error("diceSumNumbers array is too short for the board size, something went wrong!"); // shouldn't get to it
            }
            board[row][col].diceSumNumber = diceSumNumbers[arraycounter];
            arraycounter++;
            if (board[row][col].diceSumNumber == -1)
            {
                board[row][col].resourceType = NONE;
            }
            else
            {
                board[row][col].resourceType = selectResourceType();
            }
            if (board[row][col].diceSumNumber == 0) // if it is a desert, we will place the robber there
            {
                robbered = board[row][col];
                board[row][col].hasRobber = true;
            }
        }
    }

    //@brief Initialize the corners of the board
    // The corners are represented as a vector in the tile struct
    // The corners are initialized in a predefined order
    // Each tile has 6 corners, begining from the top left corner and continuing clockwise

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            int updated = 0;
            for (int i = cornerCounter; i < cornerCounter + 3; i++)
            {
                Corner *corner = new Corner(i);
                board[row][col].corners.push_back(corner);
                corner->neighborTiles.push_back(&board[row][col]);
                updated = i;
            }
            cornerCounter = updated - 1;
        }
        if (row == 0 || row == 1)
        {
            cornerCounter += 2;
        }
        if (row == 2)
        {
            cornerCounter += 3;
        }
        if (row == 3)
        {
            cornerCounter += 4;
        }
    }
    cornerCounter = 8;
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            int updated;
            for (int i = cornerCounter; i < cornerCounter + 3; i++)
            {
                Corner *corner = new Corner(i);
                corner->cornerId = i;
                board[row][col].corners.push_back(corner);
                corner->neighborTiles.push_back(&board[row][col]);
                updated = i;
            }
            cornerCounter = updated - 1;
        }
        if (row == 0)
        {
            cornerCounter += 4;
        }
        if (row == 1)
        {
            cornerCounter += 3;
        }
        if (row == 2)
        {
            cornerCounter += 2;
        }
        if (row == 3)
        {
            cornerCounter += 2;
        }
    }

    //@brief Initialize the roads of the board
    // The roads are represented as an array in the tile struct
    // The roads are initialized in a predefined order
    // Each tile has 6 roads, begining from the top left corner and continuing clockwise
    // step 1 - initialize the top part of the tiles
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (boardRoads[roadCounter]->roadId == -1)
            {
                Road *road1 = new Road();
                road1->roadId = roadCounter;
                boardRoads[roadCounter] = road1;
            }
            board[row][col].roads[0] = boardRoads[roadCounter];
            roadCounter++;

            if (boardRoads[roadCounter]->roadId == -1)
            {
                Road *road2 = new Road();
                road2->roadId = roadCounter;
                boardRoads[roadCounter] = road2;
            }
            board[row][col].roads[1] = boardRoads[roadCounter];
        }
        if (roadCounter == 5)
        {
            roadCounter += 5;
        }
        else if (roadCounter == 17)
        {
            roadCounter += 6;
        }
        else if (roadCounter == 32)
        {
            roadCounter += 8;
        }
        else if (roadCounter == 47)
        {
            roadCounter += 8;
        }
        else if (roadCounter == 60)
        {
            continue;
        }
        else
        {
            throw "something went wrong with the roadCounter";
        }
    }
    // step 2 - initialize the middle part of the tiles
    // the indexes of the road array are a bit confusing because of the way the roads are initialized inside the tiles
    roadCounter = 6;
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (boardRoads[roadCounter]->roadId == -1)
            {
                Road *road1 = new Road();
                road1->roadId = roadCounter;
                boardRoads[roadCounter] = road1;
            }
            board[row][col].roads[5] = boardRoads[roadCounter];
            roadCounter++;

            if (boardRoads[roadCounter]->roadId == -1)
            {
                Road *road2 = new Road();
                road2->roadId = roadCounter;
                boardRoads[roadCounter] = road2;
            }
            board[row][col].roads[2] = boardRoads[roadCounter];
        }
        if (roadCounter == 9)
        {
            roadCounter += 9;
        }
        else if (roadCounter == 22)
        {
            roadCounter += 11;
        }
        else if (roadCounter == 38)
        {
            roadCounter += 11;
        }
        else if (roadCounter == 53)
        {
            roadCounter += 9;
        }
        else if (roadCounter == 65)
        {
            continue;
        }
        else
        {
            throw "something went wrong with the roadCounter";
        }
    }
    // step 3 - initialize the bottom part of the tiles
    roadCounter = 11;
    for (int row = 0; row < 5; row++)

    {
        for (int col = 0; col < 5; col++)
        {
            if (boardRoads[roadCounter]->roadId == -1)
            {
                Road *road1 = new Road();
                road1->roadId = roadCounter;
                boardRoads[roadCounter] = road1;
            }
            board[row][col].roads[4] = boardRoads[roadCounter];
            roadCounter++;

            if (boardRoads[roadCounter]->roadId == -1)
            {
                Road *road2 = new Road();
                road2->roadId = roadCounter;
                boardRoads[roadCounter] = road2;
            }
            board[row][col].roads[3] = boardRoads[roadCounter];
        }
        if (roadCounter == 16)
        {
            roadCounter += 8;
        }
        else if (roadCounter == 31)
        {
            roadCounter += 8;
        }
        else if (roadCounter == 48)
        {
            roadCounter += 6;
        }
        else if (roadCounter == 61)
        {
            roadCounter += 5;
        }
        else if (roadCounter == 71)
        {
            continue;
        }
        else
        {
            throw "something went wrong with the roadCounter";
        }
    }

    //@brief Initialize the neighbors of each Corner
    // The neighbors of a corner are the corners that are close to the corner
    // The neighbors are represented as a vector in the corner struct
    // The neighbors are initialized when the corners are initialized
    // neighbours have to be in the same tile

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            for (int i = 0; i < 6; i++)
            {
                // We will check if the corner is the first, last or in the middle of the array
                // We will also check if we already added the neighbor to the corner
                Corner *currentCorner = board[row][col].corners[i];
                if (i == 0)
                {
                    if (!currentCorner->isNeighbor(board[row][col].corners[5]))
                    {
                        currentCorner->neighbors.push_back(board[row][col].corners[5]);
                    }
                    if (!currentCorner->isNeighbor(board[row][col].corners[1]))
                    {
                        currentCorner->neighbors.push_back(board[row][col].corners[1]);
                    }
                }
                else if (i == 5)
                {
                    if (!currentCorner->isNeighbor(board[row][col].corners[4]))
                    {
                        currentCorner->neighbors.push_back(board[row][col].corners[4]);
                    }
                    if (!currentCorner->isNeighbor(board[row][col].corners[0]))
                    {
                        currentCorner->neighbors.push_back(board[row][col].corners[0]);
                    }
                }
                else
                {
                    if (!currentCorner->isNeighbor(board[row][col].corners[i - 1]))
                    {
                        currentCorner->neighbors.push_back(board[row][col].corners[i - 1]);
                    }
                    if (!currentCorner->isNeighbor(board[row][col].corners[i + 1]))
                    {
                        currentCorner->neighbors.push_back(board[row][col].corners[i + 1]);
                    }
                }
            }
        }
    }

    //@brief Initialize the neighbors of each Road
    // The neighbors of a road are the roads that are close to the road
    // The neighbors are represented as a vector in the road struct
    // The neighbors are initialized when the roads are initialized
    // neighbours have to be in the same tile

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            for (int i = 0; i < 6; i++)
            {
                Road *currentRoad = board[row][col].roads[i];
                // We will check if the road is the first, last or in the middle of the array
                // We will also check if we already added the neighbor to the road
                if (i == 0)
                {
                    if (!currentRoad->isNeighbor(board[row][col].roads[5]))
                    {
                        currentRoad->neighbors.push_back(board[row][col].roads[5]);
                    }
                    if (!currentRoad->isNeighbor(board[row][col].roads[1]))
                    {
                        currentRoad->neighbors.push_back(board[row][col].roads[1]);
                    }
                }
                else if (i == 5)
                {
                    if (!currentRoad->isNeighbor(board[row][col].roads[4]))
                    {
                        currentRoad->neighbors.push_back(board[row][col].roads[4]);
                    }
                    if (!currentRoad->isNeighbor(board[row][col].roads[0]))
                    {
                        currentRoad->neighbors.push_back(board[row][col].roads[0]);
                    }
                }
                else
                {
                    if (!currentRoad->isNeighbor(board[row][col].roads[i - 1]))
                    {
                        currentRoad->neighbors.push_back(board[row][col].roads[i - 1]);
                    }
                    if (!currentRoad->isNeighbor(board[row][col].roads[i + 1]))
                    {
                        currentRoad->neighbors.push_back(board[row][col].roads[i + 1]);
                    }
                }
            }
        }
    }

    //@brief Initialize the corner's neighbor roads
    // The neighbor roads of a corner are the roads that are leads to the corner
    // The neighbor roads are represented as a vector in the corner struct
    // The neighbor roads are initialized when the corners are initialized
    // neighbors have to be in the same tile

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            Tile *tile = &board[row][col];
            for (int i = 0; i < 6; i++)
            {
                Corner *currentCorner = new Corner(*tile->corners[i]);
                // We will check if the corner is the first, last or in the middle of the array
                // We will also check if we already added the neighbor to the corner
                if (i == 0)
                {
                    if (!currentCorner->isNeighborRoad(tile->roads[5]))
                    {
                        currentCorner->neighborRoads.push_back(tile->roads[5]);
                    }
                    if (!currentCorner->isNeighborRoad(tile->roads[0]))
                    {
                        currentCorner->neighborRoads.push_back(tile->roads[0]);
                    }
                }
                else if (i == 5)
                {
                    if (!currentCorner->isNeighborRoad(tile->roads[4]))
                    {
                        currentCorner->neighborRoads.push_back(tile->roads[4]);
                    }
                    if (!currentCorner->isNeighborRoad(tile->roads[5]))
                    {
                        currentCorner->neighborRoads.push_back(tile->roads[5]);
                    }
                }
                else
                {
                    if (!currentCorner->isNeighborRoad(tile->roads[i - 1]))
                    {
                        currentCorner->neighborRoads.push_back(tile->roads[i - 1]);
                    }
                    if (!currentCorner->isNeighborRoad(tile->roads[i]))
                    {
                        currentCorner->neighborRoads.push_back(tile->roads[i]);
                    }
                }
            }
        }
    }
}

void Board::printBoard() const
{
    //@brief Print the board
    // The board is printed as a 2D array
    // Each tile is printed with its dice sum number and resource type

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            cout << board[row][col].diceSumNumber << " ";
            cout << resourceTypeToString(board[row][col].resourceType) << " ";
        }
        cout << endl;
    }
}

void Board::setRobber(int row, int col)
{
    //@brief Set the robber on a tile
    // The robber is a special piece that can be placed on a tile
    // The robber is used to block the resource production of a tile
    // The robber is represented as a boolean in the tile struct
    // The robber is moved from one tile to another, cannot be placed on the same tile twice
    if (board[row][col].hasRobber && board[row][col].resourceType == DESERT)
    {
        throw "Robber can not be placed on this tile, please choose another tile.";
    }
    robbered.hasRobber = false;
    robbered = board[row][col];
    board[row][col].hasRobber = true;
}

void Board::setRoad(int row, int col, int roadIndex, int playerID)
{
    //@brief Set a road on a tile
    // The road is a piece that can be placed on a tile
    // The road is used to connect two corners
    // The road is represented as a struct in the tile struct

    isValidRoad(row, col, roadIndex, playerID);
    board[row][col].roads[roadIndex]->isOccupied = true;
    board[row][col].roads[roadIndex]->playerID = playerID;
}

void Board::isValidRoad(int row, int col, int roadIndex, int playerID) const
{
    //@brief Check if a road is valid
    // The road is valid if it is not occupied and if it is close to a road that belongs to the player
    // The road is represented as a struct in the tile struct

    if (board[row][col].roads[roadIndex]->isOccupied)
    {
        throw "Road is already occupied, please choose another road.";
    }
    bool flag = false;
    for (int i = 0; i < 6; i++)
    {
        if (boardRoads[roadIndex]->neighbors[i]->playerID == playerID)
        {
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        throw "Player does not have a road in the neighboring road, please choose another road.";
    }
}

void Board::setCorner(int row, int col, int cornerIndex, string homeType, int playerID)
{
    //@brief Set a corner on a tile
    // The corner is a piece that can be placed on a tile
    // The corner is used to build settlements and cities
    // The corner is represented as a struct in the tile struct

    isValidCorner(row, col, cornerIndex, playerID);
    board[row][col].corners[cornerIndex]->isOccupied = true;
    board[row][col].corners[cornerIndex]->playerID = playerID;
    board[row][col].corners[cornerIndex]->homeType = homeType;
    // when setting a corner we need to update the neighbors of the corner that a corner was set, including neighboring tiles with their corners close to the corner that was set
    updateNeighbors(row, col, cornerIndex);
}

void Board::setFirstSettlements(int row, int col, int cornerIndex, int playerID)
{
    //@brief a player sets 2 settlements in his first turn, alongside 1 roads connected for each settlement
    // Only check if the settlements is not occupied or too close
    // Does not check if a road is connected as it is the first placement

    if (board[row][col].corners[cornerIndex]->isOccupied)
    {
        throw "Corner is already occupied, please choose another corner.";
    }
    if (board[row][col].corners[cornerIndex]->isNeighborCornerOccupied)
    {
        throw "Neighboring corner is occupied, please choose another corner.";
    }

    board[row][col].corners[cornerIndex]->isOccupied = true;
    board[row][col].corners[cornerIndex]->playerID = playerID;
    board[row][col].corners[cornerIndex]->homeType = "Settlement";
    updateNeighbors(row, col, cornerIndex);
}

void Board::isValidCorner(int row, int col, int cornerIndex, int playerID) const
{
    //@brief Check if a corner is valid
    // The corner is valid if it is not occupied and if it is not too close to another corner
    // The corner is represented as a struct in the tile struct
    // The corner is also valid if it is close to a road that belongs to the player

    if (board[row][col].corners[cornerIndex]->isOccupied)
    {
        throw "Corner is already occupied, please choose another corner.";
    }
    if (board[row][col].corners[cornerIndex]->isNeighborCornerOccupied)
    {
        throw "Neighboring corner is occupied, please choose another corner.";
    }
    bool flag = false;
    for (Road *neighbor : board[row][col].corners[cornerIndex]->neighborRoads)
    {
        if (neighbor->playerID == playerID)
        {
            flag = true;
        }
    }
    if (!flag)
    {
        throw "Player does not have a road in the neighboring road, please choose another corner.";
    }
}

void Board::updateNeighbors(int row, int col, int cornerIndex)
{
    //@brief Update the neighbors of a corner
    // The neighbors of a corner are the corners that are close to the corner
    // The neighbors are represented as a vector in the corner struct
    // The neighbors are updated when a corner is set

    for (Corner *neighbor : board[row][col].corners[cornerIndex]->neighbors)
    {
        neighbor->isNeighborCornerOccupied = true;
    }
}

int Board::getCornerId(int row, int col, int cornerIndex)
{
    return board[row][col].corners[cornerIndex]->cornerId;
}

int Board::getRoadId(int row, int col, int roadIndex)
{
    return board[row][col].roads[roadIndex]->roadId;
}

Tile *Board::getTile(int row, int col)
{
    return &board[row][col];
}

string Board::resourceTypeToString(ResourceType resourceType) const
{
    //@brief Convert resource type to string
    // The resource type is an enum, this function converts it to a string
    // The string is used for printing the board

    switch (resourceType)
    {
    case WOOD:
        return "WOOD";
    case BRICK:
        return "BRICK";
    case SHEEP:
        return "SHEEP";
    case WHEAT:
        return "WHEAT";
    case ORE:
        return "ORE";
    case DESERT:
        return "DESERT";
    default:
        return "NONE";
    }
}

Board::~Board()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 6; k++)
            {
                delete board[i][j].corners[k];
                delete board[i][j].roads[k];
            }
        }
    }
}

