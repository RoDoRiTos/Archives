#include "collision.hpp"

bool Collision::MouseToBox(Vec2f mouse_pos, Box box){
  if (mouse_pos.x() >= box.pos.x() && mouse_pos.x() <= box.pos.x() + box.size.x()){
    if (mouse_pos.y() >= box.pos.y() && mouse_pos.y() <= box.pos.y() + box.size.y()){
      return true;
    }
  }
  return false;
}