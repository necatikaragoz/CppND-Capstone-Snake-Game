#include "controller.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "SDL.h"
#include "snake.h"
#include "ColorCls.h"

/*
  These files define the Controller class. 
  This class handles keyboard input using the SDL libary, 
  and it sets the snake's direction based on the input.
*/

void Controller::ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite)
{
  if (snake.GetDirection() != opposite || snake.Size() == 1)
    snake.SetDirection(input);
  return;
}

void Controller::HandleInput(bool &running, Snake &snake)
{

  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
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
      case SDLK_ESCAPE:
      case SDLK_p:
        /*SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                         "Paused",
                         "You've paused the game. Click OK to resume.",
                         NULL);*/
          MessageBoxOnPlaying();
        break;
      }
    }
  }
}

void Controller::MessageBoxOnPlaying()
{
  const SDL_MessageBoxButtonData buttons[] = {
      //{/* .flags, .buttonid, .text */ 0, 0, "no"},
      {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes"},
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Exit teh Game"},
      { 0, 3, "New Game"}
  };

  const SDL_MessageBoxColorScheme colorScheme = {
      {/* .colors (.r, .g, .b) */
       /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
       GameColor::ColorCls::BoxColor(GameColor::Silver),
       /* [SDL_MESSAGEBOX_COLOR_TEXT] */
       GameColor::ColorCls::BoxColor(GameColor::Black),
       /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
       GameColor::ColorCls::BoxColor(GameColor::Blue),
       /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
       GameColor::ColorCls::BoxColor(GameColor::Blue),
       /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
       GameColor::ColorCls::BoxColor(GameColor::Pink)
       }
       };

  const SDL_MessageBoxData messageboxdata = {
      SDL_MESSAGEBOX_INFORMATION, /* .flags */
      NULL,                       /* .window */
      "Game Paused",      /* .title */
      "You've paused the game. Click OK to resume.", /* .message */
      SDL_arraysize(buttons),     /* .numbuttons */
      buttons,                    /* .buttons */
      &colorScheme                /* .colorScheme */
  };

  int buttonid;
  SDL_ShowMessageBox(&messageboxdata, &buttonid);

  std::cout << "buttonId = " << buttonid;
}