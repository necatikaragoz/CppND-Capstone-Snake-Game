#ifndef ANIMAL_H
#define ANIMAL_H


/*
  This file define Animal Base Class
*/


#include <vector>

class Animal {
 public:

  enum class Growing { kNone, kDelete, kGrowing, kReduce};

  virtual void Update() = 0;
  virtual bool Alive() const = 0; 
  virtual float Speed() const = 0;
  virtual int   Size() const  = 0; 
  virtual void GrowBody() = 0;
  virtual void ReduceBody() = 0;
  virtual void Kill() = 0;
  virtual void ChangeSpeed(float spd) = 0;

 protected:

  
  int size{1};
  float speed{0.1f};
  bool alive{true};
  Growing growing{Growing::kNone};
};

#endif