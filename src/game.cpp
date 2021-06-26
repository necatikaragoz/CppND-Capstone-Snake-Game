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
#include <fstream>
#include <sstream>
#include <algorithm>

using std::string;

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
  GetHighestScore();
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
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
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
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    UpdateHighestScore(score);
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }


const std::string kScorePath{"./score"};

enum NamesEnum{
  NE_Name,
  NE_Version,
  NE_Language,
  NE_PrettyName,
  NE_Author,
  NE_SrcUrl,
  NE_ForkUrl,
  NE_HighestScore,
  NE_LastEnumNo
};

const std::string kNames[] {
"NAME" , "VERSION" , "LANGUAGE" , "PRETTY_NAME", "AUTHOR" , "SRC_URL" , "FORK_URL" , "HIGHEST_SCORE"
};

void Game::UpdateHighestScore(int score)
{
  if(score > mHighestScore)
  {
    string line;
    string key;
    string value;
    std::ifstream filestream(kScorePath);

    if (filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::replace(line.begin(), line.end(), ' ', '_');
        std::replace(line.begin(), line.end(), '=', ' ');
        std::replace(line.begin(), line.end(), '"', ' ');

        std::istringstream linestream(line);
        while (linestream >> key >> value) {

          std::replace(value.begin(), value.end(), '_', ' ');
          if (key == kNames[NE_HighestScore] ) {

            std::ostringstream outlinestream(line);
            outlinestream << key << "=" << score;
 
            std::cout << outlinestream.str();

            
          }
        }
      }
    }
    else{
      std::cout << "file not found = " << std::endl;
    }
  }
}

void Game::GetHighestScore() 
{ 

  string line;
  string key;
  string value;
  std::ifstream filestream(kScorePath);

  mHighestScore = 0;

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');

      std::istringstream linestream(line);
      while (linestream >> key >> value) {

        std::replace(value.begin(), value.end(), '_', ' ');
        //std::cout << "key = " << key << " value =" << value << std::endl;
        if (key == kNames[NE_HighestScore] ) {
          std::replace(value.begin(), value.end(), '_', ' ');
          //std::cout << "value = " << stoi(value) << std::endl;
         mHighestScore =  stoi(value);
        }
      }
    }
  }
  else{
    std::cout << "file not found = " << std::endl;

  }

}
