#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "SDL.h"
#include <MessageQueue.h>
#include <thread>


class Controller {
 public:

  enum PlayingStatus{PS_stop, PS_running, PS_exit, RS_restart};

  void HandleInput(Controller::PlayingStatus &status, std::shared_ptr<Snake> pSnake) ;
  

 private:

  std::unique_ptr<std::thread> mpController_thread;

  void ChangeDirection(std::shared_ptr<Snake> pSnake, Snake::Direction input,
                       Snake::Direction opposite);

  void MessageBoxOnPlaying(Controller::PlayingStatus &status);  
  void MessageBoxOnKill(Controller::PlayingStatus &status);

  
};

#endif /* End of CONTROLLER_H */