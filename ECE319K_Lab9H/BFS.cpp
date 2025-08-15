#include "BFS.h"
#include "GameObjects/GameBoard.h"
#include <cstdlib>

const int dx[4] = { -1, 0, 1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

bool BFS::isValid(int row, int col) {
    return row >= 0 && col >= 0 && row < GRID_ROWS && col < GRID_COLS;
}

void BFS::animateStepFrame(AnimationState &anim, Enemy *monster, GameBoard *board, uint32_t *counter) {
    if (anim.isAnimating) {
        monster->setRow(anim.toRow);
        monster->setCol(anim.toCol);
        monster->clearBehind(*board);
        anim.isAnimating = false;
    }
}

void BFS::randomStepTowardPlayer(int &mRow, int &mCol, int pRow, int pCol, GameBoard* board, Enemy* enemy, uint32_t *counter, AnimationState &anim) {
    std::pair<int, int> directions[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

    for (int i = 3; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(directions[i], directions[j]);
    }

    Tile (&tiles)[GRID_ROWS][GRID_COLS] = board->getBoardArr();

    int currDist = abs(pRow - mRow) + abs(pCol - mCol);

    bool moved = false;

    for (int i = 0; i < 4; ++i) {
        int nRow = mRow + directions[i].first;
        int nCol = mCol + directions[i].second;

        if (isValid(nRow, nCol) && tiles[nRow][nCol].isBroken()) {
            int newDist = abs(pRow - nRow) + abs(pCol - nCol);

            if (newDist < currDist) {
                enemy->clearBehind(*board);
                anim = AnimationState(true, mRow, mCol, nRow, nCol, 0);
                moved = true;
                break;
            }
        }
    }

    if (!moved) {
        for (int i = 0; i < 4; ++i) {
            int nRow = mRow + directions[i].first;
            int nCol = mCol + directions[i].second;

            if (isValid(nRow, nCol) && tiles[nRow][nCol].isBroken()) {
                enemy->clearBehind(*board);
                anim = AnimationState(true, mRow, mCol, nRow, nCol, 0);
                if(mRow > nRow){
                    enemy->setFacing((1 << 2));
                }else if(mRow < nRow){
                     enemy->setFacing((1 << 3));

                }else if(mCol > nCol){
                    enemy->setFacing((1 << 1));
                }else if(mCol < nCol){
                    enemy->setFacing((1 << 0));
                }
                moved = true;
                break;
            }
        }
    }

    if (!moved) {
        anim.isAnimating = false;
    }

    if (anim.isAnimating) {
        if (anim.frame < 10) {
            mRow += (anim.toRow - mRow) / 10;
            mCol += (anim.toCol - mCol) / 10;
            anim.frame++;
        } else {
            mRow = anim.toRow;
            mCol = anim.toCol;
            anim.isAnimating = false;
        }
    }
}
