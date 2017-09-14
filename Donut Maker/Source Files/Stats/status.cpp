#include "status.hpp"
#include "cinder/CinderMath.h"

StManager::Status(){
  mouse = nullptr;
  for (int i = 0; i < 6; i++){
    Upgrade temp = Upgrade(i);
    upgrades.push_back(temp);
  }
  second_cnt = 0;

  for (int i = 0; i < 6; i++){
    shop.setUpgrades(upgrades[i].getData());
  }
}

void StManager::checkMouse_(){
  if (shop.isActive()){
    if (mouse->x < 310){
      shop.setActive(false);
    }
  }


  if (player.isActive()){
    if (mouse->x > 330){
      player.setActive(false);
    }
  }
}

unsigned __int64 StManager::getUpgrades(){
  unsigned __int64 base = 1;
  for (auto& upg : upgrades){
    base += (upg.getEffect().click_effect * upg.getQuantity());
    static_cast<unsigned __int64>(base *= ci::math<double>::pow(upg.getEffect().ratio_effect, upg.getQuantity()));
  }
  return base;
}

unsigned __int64 StManager::getAutoUpgs(){
  unsigned __int64 base = 0;
  for (auto& upg : upgrades){
    base += (upg.getEffect().automatic_effect*upg.getQuantity());
    static_cast<unsigned __int64>(base *= ci::math<double>::pow(upg.getEffect().ratio_effect, upg.getQuantity()));
  }
  return base;
}

void StManager::init(){
  shop.init();
  player.init();
}

void StManager::addDonuts(){
  player.addClick();
  player.addDonuts(getUpgrades());
}

void StManager::setMouseRef(ci::Vec2f* mouse){
  this->mouse = mouse;
  shop.setMouseRef(mouse);
}

void StManager::setPlayerActive(bool state){
  player.setActive(state);
}

Menu StManager::checkMouse(){
  if (mouse->x <= 40){
    if (mouse->y >= 280 && mouse->y <= 360){
      return STATUS;
    }
  }

  if (mouse->x >= 600){
    if (mouse->y >= 280 && mouse->y <= 360){
      return SHOP;
    }
  }
}

void StManager::setShopActive(bool state){
  shop.setActive(state);
}

bool StManager::isShopActive(){
  return shop.isActive();
}

GameData StManager::createSaveData(){
  GameData save;
  save.donuts_now = player.getDonuts();
  save.donuts_total = player.getDonutsTotal();
  save.clicks_total = player.getClicksTotal();
  for (int i = 0; i < 6; i++){
    save.upg_qty[i] = upgrades[i].getQuantity();
  }
  return save;
}

void StManager::loadSaveData(GameData data){
  player.setDonuts(data.donuts_now);
  player.setDonutsTotal(data.donuts_total);
  player.setClicksTotal(data.clicks_total);
  for (int i = 0; i < 6; i++){
    upgrades[i].setQty(data.upg_qty[i]);
  }
}

unsigned short StManager::getUpgQty(Upgrade_ID id){
  return upgrades[id].getQuantity();
}

bool StManager::getUpgradeOnMouse(){
  if (shop.getUpgradeOnMouse() != Upgrade_ID::null){
    return true;
  }
  return false;
}

bool StManager::buyUpgrade(){
  switch (shop.getUpgradeOnMouse()){
  case UPGRADE0:
    if (player.getDonuts() >= shop.getPrice(UPGRADE0)){
      player.subDonuts(shop.getPrice(UPGRADE0));
      upgrades[0].addQty();
      return true;
    }
    return false;
  case UPGRADE1:
    if (player.getDonuts() >= shop.getPrice(UPGRADE1)){
      player.subDonuts(shop.getPrice(UPGRADE1));
      upgrades[1].addQty();
      return true;
    }
    return false;
  case UPGRADE2:
    if (player.getDonuts() >= shop.getPrice(UPGRADE2)){
      player.subDonuts(shop.getPrice(UPGRADE2));
      upgrades[2].addQty();
      return true;
    }
    return false;
  case UPGRADE3:
    if (player.getDonuts() >= shop.getPrice(UPGRADE3)){
      player.subDonuts(shop.getPrice(UPGRADE3));
      upgrades[3].addQty();
      return true;
    }
    return false;
  case UPGRADE4:
    if (player.getDonuts() >= shop.getPrice(UPGRADE4)){
      player.subDonuts(shop.getPrice(UPGRADE4));
      upgrades[4].addQty();
      return true;
    }
    return false;
  case UPGRADE5:
    if (player.getDonuts() >= shop.getPrice(UPGRADE5)){
      player.subDonuts(shop.getPrice(UPGRADE5));
      upgrades[5].addQty();
      return true;
    }
    return false;
  }
}

void StManager::update(){
  checkMouse_();
  if (second_cnt >= 60){
    second_cnt -= 60;
    player.addDonuts(getAutoUpgs());
  }
  player.setPerClickDonuts(getUpgrades());
  player.setPerSecDonuts(getAutoUpgs());
  player.update();
  for (int i = 0; i < 6; i++){
    shop.updateUpgrades(upgrades[i].getQuantity(), i);
  }
  shop.update();
  second_cnt++;
}

void StManager::draw(){
  player.draw();
  shop.draw();
}