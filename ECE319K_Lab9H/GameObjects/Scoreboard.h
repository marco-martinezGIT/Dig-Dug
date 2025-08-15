#include "GameObjects/Displayable.h"
#include "./Constants.h"
class Scoreboard : public Displayable{
    private:
    
    public:
    int score;

    Scoreboard() : Displayable(nullptr, 0, 0);
    
    void incrementScore(int inc_score = 0);
    void resetScore();

}