/*
These files define the Game class and the game loop: Game::Run.
The Game class stores the state of the game, including an instance of a Snake object, 
the game score, and the location of "food" in the game. 
Aside from the game loop, the Game class also contains methods to update the state of the game (Game::Update), 
get the size of the snake, get the total score in the game, 
and place new food in the game if the food has been eaten by the snake.
*/

#include "game.h"
#include <iostream>
#include "SDL.h"
#include <string>
#include <random>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
        
      Initialize();
}

void Game::Initialize()
{
  mpLogScore = std::make_unique<LogScore>();
  
  mpLogScore->ReadHighestScoreFromfile();

  // add all foods to vector
  for(int i = 0; i< FoodCls::FT_LAST_ENUM_NO; i++)
  {
    mFoods.push_back(FoodCls(static_cast<FoodCls::FoodType>(i) ) ); // For 
  }

  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, mFoods);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, mpLogScore->GetHighestScore(), (snake.speed * 10));
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.

    if (!snake.SnakeCell(x, y)) {
      //food.x = x;
      //food.y = y;
      mFoods[FoodCls::FT_FEED].SetPoints(x,y);
      //foods[FoodCls::FT_FEED].x = x;
      //foods[FoodCls::FT_FEED].y = y;

      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  // Check if there's food over here
  if (CheckIntersection(FoodCls::FT_FEED)) {
    score++;
    mpLogScore->UpdateHighestScore(score);
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }


void Game::FoodThread()
{
      std::unique_lock<std::mutex> uniqueLock(mfoodMutex);
    while (true) {
        mConVar.wait(uniqueLock);
        //PlaceFood();
    }
}

int Game::RandomFoodFinder()
{
  std::uniform_int_distribution<> distr(1, static_cast<int>(FoodCls::FT_LAST_ENUM_NO)-1 ); // define the range

  return (distr(engine));
}


bool Game::CheckIntersection(int foodNo)
{        
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  if(mFoods[foodNo].mPoint.x == new_x && mFoods[foodNo].mPoint.y == new_y)
  {
    return true;
  }
  return false;
}
