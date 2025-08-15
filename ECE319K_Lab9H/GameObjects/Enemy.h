#ifndef ENEMY_H
#define ENEMY_H

#include <cstdint>
#include "GameObjects/Character.h"
#include "BitResource.h"
class GameBoard;

class Enemy : public Character {
private:
    bool canTunnel;

public:
    int deathCounter;

    Enemy();
    Enemy(bool cond);
    Enemy(uint8_t x, uint8_t y, bool cond);

    void toggleBreak(bool cond);
    bool canBreak() const;

    uint8_t getRow() const;
    uint8_t getCol() const;


    void goToTile(GameBoard &board, uint8_t targetCol, uint8_t targetRow);
    void setRow(int r);
    void setCol(int c);

};

#endif
