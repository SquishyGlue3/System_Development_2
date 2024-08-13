#include "Player.hpp"
#include "ResourceType.hpp"
#include "Road.hpp"
#include "Board.hpp"
#include <map>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Player::Player(int playerID, string playerName)
{
    this->playerID = playerID;
    this->playerName = playerName;
}

// copy constructor
Player::Player(const Player &other)
{
    playerID = other.playerID;
    playerName = other.playerName;
}

Player::~Player()
{
}

void Player::setPlayerID(int playerID)
{
    this->playerID = playerID;
}

void Player::setPlayerName(string playerName)
{
    this->playerName = playerName;
}

void Player::setPlayerScore(int playerScore)
{
    this->playerScore = playerScore;
    if (playerScore >= 10)
    {
        // the player has won the game
        cout << "Player " << playerName << " has won the game!" << endl;
    }
}

void Player::setPlayerResources(ResourceType resource, int amount) // amount could be 1 or 2 only
{
    if (amount == 1)
    {
        playerResources.push_back(resource);
    }
    else
    {
        playerResources.push_back(resource);
        playerResources.push_back(resource);
    }
}

void Player::loseHalfResources()
{
    srand(time(0));
    int half = playerResources.size() / 2; // if it is odd, we will round down
    for (int i = 0; i < half; i++)
    {
        playerResources.erase(playerResources.begin() + (rand() % playerResources.size()));
    }
}

void Player::setPlayerRoad(int roadIndex)
{
    playerRoads.push_back(roadIndex);
}

void Player::setSettlement(int boardCornerIndex)
{
    // now we will enter "Settlement" as a string in the correct place by the cornerIndex, at the map playerBuildings
    // we will also update the playerScore
    playerBuildings[boardCornerIndex] = "Settlement";
    this->setPlayerScore(playerScore + 1);
}

void Player::setCity(int boardCornerIndex)
{
    // now we will enter "City" as a string in the correct place by the cornerIndex, at the vector playerBuildings
    // we will also update the playerScore
    playerBuildings[boardCornerIndex] = "City";
    this->setPlayerScore(playerScore + 1);
}

void Player::setSpecialCard(SpecialCard card)
{
    specialCards.push_back(card);
}

void Player::setKnights(int knights)
{
    this->knights = knights;
}

vector<ResourceType> Player::getPlayerResources() const
{
    return playerResources;
}

int Player::getKnights()
{
    return knights;
}

bool Player::buySpecial()
{
    bool hasOre = false;
    bool hasSheep = false;
    bool hasWheat = false;
    for (int i = 0; i < playerResources.size(); i++)
    {
        if (playerResources[i] == ResourceType::ORE && !hasOre)
        {
            hasOre = true;
            playerResources.erase(playerResources.begin() + i);
            continue;
        }
        if (playerResources[i] == ResourceType::SHEEP && !hasSheep)
        {
            hasSheep = true;
            playerResources.erase(playerResources.begin() + i);
            continue;
        }
        if (playerResources[i] == ResourceType::WHEAT && !hasWheat)
        {
            hasWheat = true;
            playerResources.erase(playerResources.begin() + i);
            continue;
        }
    }
    if (hasOre && hasSheep && hasWheat)
    {
        return true;
    }
    if (hasOre)
    {
        playerResources.push_back(ResourceType::ORE);
    }
    if (hasSheep)
    {
        playerResources.push_back(ResourceType::SHEEP);
    }
    if (hasWheat)
    {
        playerResources.push_back(ResourceType::WHEAT);
    }
    return false;
}

bool Player::buyRoad()
{
    bool hasBrick = false;
    bool hasWood = false;
    for (int i = 0; i < playerResources.size(); i++)
    {
        if (playerResources[i] == ResourceType::BRICK && !hasBrick)
        {
            hasBrick = true;
            playerResources.erase(playerResources.begin() + i);
        }
        if (playerResources[i] == ResourceType::WOOD && !hasWood)
        {
            hasWood = true;
            playerResources.erase(playerResources.begin() + i);
        }
    }
    if (hasBrick && hasWood)
    {
        return true;
    }
    if (hasBrick) // if the player has only one of the resources, we will return it to the playerResources vector
    {
        playerResources.push_back(ResourceType::BRICK);
    }
    if (hasWood) // if the player has only one of the resources, we will return it to the playerResources vector
    {
        playerResources.push_back(ResourceType::WOOD);
    }
    return false;
}

