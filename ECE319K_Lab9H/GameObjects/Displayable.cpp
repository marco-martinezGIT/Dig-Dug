#include "Displayable.h"
#include "BitResource.h"
#include <cstdint>

Displayable::Displayable() : x(0), y(0), image(block_7) {}

Displayable::Displayable(const uint16_t *img, uint8_t xPos, uint8_t yPos) : image(img), x(xPos), y(yPos){ }

Displayable::~Displayable() {}   

void Displayable::setX(uint8_t xPos) {
    x = xPos;
} 

void Displayable::setY(uint8_t yPos) {
    y = yPos;
} 

uint8_t Displayable::getX() const {
    return x;
}

uint8_t Displayable::getY() const {
    return y;  
}

const uint16_t* Displayable::getImage() const {
    return image;
}

void Displayable::setImage(const uint16_t *img){
    image = img;
}

void Displayable::setPosition(uint8_t xPos, uint8_t yPos) {
    x = xPos;
    y = yPos;
}
   
 