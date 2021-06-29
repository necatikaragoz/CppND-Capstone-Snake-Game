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
#include <thread>

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

  PlaceFood(FoodCls::FT_FEED);
}

void Game::Run(Controller &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

    mpFood_thread = std::make_unique<std::thread>(&Game::FoodThread, this);
    mpFood_thread.get()->detach();

    mpHungry_thread = std::make_unique<std::thread>(&Game::HungryThread, this);
    mpHungry_thread.get()->detach();

   // std::thread tHungry(&Game::, this, FoodCls::FT_HAZARDOUS);
    //tHazard.detach();

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
      renderer.UpdateWindowTitle(score, frame_count, mpLogScore->GetHighestScore(), (snake.Speed() * 10));
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

void Game::PlaceFood(FoodCls::FoodType foodType) {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.

    if (CheckFoodLocation (x,y,foodType) && !snake.SnakeCell(x, y)) {
      mFoods[foodType].SetPoints(x,y);

      return;
    }
  }
}

bool Game::CheckFoodLocation(int x, int y, FoodCls::FoodType foodType)
{
  for(int i = 0; i< FoodCls::FT_LAST_ENUM_NO; i++)
  {
    if(foodType == static_cast<FoodCls::FoodType>(i))
    {
      continue;
    }
    else if( (mFoods[i].visible && (mFoods[i].GetPoint().x == x) && (mFoods[i].GetPoint().y == y ) ) )
    {
      return false;     
    }
  }
  return true;
}

void Game::Update() 
{
  if (!snake.Alive()) 
  {
    return;
  }

  //first: snake location must be updated
  snake.Update();

  // Check if there's food over here
  if (CheckIntersection(FoodCls::FT_FEED)) 
  {
    score++;
    mpLogScore->UpdateHighestScore(score);
    PlaceFood(FoodCls::FT_FEED);
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.ChangeSpeed(0.02);
  } 
  else if(CheckIntersection(FoodCls::FT_HAZARDOUS))
  {
    if(score > 1)
    {
      score--;
    }
    snake.ReduceBody();
    mFoods[FoodCls::FT_HAZARDOUS].visible = false;
  
  }
  else if(CheckIntersection(FoodCls::FT_COLD))
  {
    score++;
    mpLogScore->UpdateHighestScore(score);
    snake.GrowBody();
    snake.ChangeSpeed(-0.04);
    mFoods[FoodCls::FT_COLD].visible = false;
  
  }
  else if(CheckIntersection(FoodCls::FT_HOT))
  {
    score++;
    mpLogScore->UpdateHighestScore(score);
    snake.GrowBody();
    snake.ChangeSpeed(0.04);
    mFoods[FoodCls::FT_HOT].visible = false;
  }
  else if(CheckIntersection(FoodCls::FT_KILL))
  {
    mFoods[FoodCls::FT_KILL].visible = false;
    snake.Kill();
  }

}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.Size(); }


void Game::FoodThread()
{
    auto begin  =  std::chrono::steady_clock::now();  //std::chrono::steady_clock::now();
     
    // random number generate
    std::uniform_int_distribution<int> distr(0, 10); // define the range
    int randomWaitMs = distr(engine);
  
    //Check the time 
    while(true)
    {
      // wait with 1 ms resolution
      std::this_thread::sleep_for(std::chrono::milliseconds(1));

      std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - begin;

      // if the tiem is excited then change the mode
      if(elapsed.count() >= randomWaitMs)
      {
        // update time 
        begin = std::chrono::steady_clock::now();
        //update phase and send message
        UpdateFood();

        randomWaitMs = distr(engine);
      }
    }
}


void Game::UpdateFood()
{
  static int foodType = FoodCls::FT_HAZARDOUS;

  for(int i = FoodCls::FT_HAZARDOUS ; i< FoodCls::FT_LAST_ENUM_NO; i++)
  {
    mFoods[i].visible = false;
  }

  if(snake.Alive())
  {
    PlaceFood(static_cast<FoodCls::FoodType>(RandomFoodFinder()) );
  }
  

}

int Game::RandomFoodFinder()
{
  std::uniform_int_distribution<> distr(1, static_cast<int>(FoodCls::FT_LAST_ENUM_NO)-1 ); // define the range

  return (distr(engine));
}


bool Game::CheckIntersection(int foodNo)
{        
  //Check that snake eat a food or not
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  if( mFoods[foodNo].visible && (mFoods[foodNo].mPoint.x == new_x) && (mFoods[foodNo].mPoint.y == new_y) )
  {
    
    return true;
  }
  
  return false;
}



void Game::HungryThread()
{

}