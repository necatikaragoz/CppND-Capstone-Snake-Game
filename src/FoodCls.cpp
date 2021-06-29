
/*
  This file define the Food type and it's specs. 
  This file holds the food unqie paramteres.
*/

#include <FoodCls.h>

    FoodCls::FoodCls(FoodType type)
    {
        Initialize(type);
    }

    FoodCls::FoodCls(SDL_Point point, FoodType type)
    {
        mPoint = point;
        Initialize(type);
    }

    FoodCls::FoodCls(int x, int y, FoodType type)
    {
        mPoint.x = x;
        mPoint.y = y;
        Initialize(type);

    }

    void FoodCls::Initialize(FoodType type)
    {
        mType = type;
        visible = false;

        mpConVar = std::make_unique<std::condition_variable>();
    }

    void FoodCls::SetPoints(int x, int y) { mPoint.x = x; mPoint.y = y; visible = true; }

    void FoodCls::SetRectangle(SDL_Rect &rect)
    {
        rect.x = mPoint.x * rect.w;     
        rect.y = mPoint.y * rect.h;
    }