#pragma once
#include "player.hpp"
#include "../D-NSpace/my_nspace.hpp"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "upgrade.hpp"
#include <vector>

class Shop{
private:
  bool active;

  doritos::Plane plane;

  ci::gl::Texture transparent_blue;
  ci::gl::Texture transparent_black;
  ci::gl::Texture arrow;
  ci::gl::Texture upg;
  ci::gl::Texture upg_dark;

  std::vector<ci::gl::Texture> upg_tex;
  std::vector<ci::gl::Texture> upg_dark_tex;
  std::vector<ci::gl::Texture> donut_tex;

  ci::Vec3f donut_rotation;
  ci::Vec3f donut_scale;

  ci::Font font10;
  ci::Font font16;

  std::vector<Upg::Data> upgrades;
  unsigned short upg_qty[6];

  ci::Vec2f* mouse;

  unsigned __int64 getPrice(Upg::Data data);
  bool checkMouse(float target_sx,float target_ex,
    float target_sy,float target_ey);
  void drawUpg();

public:
  Shop();

  void init();
  void setUpgrades(Upg::Data data);
  void updateUpgrades(unsigned short qty, int i);
  void setActive(bool state);
  bool isActive();
  void setMouseRef(ci::Vec2f* mouse);
  unsigned __int64 getPrice(Upgrade_ID id);
  Upgrade_ID getUpgradeOnMouse();

  void update();
  void draw();
};