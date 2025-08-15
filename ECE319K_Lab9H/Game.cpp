#include "Game.h"
#include "Switch.h"
#include "Constants.h"
#include "GameObjects/Character.h"
#include "../inc/ST7735.h"
#include "BitResource.h"
#include "GameObjects/GameBoard.h"

extern uint8_t language;

void handleCollision(Character& user, Enemy& monster, GameBoard &board, uint32_t &score) {
    
    if (switchActive(27)) {
        user.clearBehind(board);
        monster.clearBehind(board);
        resetEnemy(monster, board);
        user.drawCharacter();
        score += 150;
    }
    else {
        user.decrementLives(board);
        if (user.getLives() > 0) {
            user.clearBehind(board);
            resetCharacter(user, board);
            monster.clearBehind(board);
            resetEnemy(monster, board);
            monster.deathCounter -=1;
        }
    }
}

void resetCharacter(Character& user, GameBoard &board) {
    user.respawn(board);
    user.setX(GRID_COLS / 2 * TILE_WIDTH);
    user.setY(GRID_ROWS / 2 * TILE_LENGTH);
    user.setFacing(0);
    user.drawCharacter();
}

void resetEnemy(Enemy& monster, GameBoard &board) {
    board.updateTile(monster.getCol() * BOX_SIZE, monster.getRow() * BOX_SIZE);
    if(monster.deathCounter % 2 == 0){
    //monster.respawn(board);
    monster.setImage(monsters[0]);
    monster.setX(2 * TILE_WIDTH);
    monster.setY(1 * TILE_LENGTH);
    monster.drawCharacter();
    }else if(monster.deathCounter % 2 == 1){
        
       monster.setImage(monsters[1]);
        monster.setX(6 * TILE_WIDTH);
        monster.setY(9 * TILE_LENGTH);
        monster.drawCharacter();
    }
     monster.deathCounter++;
    
}


bool checkCollision(Character &player, Enemy &monster) {
    uint8_t playerX = player.getX();
    uint8_t playerY = player.getY();
    uint8_t monsterX = monster.getX();
    uint8_t monsterY = monster.getY();
    uint8_t playerWidth = BOX_SIZE;
    uint8_t playerHeight = BOX_SIZE;
    uint8_t monsterWidth = BOX_SIZE;
    uint8_t monsterHeight = BOX_SIZE;

    bool collisionX = playerX < monsterX + monsterWidth && playerX + playerWidth > monsterX;
    bool collisionY = playerY < monsterY + monsterHeight && playerY + playerHeight > monsterY;

    return collisionX && collisionY;  
}

void showGameOver() {
    const char gameoverE[] = "Game Over!";
    const char gameoverS[] = "¡Juego terminado!";
    const char *gameOverMessage[2] = {gameoverE, gameoverS};
    if (language) ST7735_DrawString(2, 7, (char*)gameOverMessage[language], ST7735_WHITE);
    else ST7735_DrawString(6, 7, (char*)gameOverMessage[language], ST7735_WHITE);
}