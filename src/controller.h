#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "SDL.h"
#include <MessageQueue.h>
#include <thread>


class Controller {
 public:

  void HandleInput(bool &running, Snake &snake) ;

  void ControllerThread();
  void Initialize();

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite);

  void UpdatePhase();
    
  std::unique_ptr<std::thread> mpController_thread;
};

#endif /* End of CONTROLLER_H */