#ifndef CHARACTER_H
#define CHARACTER_H

#include <cstdint>
#include "Displayable.h"
#include "BitResource.h"

class Enemy; 
class GameBoard;  

class Character : public Displayable {
public:
    static Character* user;
    static Enemy* monster;

    uint8_t walkCounter;
    uint8_t numLives;
    bool canShoot;
    uint8_t wasFacing;
    uint8_t startX;
    uint8_t startY; 

    const uint16_t* up[2];
    const uint16_t* down[2];
    const uint16_t* left[2];
    const uint16_t* right[2];

    Character(bool shoot, uint8_t numLives, const uint16_t *img, uint8_t xPos, uint8_t yPos, uint8_t wasFacing);
    virtual ~Character();

    uint8_t getLives() const;
    uint8_t getX() const;
    uint8_t getY() const;
    void addX(int8_t xPos);
    void addY(int8_t yPos);
    bool getCanShoot() const;
    void setX(uint8_t xVal);
    void setY(uint8_t yVal);
    void setLives(uint8_t lives);
    void setShoot(bool shoot);

    void clearBehind(GameBoard &board);
    bool isXAligned(GameBoard &board);
    bool isYAligned(GameBoard &board);
    void drawCharacter();
    void moveUp(GameBoard &board);
    void moveDown(GameBoard &board);
    void moveLeft(GameBoard &board);
    void moveRight(GameBoard &board);

    uint8_t getRow() const;
    uint8_t getCol() const;

    uint8_t getStartX() const;
    uint8_t getStartY() const;

    void setStartX(uint8_t x);
    void setStartY(uint8_t y);

    uint8_t getFacing() const;
    void decrementLives(GameBoard &board);
    void setFacing(uint8_t facing);
    void respawn(GameBoard &board);

    static void setUser(Character* u);
    static void setMonster(Enemy* m);
};

#endif
