#include "controller.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "SDL.h"
#include "snake.h"

/*
  These files define the Controller class. 
  This class handles keyboard input using the SDL libary, 
  and it sets the snake's direction based on the input.
*/

void Controller::ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) 
{
  if (snake.GetDirection() != opposite || snake.Size() == 1) snake.SetDirection(input);
  return;
}

void Controller::HandleInput(bool &running, Snake &snake) 
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) 
  {
    if (e.type == SDL_QUIT) {
      running = false;
    } 
    else if (e.type == SDL_KEYDOWN) 
    {
      switch (e.key.keysym.sym) 
      {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}