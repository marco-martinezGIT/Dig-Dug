#ifndef BFS_H
#define BFS_H

#include "GameObjects/GameBoard.h"
#include "GameObjects/AnimationState.h"
#include "GameObjects/Enemy.h"

class BFS {
public:
    static void animateStepFrame(AnimationState &anim, Enemy *monster, GameBoard *board, uint32_t *counter);
    static void randomStepTowardPlayer(int &mRow, int &mCol, int pRow, int pCol, GameBoard* board, Enemy* enemy, uint32_t *counter, AnimationState &anim);
    static bool isValid(int row, int col);
};

#endif
