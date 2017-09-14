#include "upgrade.hpp"

Upgrade::Upgrade(){
  effect = { 0, 0, 1.0f };
  data = { null, 0, 1.0f };
  quantity = 0;
}

Upgrade::Upgrade(int id){
  switch (id){
  case UPGRADE0:
    effect = { 1, 1, 1.01f };
    data = { UPGRADE0, 10, 1.15f };
    quantity = 0;
    break;
  case UPGRADE1:
    effect = { 10, 15, 1.02f };
    data = { UPGRADE1, 200, 1.2f };
    quantity = 0;
    break;
  case UPGRADE2:
    effect = { 50, 123, 1.04f };
    data = { UPGRADE2, 2500, 1.25f };
    quantity = 0;
    break;
  case UPGRADE3:
    effect = { 500, 2500, 1.1f };
    data = { UPGRADE3, 30000, 1.3f };
    quantity = 0;
    break;
  case UPGRADE4:
    effect = { 5000, 30000, 1.15f };
    data = { UPGRADE4, 100000, 1.4f };
    quantity = 0;
    break;
  case UPGRADE5:
    effect = { 12800, 256000, 1.25f };
    data = { UPGRADE5, 5120000, 1.5f };
    quantity = 0;
    break;
  default:
    effect = { 0, 0, 1.0f };
    data = { null, 0, 1.0f };
    quantity = 0;
    break;
  }
  quantity = 0;
}

Upg::Effect Upgrade::getEffect(){
  return effect;
}

Upg::Data Upgrade::getData(){
  return data;
}

void Upgrade::setQty(unsigned short value){
  quantity = value;
}

void Upgrade::addQty(){
  quantity++;
}

unsigned short Upgrade::getQuantity(){
  return quantity;
}