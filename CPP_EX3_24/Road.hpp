#ifndef ROAD_HPP
#define ROAD_HPP

//@brief Road struct
// The road struct represent a Road placed on a Tile
struct Road
{
    int roadId = -1;
    int playerID = -1;
    bool isOccupied = false;
    vector <Road*> neighbors;

    bool isNeighbor(Road* road)
    {
        for (Road* neighbor : neighbors)
        {
            if (neighbor == road)
            {
                return true;
            }
        }
        return false;
    }

    Road& operator=(const Road& other)
    {
        roadId = other.roadId;
        playerID = other.playerID;
        isOccupied = other.isOccupied;
        return *this;
    }

    Road() = default;
    ~Road() {};
};

#endif // ROAD_HPP