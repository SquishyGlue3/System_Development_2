

#include <iostream>
#include <vector>
#include <string>
#include "Player.hpp"
#include "Board.hpp"
#include "Corner.hpp"
#include "ResourceType.hpp"
#include "Road.hpp"
#include "SpecialCards.hpp"
#include "Tile.hpp"
#include <array>

using namespace std;
// create board pointer
Board *board = new Board();
vector<Player*> players;
Player *hasLongetRoad = nullptr;
Player *hasLargestArmy = nullptr;

void Board::dealResource(int diceSum)
{
    if (diceSum == 7)
    {
        for (Player* player : players)
        {
            if (player->getPlayerResources().size() > 7)
            {
                player->loseHalfResources();
            }
        }
        return;
    }
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (board[row][col].diceSumNumber == diceSum && !board[row][col].hasRobber)
            {
                for (Corner *corner : board[row][col].corners)
                {
                    if (corner->isOccupied)
                    {
                        if (corner->homeType == "Settlement")
                        {
                            for (Player* player : players)
                            {
                                if (player->getPlayerID() == corner->playerID)
                                {
                                    player->setPlayerResources(board[row][col].resourceType, 1);
                                    break;
                                }
                            }
                        }
                        else if (corner->homeType == "City")
                        {
                            for (Player* player : players)
                            {
                                if (player->getPlayerID() == corner->playerID)
                                {
                                    player->setPlayerResources(board[row][col].resourceType, 2);
                                    break;
                                }
                            }
                        }
                        else
                        {
                            cout << "in corner " << corner->cornerId << " in tile" << row << "," << col << endl;
                            throw invalid_argument("Invalid home type was assigned to this corner");
                        }
                    }
                }
            }
        }
    }
}

void checkLongestRoad()
{
    int max = 0;
    if (hasLongetRoad != nullptr)
    {
        max = hasLongetRoad->getPlayerRoads().size();
    }
    for (Player* player : players)
    {
        if (player->getPlayerRoads().size() > max)
        {
            max = player->getPlayerRoads().size();
            hasLongetRoad->setPlayerScore(hasLongetRoad->getPlayerScore() - 2);
            hasLongetRoad = player;
            hasLongetRoad->setPlayerScore(hasLongetRoad->getPlayerScore() + 2);
        }
    }
}

void checkLargestArmy()
{
    int max = 0;
    if (hasLargestArmy != nullptr)
    {
        max = hasLargestArmy->getKnights();
    }
    for (Player* player : players)
    {
        if (player->getKnights() > max)
        {
            max = player->getKnights();
            hasLargestArmy->setPlayerScore(hasLargestArmy->getPlayerScore() - 2);
            hasLargestArmy = player;
            hasLargestArmy->setPlayerScore(hasLargestArmy->getPlayerScore() + 2);
        }
    }
}

void useRobber(Player player)
{
    vector<Player*> playerOnTile;
        // move the robber
        int row, col;
        cout << "Robber is moving, please enter the new location of the robber" << endl;
        cin >> row >> col;
        board->setRobber(row, col);
        for(Corner* corner : board->getTile(row, col)->corners)
        {
            if(corner->isOccupied && corner->playerID != player.getPlayerID())
            {
                playerOnTile.push_back(players[corner->playerID]); // add the player(instance!) to the list
            }
        }
        if(playerOnTile.size() > 0)
        {
            cout << "Please choose a player to steal from" << endl;
            int choice;
            cin >> choice;
            player.steal(*playerOnTile[choice]);
        }
}

int rollDice(Player player)
{
    // rolling 2 dices and add them up
    int n1 = rand() % 6 + 1;
    int n2 = rand() % 6 + 1;
    if (n1 + n2 == 7)
    {
        useRobber(player);
    }
    return n1 + n2;
}

void useKnight(Player player)
{
    useRobber(player);
}

