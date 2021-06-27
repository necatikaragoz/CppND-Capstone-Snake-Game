#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"

class Food
{

public:
    // member variables
    enum FoodType
    {
        FT_FEED, // for growing the snake +1
        FT_HAZARDOUS, // for shrink snake -1
        FT_KILL, // for killing the snake
        FT_COLD,  // for slow down the shake
        FT_HOT,   // for increase the speed of the snake
    };

    SDL_Point mPoint;
    FoodType  mType;

    // member protoypes
    Food(SDL_Point point, FoodType type)
    {
        mPoint = point;
        mType = type;
    }

    Food(int x, int y, FoodType type)
    {
        mPoint.x = x,
        mPoint.y = y,
        mType = type;
    }

    SDL_Point GetPoint() {return mPoint;}

    FoodType GetType() {return mType;}

    void SetType(FoodType type) {  mType = type; }
    

private:


};


#endif  /* End of FOOD_H */