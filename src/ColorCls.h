#ifndef COLORCLS_H
#define COLORCLS_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <memory>
#include "FoodCls.h"


//Rule of five

namespace GameColor
{
  
  class ColorCls
  {

    public: 
    ColorCls( Uint8 r, Uint8 g, Uint8 b,
                    Uint8 a ) : mRed(r), mGreen(g), mBlue(b), mAlpha(a)
                    {
                      
                    }
    ColorCls(Uint32 rgba)
    {
      mRed   = (rgba >> 24) && 0xFF ;
      mGreen = (rgba >> 16) && 0xFF ;
      mBlue  = (rgba >> 8) && 0xFF ;
      mAlpha = rgba && 0xFF ;
    }

    ~ColorCls() {};  //1 : destructor

    ColorCls(const ColorCls &source) // 2 : copy constructor
    {
      mRed   = source.mRed;
      mGreen = source.mGreen;
      mBlue  = source.mBlue;
      mAlpha = source.mAlpha;
    }

    ColorCls &operator=(const ColorCls &source) // 3 : copy assignment operator
    {
      if (this == &source)
        return *this;
      mRed   = source.mRed;
      mGreen = source.mGreen;
      mBlue  = source.mBlue;
      mAlpha = source.mAlpha;

      return *this;
    }

    ColorCls(ColorCls &&source) // 4 : move constructor
    {
      mRed   = source.mRed;
      mGreen = source.mGreen;
      mBlue  = source.mBlue;
      mAlpha = source.mAlpha;

      source.mRed = 0;
      source.mGreen = 0;
      source.mBlue = 0;
      source.mAlpha = 0;
    }


    ColorCls &operator=(ColorCls &&source) // 5 : move assignment operator
    {
      if (this == &source)
        return *this;

      mRed   = source.mRed;
      mGreen = source.mGreen;
      mBlue  = source.mBlue;
      mAlpha = source.mAlpha;

      return *this;
    }

    Uint8 Red() { return mRed; }
    Uint8 Green() { return mGreen; }
    Uint8 Blue() { return mBlue; }
    Uint8 Alpha() { return mAlpha; }

    private:
    Uint8 mRed;
    Uint8 mGreen;
    Uint8 mBlue;
    Uint8 mAlpha;
  };

  
  static ColorCls Dark(0x1E, 0x1E, 0x1E, 0xFF);
  static ColorCls Red(0xFF, 0x00, 0x00, 0xFF);
  static ColorCls Orangered(0xFF, 0x045, 0x00, 0xFF);
  static ColorCls Green(0x00, 0xFF, 0x00, 0xFF);
  static ColorCls Blue(0x00, 0x00, 0xFF, 0xFF);
  static ColorCls Yellow(0xFF, 0xCC, 0x00, 0xFF);
  static ColorCls White(0xFF, 0xFF, 0xFF, 0xFF);
  static ColorCls Black(0x00, 0x00, 0x00, 0xFF);
  static ColorCls Cyan(0x00, 0xFF, 0xFF, 0xFF);
  static ColorCls Aquamarine(0x7F, 0xFF, 0xD4, 0xFF);
  static ColorCls Gold(0xFF, 0xD7, 0x00, 0xFF);
  static ColorCls Chocolate(0xD2, 0x69, 0x1E, 0xFF);
  static ColorCls Silver(0xC0, 0xC0, 0xC0, 0xFF);
  static ColorCls Pink(0xFF, 0xC0, 0xCB, 0xFF);

  static ColorCls HeadAlive(Silver);
  static ColorCls HeadKill(Chocolate);
  static ColorCls SnakeBody(White);
  static ColorCls FoodFeed(Yellow);
  static ColorCls FoodHazard(Orangered);
  static ColorCls FoodKill(Red);
  static ColorCls FoodCold(Cyan);
  static ColorCls FoodHot(Yellow);


}

#endif  /* End of COLORCLS */