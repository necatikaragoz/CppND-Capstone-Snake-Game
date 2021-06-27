#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include <iostream>

class FoodCls
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
        FT_LAST_ENUM_NO
    };

    SDL_Point mPoint;
    FoodType  mType;
    bool visible;

    // member protoypes

    FoodCls(FoodType type);

    FoodCls(SDL_Point point, FoodType type);

    FoodCls(int x, int y, FoodType type);

    SDL_Point GetPoint() {return mPoint;}

    FoodType GetType() {return mType;}

    void SetPoints(int x, int y);

    void SetRectangle(SDL_Rect &rect);
    
private:


};


#endif  /* End of FOOD_H */