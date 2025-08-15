#pragma once
#include <cstdint>
#include "GameObjects/Displayable.h"

class Tile : public Displayable {
public:
    Tile();
    Tile(uint8_t imageIdx);
    Tile(const uint16_t* img, uint8_t xPos, uint8_t yPos, uint8_t imageIdx);
    ~Tile();

    void setImageIndex(uint8_t imageIdx);
    uint8_t getImageIndex();

    uint8_t getPixelX() const;
    uint8_t getPixelY() const;

    uint8_t getCol() const;
    uint8_t getRow() const;

    void drawTile();

    bool isBroken() const;
    void setBroken(bool state);

    void setTileX(uint8_t xPos);
    void setTileY(uint8_t yPos);

private:
    uint8_t imageIndex;
};
