#pragma once
#include "player.hpp"
#include "shop.hpp"
#include "upgrade.hpp"
#include <vector>

struct GameData{
  unsigned __int64 donuts_now;
  unsigned __int64 donuts_total;
  unsigned __int64 clicks_total;
  unsigned short upg_qty[6];
};

enum Menu{
  STATUS,
  SHOP
};

class Status{
private:
  Player player;
  Shop shop;

  std::vector<Upgrade> upgrades;

  ci::Vec2f* mouse;

  int second_cnt;

  void checkMouse_();

  unsigned __int64 getUpgrades();
  unsigned __int64 getAutoUpgs();
public:
  Status();

  void init();
  void addDonuts();
  void setMouseRef(ci::Vec2f* mouse);
  void setPlayerActive(bool state);
  Menu checkMouse();
  void setShopActive(bool state);
  bool isShopActive();
  GameData createSaveData();
  void loadSaveData(GameData data);
  unsigned short getUpgQty(Upgrade_ID id);
  bool getUpgradeOnMouse();
  bool buyUpgrade();

  void update();
  void draw();
};
typedef Status StManager;