int main()
{
    Player p1 = Player(1, "Rotem");
    Player p2 = Player(2, "Dor");
    Player p3 = Player(3, "Dan");

    players.push_back(&p1);
    players.push_back(&p2);
    players.push_back(&p3);

    // player 1 turn
    board->setFirstSettlements(0, 0, 3, p1.getPlayerID()); // which is index 10 in the board
    p1.setSettlement(10);                                  // it will sit next to wood, sheep and ore
    board->setRoad(0, 0, 3, p1.getPlayerID());             // which is index 12 in the board
    p1.setPlayerRoad(12);

    // player 2 turn
    board->setFirstSettlements(1, 2, 1, p2.getPlayerID()); // which is index 12 in the board
    p2.setSettlement(12);                                  // it will sit next to sheep, brick and wood
    board->setRoad(1, 2, 1, p2.getPlayerID());             // which is index 15 in the board
    p2.setPlayerRoad(15);

    // player 3 turn
    board->setFirstSettlements(0, 0, 5, p3.getPlayerID()); // which is index 8 in the board
    p3.setSettlement(8);                                   // it will sit next to wood and wheat
    board->setRoad(0, 0, 4, p3.getPlayerID());             // which is index 11 in the board
    p3.setPlayerRoad(11);
    //-------------Now is the second round of setting settlements, which will give resources--------------------
    // player 3 turn
    board->setFirstSettlements(2, 0, 2, p3.getPlayerID()); // which is index 17 in the board
    p3.setSettlement(17);                                  // it will sit next to wheat, brick and wheat
    int size1 = board->getTile(2, 0)->corners[2]->neighborTiles.size();
    for (int i = 0; i < size1; i++)
    {
        p3.setPlayerResources(board->getTile(2, 0)->corners[2]->neighborTiles[i]->resourceType, 1); // will get 2 wheat and 1 brick
    }
    board->setRoad(2, 0, 1, p3.getPlayerID()); // which is index 24 in the board
    p3.setPlayerRoad(24);

    // player 2 turn
    board->setFirstSettlements(3, 3, 1, p2.getPlayerID()); // which is index 35
    p2.setSettlement(35);                                  // it will sit next to ore, wood and ore
    int size2 = board->getTile(2, 0)->corners[2]->neighborTiles.size();
    for (int i = 0; i < size2; i++)
    {
        p2.setPlayerResources(board->getTile(2, 0)->corners[2]->neighborTiles[i]->resourceType, 1); //  will get 2 ore and 1 wood
    }
    board->setRoad(3, 3, 0, p2.getPlayerID()); // which is index 47
    p2.setPlayerRoad(47);

    // player 1 turn
    board->setFirstSettlements(4, 2, 0, p1.getPlayerID()); // which is index 43
    p1.setSettlement(43);                                  // it will sit next to wheat, sheep and brick
    int size3 = board->getTile(2, 0)->corners[2]->neighborTiles.size();
    for (int i = 0; i < size3; i++)
    {
        p1.setPlayerResources(board->getTile(2, 0)->corners[2]->neighborTiles[i]->resourceType, 1); //  will get 1 wheat, 1 sheep and 1 brick
    }
    board->setRoad(4, 2, 0, p1.getPlayerID()); // which is index 59
    p1.setPlayerRoad(59);

    //----------------end of first round, only setting first settlements and roads----------------

    // right now p1 has 1 wheat, 1 sheep, 1 brick
    // p2 has 2 ore, 1 wood
    // p3 has 2 wheat, 1 brick

    // player 1 turn
    board->dealResource(rollDice(p1)); // result will be 5, p2 will get ore

    // player 2 turn
    board->dealResource(rollDice(p2)); // result will be 5, p2 will get ore

    // player 3 turn
    board->dealResource(rollDice(p3)); // result will be 10, p3 will get 1 wood, p1 will get 1 wood
    if (p3.buyRoad())                  // can p3 buy a road?
    {
        board->setRoad(1, 0, 2, p3.getPlayerID()); // which is index 19
        p3.setPlayerRoad(19);                      // p3 bought a road
    }

    //-----------------------------------End of the second round---------------------------------------

    // player 1 turn
    board->dealResource(rollDice(p1)); // result will be 9, p2 will get 1 brick, p3 will get 1 brick
    if (p1.buyRoad())                  // can p1 buy a road?
    {
        board->setRoad(4, 2, 1, p1.getPlayerID()); // which is index 60
        p1.setPlayerRoad(60);                      // p1 bought a road
    }

    // player 2 turn
    board->dealResource(rollDice(p2)); // result will be 10,  p1 will get 1 wood, p3 will get 1 wood

    // player 3 turn
    board->dealResource(rollDice(p3));                           // result will be 10,  p1 will get 1 wood, p3 will get 1 wood
    try
    {
        p3.tradePlayer(p1, ResourceType::WOOD, ResourceType::SHEEP); // p3 will trade 1 wood for 1 sheep
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    if (p3.buySettlement())                                      // can p3 buy a settlement?
    {
        board->setCorner(1, 0, 3, "Settlement", p3.getPlayerID()); // which is index 19
        p3.setSettlement(19);                                      // p3 bought a settlement
    }

    //-----------------------------------End of the third round---------------------------------------

    board->dealResource(rollDice(p1)); // result will be 10, p1 will get 1 wood, p3 will get 1 wood

    board->dealResource(rollDice(p2)); // result will be 6, p1 will get 1 ore, p3 will get 1 ore, p2 will get 1 sheep

    board->dealResource(rollDice(p3)); // result will be 9, p2 will get 1 brick, p3 will get 1 brick

    board->dealResource(rollDice(p1)); // result will be 11, p2 will get 1 brick, p3 will get 1 wheat

    board->dealResource(rollDice(p2)); // result will be 7, the robber will be moved, p2 will lose half of his resources

    board->dealResource(rollDice(p3)); // result will be 4, p2 will get 1 wood, p1 will get 1 wheat

    //----------------Couple of more turns in between...----------------
    p1.setPlayerScore(9);
    p2.setPlayerScore(6);
    p3.setPlayerScore(8);
    p3.setKnights(3);
    p2.setKnights(2);
    p1.setKnights(1);

    p2.setPlayerRoad(36);
    p2.setPlayerRoad(29);

    p1.setPlayerRoad(58);
    p1.setPlayerRoad(51);
    p1.setPlayerRoad(43);

    hasLongetRoad = &p1;
    hasLargestArmy = &p3;

    //----------------Last turn of the Game...----------------
    // player 2 turn
    p2.rollDice();           // result will be 10
    board->dealResource(10); // p2 will get 1 wood, p3 will get 1 wood..
    if (p2.buySpecial())     // can p2 buy a special card?
    {
        p2.setSpecialCard(SpecialCard::KNIGHT); // p2 bought a special card
        checkLargestArmy();
    }
    if (p2.buySpecial()) // can p2 buy a special card?
    {
        p2.setSpecialCard(SpecialCard::KNIGHT); // p2 bought a special card and achieved the largest army
        checkLargestArmy();
        useKnight(p2);
    }

    p2.setPlayerScore(p2.getPlayerScore() + 2); // p2 has 8 points now
    p3.setPlayerScore(p3.getPlayerScore() - 2); // p3 has 6 points now
    if (p2.buyRoad())                           // can p2 buy a road?
    {
        board->setRoad(2, 3, 3, p2.getPlayerID());
        p2.setPlayerRoad(21); // p2 bought a road and achieved the longest road
        checkLongestRoad();
    }
    p1.setPlayerScore(p1.getPlayerScore() - 2); // p1 has 7 points now
    p2.setPlayerScore(p2.getPlayerScore() + 2); // p2 has 10 points now

    // Game should be finished now

    return 0;
}
