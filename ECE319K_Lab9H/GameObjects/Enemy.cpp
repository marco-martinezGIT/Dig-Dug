#include "Enemy.h"
#include "BitResource.h"

Enemy::Enemy() : Character(false, 1, monster1, 0, 0, 0), canTunnel(false){}

Enemy::Enemy(uint8_t x, uint8_t y, bool cond) : Character(false, 1, monster1, x, y, 0), canTunnel(cond) {}

void Enemy::toggleBreak(bool cond) {
    canTunnel = cond;
}

bool Enemy::canBreak() const {
    return canTunnel;
}

uint8_t Enemy::getCol() const {
    return (x + BOX_SIZE / 2) / TILE_WIDTH;
}

uint8_t Enemy::getRow() const {
    return (y + BOX_SIZE / 2) / TILE_LENGTH;
}

void Enemy::setRow(int r) {
    y = r * TILE_LENGTH + TILE_LENGTH / 2 - BOX_SIZE / 2;
}

void Enemy::setCol(int c) {
    x = c * TILE_WIDTH + TILE_WIDTH / 2 - BOX_SIZE / 2;
}
