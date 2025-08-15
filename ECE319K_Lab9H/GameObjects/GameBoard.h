#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Character.h"
#include "Displayable.h"
#include "BitResource.h"
#include "Tile.h"
#include <cstdint>
#include "./Constants.h"
#include <queue>
#include <utility>

class Character;
class Enemy;

class GameBoard : public Displayable {
private:  
    static Tile boardArr[GRID_ROWS][GRID_COLS];  
 
public:
    void updateTile(uint8_t x, uint8_t y); 
    void board_init();
    void printTile(Tile *t);
    void printBoard();  
    static Tile (&getBoardArr())[GRID_ROWS][GRID_COLS];
    void followEnemyPath(Enemy *enemy, std::queue<std::pair<int, int>>* path, bool canTunnel);
    Enemy* spawnMonster(int spawnX, int spawnY);
    Character* spawnPlayer(int row, int col, Enemy *e);
};

#endif
