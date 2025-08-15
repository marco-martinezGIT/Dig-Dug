#include "GameBoard.h"
#include "Constants.h"
#include "Tile.h"
#include "BitResource.h"
#include <cstdint>
#include "../../inc/Clock.h"
#include "Enemy.h"

Tile GameBoard::boardArr[GRID_ROWS][GRID_COLS];

Tile (&GameBoard::getBoardArr())[GRID_ROWS][GRID_COLS] {
    return boardArr;
}

void GameBoard::updateTile(uint8_t x, uint8_t y) {
    int col = x / TILE_WIDTH;
    int row = y / TILE_LENGTH;

    if (col >= 0 && col < GRID_COLS && row >= 0 && row < GRID_ROWS) {
        Tile& tile = boardArr[row][col];

        if (tile.getImageIndex() < BROKEN_BLOCK_OFFSET) {
            int newIndex = tile.getImageIndex() + BROKEN_BLOCK_OFFSET;
            tile.setImageIndex(newIndex);
            tile.setImage(blocks_arr[newIndex]);
        }

        tile.drawTile();
    }
}

void GameBoard::board_init() {
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            int idx = (row / 3 > 2) ? 2 : (row / 3);
            boardArr[row][col].setImageIndex(idx);
            boardArr[row][col].setY(row * TILE_LENGTH);
            boardArr[row][col].setX(col * TILE_WIDTH);

            if (row == 1 && col >= 1 && col <= 3) {
                boardArr[row][col].setImageIndex(3);
                boardArr[row][col].setBroken(true);
            }if(row == 9){
            if(col >= 5 && col <= 7){
                int newIndex = boardArr[row][col].getImageIndex() + BROKEN_BLOCK_OFFSET;
                boardArr[row][col].setImageIndex(newIndex);
                boardArr[row][col].setImage(blocks_arr[newIndex]);
            }
        }
        }
    }

    printBoard();
}

void GameBoard::printBoard() {
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            boardArr[row][col].drawTile();
        }
    }
}

void GameBoard::followEnemyPath(Enemy *enemy, std::queue<std::pair<int, int>>* path, bool canTunnel) {
    Tile (&tiles)[GRID_ROWS][GRID_COLS] = getBoardArr();
    int enemyCol = enemy->getX() / TILE_WIDTH;
    int enemyRow = enemy->getY() / TILE_LENGTH;
    int breakCount = 0;

    printf("Enemy start: (%d, %d)\n", enemyRow, enemyCol);
    printf("Following path:\n");

    while (!path->empty()) {
        std::pair<int, int> step = path->front();
        path->pop();

        int targetRow = step.first;
        int targetCol = step.second;

        if (targetRow < 0 || targetRow >= GRID_ROWS || targetCol < 0 || targetCol >= GRID_COLS) {
            continue;
        }

        Tile& targetTile = tiles[targetRow][targetCol];
        bool isBroken = targetTile.isBroken();

        if (canTunnel && !isBroken) {
            if (breakCount < 4) {
                targetTile.setBroken(true);
                breakCount++;
            } else {
                break;
            }
        }

        if (!canTunnel && !isBroken) continue;

        int deltaCol = targetCol - enemyCol;
        if (deltaCol != 0) {
            int dirX = (deltaCol > 0) ? 1 : -1;
            for (int i = 0; i < abs(deltaCol); ++i) {
                enemy->clearBehind(*this);
                enemyCol += dirX;
                enemy->setX(enemyCol * TILE_WIDTH);
                enemy->drawCharacter();
                Clock_Delay1ms(10);
            }
        }

        int deltaRow = targetRow - enemyRow;
        if (deltaRow != 0) {
            int dirY = (deltaRow > 0) ? 1 : -1;
            for (int i = 0; i < abs(deltaRow); ++i) {
                enemy->clearBehind(*this);
                enemyRow += dirY;
                enemy->setY(enemyRow * TILE_LENGTH);
                enemy->drawCharacter();
                Clock_Delay1ms(10);
            }
        }
    }
}

Character* GameBoard::spawnPlayer(int row, int col, Enemy *e) {
    Character* player = new Character(true, 3, taizo_stand, col * TILE_WIDTH, row * TILE_LENGTH, 0);
    Character::monster = e;
    player->drawCharacter();

    return player;
}

Enemy* GameBoard::spawnMonster(int row, int col) {
    Enemy* monster = new Enemy(col * TILE_WIDTH, row * TILE_LENGTH, false);
    monster->drawCharacter();
    return monster;
}
