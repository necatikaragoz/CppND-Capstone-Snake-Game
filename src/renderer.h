#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <memory>
#include "FoodCls.h"
#include "ColorCls.h"


class Renderer {
 public:
   // member variables

   // member protoypes

  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(std::shared_ptr<Snake> const  pSnake, std::vector<FoodCls> &food);
  void UpdateWindowTitle(int score, int fps, int highestScore, float speed);

  void LoadFileOnTheScreen();  

 private:
  // member variables

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sdl_window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> sdl_renderer;

  std::vector<GameColor::ColorCls> mvFoodcolors;
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

   // member protoypes
  void SetColor(GameColor::ColorCls color);
  void DrawFoods(SDL_Rect block, std::vector<FoodCls> &foods);

};

#endif