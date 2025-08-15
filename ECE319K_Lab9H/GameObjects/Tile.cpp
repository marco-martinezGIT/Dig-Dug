#include <cstdint>
#include "Tile.h"
#include "../inc/ST7735.h"
#include "BitResource.h"
#include "Constants.h"
#include "GameObjects/Displayable.h"

Tile::Tile()
    : Displayable(blocks_arr[0], 0, 0), imageIndex(0) {}

Tile::Tile(uint8_t imageIdx)
    : Displayable(blocks_arr[imageIdx], 0, 0), imageIndex(imageIdx) {}

Tile::Tile(const uint16_t* img, uint8_t xPos, uint8_t yPos, uint8_t imageIdx)
    : Displayable(img, xPos, yPos), imageIndex(imageIdx) {}

Tile::~Tile() = default;

void Tile::setImageIndex(uint8_t imageIdx) {
    imageIndex = imageIdx;
    image = blocks_arr[imageIndex];
}

uint8_t Tile::getImageIndex() {
    return imageIndex;
}

uint8_t Tile::getPixelX() const {
    return x;
}

uint8_t Tile::getPixelY() const {
    return y;
}

uint8_t Tile::getCol() const {
    return x / TILE_WIDTH;
}

uint8_t Tile::getRow() const {
    return y / TILE_LENGTH;
}

void Tile::drawTile() {
    ST7735_DrawBitmap(getPixelX(), getPixelY() + Y_OFFSET, image, TILE_WIDTH, TILE_LENGTH);
}

bool Tile::isBroken() const {
    return imageIndex >= BROKEN_BLOCK_OFFSET;
}

void Tile::setBroken(bool state) {
    if (state && imageIndex < BROKEN_BLOCK_OFFSET) {
        imageIndex += BROKEN_BLOCK_OFFSET;
        image = blocks_arr[imageIndex];
    } else if (!state && imageIndex >= BROKEN_BLOCK_OFFSET) {
        imageIndex -= BROKEN_BLOCK_OFFSET;
        image = blocks_arr[imageIndex];
    }
    drawTile();
}

void Tile::setTileX(uint8_t xPos) { x = xPos; }
void Tile::setTileY(uint8_t yPos) { y = yPos; }
