
#include <FoodCls.h>

    FoodCls::FoodCls(FoodType type)
    {
        mType = type;
        visible = false;
    }

    FoodCls::FoodCls(SDL_Point point, FoodType type)
    {
        mPoint = point;
        mType = type;
        visible = false;
    }

    FoodCls::FoodCls(int x, int y, FoodType type)
    {
        mPoint.x = x;
        mPoint.y = y;
        mType = type;
        visible = false;
    }

    void FoodCls::SetPoints(int x, int y) { mPoint.x = x; mPoint.y = y;}

    void FoodCls::SetRectangle(SDL_Rect &rect)
    {
        rect.x = mPoint.x;     
        rect.y = mPoint.y; 
    }