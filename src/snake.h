#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "Animal.h"
#include <iostream>

class Snake : public Animal{
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {
        }

  ~Snake()
  {
  }

  void Update();
  bool Alive() const { return alive; } 
  float Speed() const { return speed; } 
  int   Size() const { return body.size(); } 
  Direction  GetDirection() const { return direction; } 
  void SetDirection(Direction dir)  { direction = dir; }
  void GrowBody();
  void ReduceBody();
  void Kill();
  bool SnakeCell(int x, int y);
  void ChangeSpeed(float spd);

  void ResetSnake();


  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  Direction direction = Direction::kUp;

  int grid_width;
  int grid_height;

  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);


};

#endif