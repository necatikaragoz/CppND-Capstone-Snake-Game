#include "renderer.h"
#include <iostream>
#include <string>
#include "FoodCls.h"
#include "ColorCls.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      sdl_window(nullptr, SDL_DestroyWindow),
      sdl_renderer(nullptr, SDL_DestroyRenderer)
      {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window.reset(SDL_CreateWindow("Snake Game modified by Necati KARAGÖZ", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN) );

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer.reset(SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED) );
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  mvFoodcolors.push_back(GameColor::FoodFeed);
  mvFoodcolors.push_back(GameColor::FoodHazard);
  mvFoodcolors.push_back(GameColor::FoodKill);
  mvFoodcolors.push_back(GameColor::FoodCold);
  mvFoodcolors.push_back(GameColor::FoodHot);
  
}

Renderer::~Renderer() {
  //not needed any more because of the unique ptr
  //SDL_DestroyWindow();
  SDL_Quit();
}

void Renderer::Render(std::shared_ptr<Snake> const  pSnake, std::vector<FoodCls> &foods) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SetColor(GameColor::Dark);
  SDL_RenderClear(sdl_renderer.get());

  // Render foods
  DrawFoods(block, foods);

  // Render snake's body
  SetColor(GameColor::SnakeBody);
  for (SDL_Point const &point : pSnake.get()->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // Render snake's head
  block.x = static_cast<int>(pSnake.get()->head_x) * block.w;
  block.y = static_cast<int>(pSnake.get()->head_y) * block.h;
  if (pSnake.get()->Alive()) {
    //SDL_SetRenderDrawColor(sdl_renderer.get(), 0x00, 0x7A, 0xCC, 0xFF);
    SetColor(GameColor::HeadAlive);
  } else {
    //SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
    SetColor(GameColor::HeadKill);
  }
  SDL_RenderFillRect(sdl_renderer.get(), &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer.get());
}

void Renderer::UpdateWindowTitle(int score, int fps, int highestScore, float speed) {
  std::string title{"Snake Score: " + std::to_string(score) + " -- HighestScore: " + std::to_string(highestScore) + " -- Speed: " + std::to_string(speed)   + " -- FPS: " + std::to_string(fps) };
  SDL_SetWindowTitle(sdl_window.get(), title.c_str());
}


void Renderer::SetColor(GameColor::ColorCls color)
{
  SDL_SetRenderDrawColor(sdl_renderer.get(), color.Red(), color.Green(), color.Blue(), color.Alpha() );
}


void Renderer::DrawFoods(SDL_Rect block, std::vector<FoodCls> &foods)
{
  for(int i = FoodCls::FT_FEED ; i< FoodCls::FT_LAST_ENUM_NO; i++)
  {
    if(foods[i].visible)
   {
        SetColor(mvFoodcolors.at(i));
        block.x = foods[i].mPoint.x * block.w;
        block.y = foods[i].mPoint.y * block.h;
        SDL_RenderFillRect(sdl_renderer.get(), &block);
   }
  }
}


void Renderer::LoadFileOnTheScreen()
{

  SDL_Surface *pSurface  = SDL_GetWindowSurface(sdl_window.get());
  SDL_Surface *pImage = SDL_LoadBMP("../image.bmp");

    SDL_Rect block;
    if (pImage == nullptr)
    {
      std::cout << "SDL could not load the image! SDL Error: " << SDL_GetError() << std::endl;
    }
    else
    {
      block.x = (screen_width - pImage->w) / 2;
      block.y = (screen_height - pImage->h) / 2;

      SDL_BlitSurface(pImage, NULL, pSurface, &block);
      SDL_UpdateWindowSurface(sdl_window.get());
    }

    return;
}
