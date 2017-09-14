#pragma once
#include "donut.hpp"
#include "../Stats/status.hpp"
#include <list>

class Spawner{
private:
  std::list<Donuts> donuts;

  float half_size = doritos::Window::HEIGHT / 2;

  ci::Vec2f* mouse;

  Status* status_ref;

public:
  Spawner();
  void init();
  void setStatusRef(Status* ref);

  void spawnDonut();

  void setMouseRef(ci::Vec2f*);
  bool checkMouse(ci::Vec2f);

  void draw();
  void update();
};
typedef Spawner SpManager;