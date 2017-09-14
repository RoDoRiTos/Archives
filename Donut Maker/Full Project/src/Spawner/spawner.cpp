#include "spawner.hpp"
#include "cinder/rand.h"

using namespace ci;

SpManager::Spawner(){
  Rand::randomize();

  mouse = nullptr;

  status_ref = nullptr;
}

void SpManager::init(){
  Donuts donut;

  donut.init();

  donuts.push_back(donut);
}

void SpManager::setStatusRef(Status* ref){
  status_ref = ref;
}

void SpManager::spawnDonut(){
  Donuts donut;

  if (status_ref->getUpgQty(UPGRADE5)){
    donut.init(randInt(0, 6));
  }
  else if (status_ref->getUpgQty(UPGRADE4)){
    donut.init(randInt(0, 5));
  }
  else if (status_ref->getUpgQty(UPGRADE3)){
    donut.init(randInt(0, 4));
  }
  else if (status_ref->getUpgQty(UPGRADE2)){
    donut.init(randInt(0, 3));
  }
  else if (status_ref->getUpgQty(UPGRADE1)){
    donut.init(randInt(0, 2));
  }
  else{
    donut.init(randInt(0, 1));
  }

  donuts.push_back(donut);
}

void SpManager::setMouseRef(Vec2f* pos){
  mouse = pos;
}

bool SpManager::checkMouse(Vec2f pos){
  if (pos.x > half_size - 100 && pos.x < half_size + 100){
    if (pos.y > half_size - 100 && pos.y < half_size + 100){
      return true;
    }
  }
  return false;
}

void SpManager::draw(){
  for (auto& donut : donuts){
    donut.draw();
  }
}

void SpManager::update(){

  std::list<Donuts>::iterator it = donuts.begin();

  if (donuts.size() > 25){
    donuts.erase(++donuts.begin());
  }

  while (it != donuts.end()){

    if (checkMouse(*mouse)){
      it->setScale(1);
    }
    else{
      it->setScale(0);
    }
    it->update();

    if (it->isOutBound()){
      it = donuts.erase(it);
      continue;
    }
    it++;
  }
}