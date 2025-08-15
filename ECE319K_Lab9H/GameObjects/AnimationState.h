#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H

class AnimationState {
public:
    bool isAnimating;
    int fromRow, fromCol; 
    int toRow, toCol;
    int frame;

    AnimationState() : isAnimating(false), fromRow(0), fromCol(0), toRow(0), toCol(0), frame(0) {}

    AnimationState(bool anim, int fRow, int fCol, int tRow, int tCol, int f) :
        isAnimating(anim), fromRow(fRow), fromCol(fCol), toRow(tRow), toCol(tCol), frame(f) {}
};

#endif
