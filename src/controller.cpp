#include "controller.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "SDL.h"
#include "snake.h"


template <typename T>
T MessageQueue2<T>::receive()
{
    
    // perform queue modification under the lock
    std::unique_lock<std::mutex> uLock(_mutex);

    _cond.wait(uLock, [this] { return !_messages.empty(); }); // pass unique lock to condition variable

    // remove last vector element from queue
    T msg = std::move(_messages.back());
    _messages.pop_back();

    return msg; // will not be copied due to return value optimization (RVO) in C++

}

template <typename T>
void MessageQueue2<T>::send(T &&msg)
{
    // simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // perform vector modification under the lock
    std::lock_guard<std::mutex> uLock(_mutex);

    // add vector to queue
    _messages.push_back(std::move(msg));
    _cond.notify_one(); // notify client after pushing new Vehicle into vector
}

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


void Controller::Initialize()
{
  mpController_thread = std::make_unique<std::thread>(&Controller::ControllerThread, this);
  mpController_thread.get()->detach();
}


void Controller::HandleInput(bool &running, Snake &snake) 
{
  SDL_Event e = mMessageQueue.receive();
  //int i = mMessageQueue.receive();
  //SDL_Event e;
  //while (SDL_PollEvent(&e)) 
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


void Controller::ControllerThread()
{
  //Check the time 
  while(true)
  {
    // wait with 1 ms resolution
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    UpdatePhase();
  }
}


void Controller::UpdatePhase()
{
  SDL_Event e;
  e.type = SDL_FIRSTEVENT;
  int i;

  if(SDL_PollEvent(&e))
  {
    mMessageQueue.send(std::move(e) );
  }
}

