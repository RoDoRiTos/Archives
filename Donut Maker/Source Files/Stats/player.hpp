#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "../D-NSpace/my_nspace.hpp"

class Player{
private:

  bool active;
  unsigned __int64 clicks;
  unsigned __int64 clicks_total;

  unsigned __int64 donuts;
  unsigned __int64 donuts_total;

  unsigned __int64 per_sec;
  unsigned __int64 per_click;

  doritos::Plane plane;

  ci::gl::Texture transparent_red;
  ci::gl::Texture arrow;

  ci::Font font40;
  ci::Font font30;
  ci::Font font16;

public:
  Player();
  void init();

  void setActive(bool state);
  bool isActive();

  void addClick();
  unsigned __int64 getClicksTotal();
  void setClicksTotal(unsigned __int64 value);
  void addClicksTotal();

  unsigned __int64 getDonuts();
  void setDonuts(unsigned __int64 value);
  void addDonuts(unsigned __int64 value);
  void subDonuts(unsigned __int64 value);

  unsigned __int64 getDonutsTotal();
  void setDonutsTotal(unsigned __int64 value);
  void addDonutsTotal(unsigned __int64 value);

  void setPerSecDonuts(unsigned __int64 value);
  void setPerClickDonuts(unsigned __int64 value);

  void update();
  void draw();
};