bool Player::buySettlement()
{
    bool hasBrick = false;
    bool hasWood = false;
    bool hasWheat = false;
    bool hasSheep = false;
    for (int i = 0; i < playerResources.size(); i++)
    {
        if (playerResources[i] == ResourceType::BRICK && !hasBrick)
        {
            hasBrick = true;
            playerResources.erase(playerResources.begin() + i);
        }
        if (playerResources[i] == ResourceType::WOOD && !hasWood)
        {
            hasWood = true;
            playerResources.erase(playerResources.begin() + i);
        }
        if (playerResources[i] == ResourceType::WHEAT && !hasWheat)
        {
            hasWheat = true;
            playerResources.erase(playerResources.begin() + i);
        }
        if (playerResources[i] == ResourceType::SHEEP && !hasSheep)
        {
            hasSheep = true;
            playerResources.erase(playerResources.begin() + i);
        }
    }
    if (hasBrick && hasWood && hasWheat && hasSheep)
    {
        return true;
    }
    if (hasBrick) // if the player has only one of the resources, we will return it to the playerResources vector
    {
        playerResources.push_back(ResourceType::BRICK);
    }
    if (hasWood) // if the player has only one of the resources, we will return it to the playerResources vector
    {
        playerResources.push_back(ResourceType::WOOD);
    }
    if (hasWheat) // if the player has only one of the resources, we will return it to the playerResources vector
    {
        playerResources.push_back(ResourceType::WHEAT);
    }
    if (hasSheep) // if the player has only one of the resources, we will return it to the playerResources vector
    {
        playerResources.push_back(ResourceType::SHEEP);
    }
    return false;
}

int Player::getPlayerID() const
{
    return playerID;
}

string Player::getPlayerName() const
{
    return playerName;
}

int Player::getPlayerCardsSum() const
{
    return playerResources.size();
}

vector<int> Player::getPlayerRoads() const
{
    return playerRoads;
}

map<int, string> Player::getPlayerBuildings() const
{
    return playerBuildings;
}

int Player::getPlayerScore() const
{
    return playerScore;
}

vector<SpecialCard> Player::getSpecialCards()
{
    return specialCards;
}

void Player::trade4For1(ResourceType resource, ResourceType wantedResource)
{
    int count = 0;
    // the player will trade 4 of the same resource for 1 of any other resource
    for (int i = 0; i < playerResources.size(); i++)
    {
        if (count == 4)
        {
            playerResources.push_back(wantedResource);
            return;
        }
        if (playerResources[i] == resource)
        {
            count++;
            playerResources.erase(playerResources.begin() + i);
        }
    }
    // if the player doesn't have 4 of the same resource, we will return the resource to the playerResources vector
    if (count < 4)
    {
        for (int i = 0; i < count; i++)
        {
            playerResources.push_back(resource);
        }
    }
    throw invalid_argument("Player doesn't have 4 of the same resource");
}

void Player::tradePlayer(Player &player2, ResourceType resource, ResourceType wantedResource)
{
    bool found1 = false;
    bool found2 = false;
    for (int i = 0; i < playerResources.size(); i++)
    {
        if (playerResources[i] == resource)
        {
            found1 = true;
            playerResources.erase(playerResources.begin() + i);
            break;
        }
    }
    for (int i = 0; i < player2.playerResources.size(); i++)
    {
        if (player2.playerResources[i] == wantedResource)
        {
            found2 = true;
            player2.playerResources.erase(player2.playerResources.begin() + i);
            break;
        }
    }
    switch (found1 && found2)
    {
        case true:
            break;
        case false:
            if (found1)
            {
                playerResources.push_back(resource);
            }
            if (found2)
            {
                player2.playerResources.push_back(wantedResource);
            }
            throw invalid_argument("Player doesn't have the requested resource");
    }
    playerResources.push_back(wantedResource);
    player2.playerResources.push_back(resource);
}

void Player::steal(Player &player2)
{
    int index = rand() % player2.playerResources.size();
    playerResources.push_back(player2.playerResources[index]);
    player2.playerResources.erase(player2.playerResources.begin() + index);
}
