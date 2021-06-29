#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "SDL.h"
#include <MessageQueue.h>
#include <thread>


class Controller {
 public:

  enum PlayingStatus{PS_stop, PS_running};

  void HandleInput(Controller::PlayingStatus &status, Snake &snake) ;
  

 private:

  std::unique_ptr<std::thread> mpController_thread;

  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite);

  void MessageBoxOnPlaying();  

  
};

#endif /* End of CONTROLLER_H */