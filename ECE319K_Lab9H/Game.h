#ifndef GAME_H
#define GAME_H

#include "GameObjects/Character.h"
#include "GameObjects/Enemy.h"
#include "Switch.h"
#include "Constants.h"
#include "GameObjects/GameBoard.h"

void handleCollision(Character& user, Enemy& monster, GameBoard &board, uint32_t &score) ;
void resetCharacter(Character& user, GameBoard &board);
void resetEnemy(Enemy& monster, GameBoard &board);
bool checkCollision(Character &player, Enemy &monster);
void showGameOver();  
#endif
