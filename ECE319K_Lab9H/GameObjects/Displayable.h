#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H
#include "./Constants.h"
#include <cstdint> 
 
class Displayable {
protected:
    const uint16_t* image;
    uint8_t x;
    uint8_t y; 

public: 
    Displayable();
    Displayable(const uint16_t* image, uint8_t xPos, uint8_t yPos);

    virtual ~Displayable();
     
    const uint16_t* getImage() const;  
    void setImage(const uint16_t *img);
    void setX(uint8_t xPos); 
    void setY(uint8_t yPos);
    uint8_t getX() const;
    uint8_t getY() const;
    void setPosition(uint8_t xPos, uint8_t yPos);

};

#endif
