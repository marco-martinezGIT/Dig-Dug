#include "Character.h"
#include "../inc/ST7735.h"
#include "Constants.h"
#include "GameBoard.h"
#include "Enemy.h"
#include <cstdint>

class Enemy; 
Character* Character::user = nullptr;
Enemy* Character::monster = nullptr;

Character::Character(bool shoot, uint8_t numLives, const uint16_t *img, uint8_t xPos, uint8_t yPos, uint8_t wasFacing)
    : Displayable(img, xPos, yPos), canShoot(shoot), numLives(numLives), walkCounter(0), wasFacing(wasFacing) {
    up[0] = taizo_stand; up[1] = taizo_stand;
    left[0] = taizo_stand; left[1] = taizo_stand;
    down[0] = taizo_stand; down[1] = taizo_stand;
    right[0] = taizo_stand; right[1] = taizo_stand;
    startX = xPos;
    startY = yPos;
}

Character::~Character() {}
uint8_t Character::getLives() const { return numLives; }
uint8_t Character::getX() const { return x; }
uint8_t Character::getY() const { return y; }
void Character::addX(int8_t xPos) { x += xPos; }
void Character::addY(int8_t yPos) { y += yPos; }
bool Character::getCanShoot() const { return canShoot; }
void Character::setX(uint8_t xVal) { x = xVal; }
void Character::setY(uint8_t yVal) { y = yVal; }
void Character::setLives(uint8_t lives) { numLives = lives; }
void Character::setShoot(bool shoot) { canShoot = shoot; }

void Character::clearBehind(GameBoard &board) {
    int centerX = x + BOX_SIZE / 2;
    int centerY = y + BOX_SIZE / 2;
    int tileCol = centerX / TILE_WIDTH;
    int tileRow = centerY / TILE_LENGTH;
    board.updateTile(centerX, centerY);
    Tile (&tiles)[GRID_ROWS][GRID_COLS] = board.getBoardArr();
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int r = tileRow + dy;
            int c = tileCol + dx;
            if (r >= 0 && r < GRID_ROWS && c >= 0 && c < GRID_COLS) {
                if (r == tileRow && c == tileCol) continue;
                tiles[r][c].drawTile(); 
            }
        }
    }
    user->drawCharacter();
    monster->drawCharacter();
}

bool Character::isXAligned(GameBoard &board) {
    int16_t center = x + BOX_SIZE / 2;
    int16_t snap = ((center) / TILE_SIZE) * TILE_SIZE + TILE_SIZE / 2;
    int16_t diff = center - snap;
    if (diff >= -SNAP_TOLERANCE && diff <= SNAP_TOLERANCE) {
        x = snap - BOX_SIZE / 2; 
        clearBehind(board);
        return true;
    }
    return false;
}

bool Character::isYAligned(GameBoard &board) {
    int16_t center = y + BOX_SIZE / 2;
    int16_t snap = ((center) / TILE_SIZE) * TILE_SIZE + TILE_SIZE / 2;
    int16_t diff = center - snap;
    if (diff >= -SNAP_TOLERANCE && diff <= SNAP_TOLERANCE) {
        y = snap - BOX_SIZE / 2;  
        clearBehind(board);
        return true;
    }
    return false;
}

void Character::drawCharacter() {
    if (image != nullptr) {
        ST7735_DrawBitmap(x, y + Y_OFFSET, image, BOX_SIZE, BOX_SIZE);
    }
}

void Character::moveUp(GameBoard &board) {
    if (isXAligned(board) && y > 0) {
        clearBehind(board);
        y -= SPEED;
        if (wasFacing == (1 << 2)) walkCounter++;
        else { walkCounter = 0; wasFacing = (1 << 2); }
        image = up[walkCounter % 2];
        drawCharacter();
    }
}

void Character::moveDown(GameBoard &board) {
    if (isXAligned(board) && y < 140) {
        clearBehind(board);
        y += SPEED;
        if (wasFacing == (1 << 3)) walkCounter++;
        else { walkCounter = 0; wasFacing = (1 << 3); }
        image = down[walkCounter % 2];
        drawCharacter();
    }
}

void Character::moveLeft(GameBoard &board) {
    if (isYAligned(board) && x > 0) {
        clearBehind(board);
        x -= SPEED;
        if (wasFacing == (1 << 1)) walkCounter++;
        else { walkCounter = 0; wasFacing = (1 << 1); }
        image = left[walkCounter % 2];
        drawCharacter();
    }
}

void Character::moveRight(GameBoard &board) {
    if (isYAligned(board) && x < 114) {
        clearBehind(board);
        x += SPEED;
        if (wasFacing == (1 << 0)) walkCounter++;
        else { walkCounter = 0; wasFacing = (1 << 0); }
        image = right[walkCounter % 2];
        drawCharacter();
    }
}

uint8_t Character::getRow() const {
    return (y + BOX_SIZE / 2) / TILE_SIZE;
}

uint8_t Character::getCol() const {
    return (x + BOX_SIZE / 2) / TILE_SIZE;
}

uint8_t Character::getFacing() const {
    return wasFacing;
}

void Character::decrementLives(GameBoard &board) {
    if (numLives > 0) {
        numLives--;
    }

    if (numLives == 0) {
    } else {
        respawn(board);
    }
}

void Character::respawn(GameBoard &board) {
   clearBehind(board);
    x = startX; 
    y = startY; 
    wasFacing = (1 << 2); 
    canShoot = true; 
    drawCharacter(); 
}

void Character::setFacing(uint8_t facing) {
    wasFacing = facing;
}
void Character::setUser(Character* u) {
    user = u;
}

void Character::setMonster(Enemy* m) {
    monster = m;
}
