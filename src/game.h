#ifndef GAME_H
#define GAME_H

#include <random>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "LogScore.h"
#include "FoodCls.h"
#include <thread>

class Game {
 public:

 //member variables

 //member prototypes
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
 //member variables

  Snake snake;
  //SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  std::unique_ptr<LogScore> mpLogScore;
  std::unique_ptr<std::thread> mpFood_thread; 
  std::unique_ptr<std::thread> mpHungry_thread;
  std::vector<FoodCls> mFoods;

//member prototypes
  int  RandomFoodFinder();
  void PlaceFood(FoodCls::FoodType foodType);
  void UpdateFood();
  void Update();
  void Initialize();
  void FoodThread();
  bool CheckIntersection(int foodNo);
  bool CheckFoodLocation(int x, int y, FoodCls::FoodType foodType);
  void HungryThread();


};
#endif