#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include "ResourceType.hpp"
#include "Road.hpp"
#include "SpecialCards.hpp"
#include <map>

using namespace std;

class Player
{
private:
    int playerID;
    string playerName;
    int playerScore;
    vector<ResourceType> playerResources;
    vector<SpecialCard> specialCards;
    map<int, string> playerBuildings;
    vector<int> playerRoads;
    int knights;

public:
    Player(int playerID, string playerName) : playerID(playerID), playerName(playerName) {};
    ~Player() {};

    void setPlayerID(int playerID);
    void setPlayerName(string playerName);
    void setPlayerScore(int playerScore);
    void setPlayerResources(ResourceType resource, int amount);
    void loseHalfResources();
    void setPlayerRoad(int roadIndex);        // we will use row and col to determine the requseted tile, than we will use the roadIndex to determine the requested road
    void setSettlement(int boardCornerIndex); // we will use row and col to determine the requseted tile, than we will use the cornerIndex to determine the requested corner
    void setCity(int boardCornerIndex);       // we will use row and col to determine the requseted tile, than we will use the cornerIndex to determine the requested corner
    void setSpecialCard(SpecialCard specialCard);
    void setKnights(int knights);
    vector<ResourceType> getPlayerResources() const;
    int getKnights();
    bool buySpecial();
    bool buyRoad();
    bool buySettlement();
    vector<SpecialCard> getSpecialCards();
    int getPlayerID() const;
    string getPlayerName() const;
    int getPlayerScore() const;
    int getPlayerCardsSum() const;
    vector<int> getPlayerRoads() const;
    map<int, string> getPlayerBuildings() const;
    int rollDice();
    void trade4For1(ResourceType resource, ResourceType wantedResource);
    void tradePlayer(Player &player, ResourceType resource, ResourceType wantedResource);
    void steal(Player &player2);
};

#endif // PLAYER_HPP
