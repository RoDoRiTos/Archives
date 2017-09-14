#include "data_manager.hpp"
#include "cinder/Json.h"

using namespace ci;
using namespace ci::app;

void DataManager::setRef(Status* ref){
  status_ref = ref;
}

void DataManager::save(){
  GameData save = status_ref->createSaveData();
  JsonTree data;
  data.addChild(JsonTree("Donuts Now", save.donuts_now));
  data.addChild(JsonTree("Donuts Total", save.donuts_total));
  data.addChild(JsonTree("Clicks Total", save.clicks_total));
  JsonTree temp_ary = JsonTree::makeArray("Upgrades Quantities");
  for (int i = 0; i < 6; i++){
    temp_ary.pushBack(JsonTree("",save.upg_qty[i]));
  }
  data.addChild(temp_ary);
  data.write(getAppPath() / "../../assets/savedata/savedata.json", JsonTree::WriteOptions().createDocument(false));
}

GameData DataManager::load(){
  JsonTree data(loadAsset("savedata/savedata.json"));
  GameData temp;
  temp.donuts_now = data["Donuts Now"].getValue<unsigned __int64>();
  temp.donuts_total = data["Donuts Total"].getValue<unsigned __int64>();
  temp.clicks_total = data["Clicks Total"].getValue<unsigned __int64>();
  for (int i = 0; i < 6; i++){
    temp.upg_qty[i] = data["Upgrades Quantities"][i].getValue<unsigned short>();
  }
  return temp;
}