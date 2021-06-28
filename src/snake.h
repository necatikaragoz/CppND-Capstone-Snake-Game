#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  enum class Growing { kNone, kDelete, kGrowing, kReduce};

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();
  bool Alive() const { return alive; } 
  float Speed() const { return speed; } 
  int   Size() const { return size; } 
  Direction   GetDirection() const { return direction; } 
  void SetDirection(Direction dir)  { direction = dir; }
  void GrowBody();
  void ReduceBody();
  void Kill();
  bool SnakeCell(int x, int y);
  void ChangeSpeed(float spd);

  Direction direction = Direction::kUp;

  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:

  int size{1};
  float speed{0.1f};
  bool alive{true};
  Growing growing{Growing::kNone};
  int grid_width;
  int grid_height;

  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);


};

#endif