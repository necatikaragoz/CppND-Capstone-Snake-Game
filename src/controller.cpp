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

void Controller::ChangeDirection(std::shared_ptr<Snake> pSnake, Snake::Direction input, Snake::Direction opposite)
{
  if (pSnake.get()->GetDirection() != opposite || pSnake.get()->Size() == 1)
    pSnake.get()->SetDirection(input);
  return;
}

void Controller::HandleInput(Controller::PlayingStatus &status, std::shared_ptr<Snake> pSnake)
{
  SDL_Event e;
  if(! pSnake.get()->Alive() )
  {
    MessageBoxOnKill(status);
  }
  
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      MessageBoxOnKill(status);
    }
    else if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_UP:
        ChangeDirection(pSnake, Snake::Direction::kUp,
                        Snake::Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(pSnake, Snake::Direction::kDown,
                        Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(pSnake, Snake::Direction::kLeft,
                        Snake::Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(pSnake, Snake::Direction::kRight,
                        Snake::Direction::kLeft);
        break;
      case SDLK_ESCAPE:
      case SDLK_p:
        /*SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                         "Paused",
                         "You've paused the game. Click OK to resume.",
                         NULL);*/
          MessageBoxOnPlaying(status);
        break;
      }
    }
  }
}


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

void Controller::MessageBoxOnPlaying(Controller::PlayingStatus &status)
{
  const SDL_MessageBoxButtonData buttons[] = {
      //{/* .flags, .buttonid, .text */ 0, 0, "no"},
      {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, static_cast<int>(PS_running), "Yes"},
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, static_cast<int>(PS_exit), "Exit the Game"},
      { 0, static_cast<int>(RS_restart), "New Game"}
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
  status =  static_cast<PlayingStatus>(buttonid);
}


void Controller::MessageBoxOnKill(Controller::PlayingStatus &status)
{

  const SDL_MessageBoxButtonData buttons[] = {
      //{/* .flags, .buttonid, .text */ 0, 0, "no"},
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, static_cast<int>(PS_exit), "Exit the Game"},
      { 0, static_cast<int>(RS_restart), "New Game"}
  };

  const SDL_MessageBoxData messageboxdata = {
      SDL_MESSAGEBOX_INFORMATION, /* .flags */
      NULL,                       /* .window */
      "Game Over",      /* .title */
      "Oops... Snake killed. ", /* .message */
      SDL_arraysize(buttons),     /* .numbuttons */
      buttons,                    /* .buttons */
      &colorScheme                /* .colorScheme */
  };

  int buttonid;
  SDL_ShowMessageBox(&messageboxdata, &buttonid);
  status =  static_cast<PlayingStatus>(buttonid);  

}

