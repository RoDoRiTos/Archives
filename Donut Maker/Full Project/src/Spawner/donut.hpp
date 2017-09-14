#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include <vector>
#include "../D-NSpace/my_nspace.hpp"


class Donuts{
private:
  ci::gl::Texture texture;
  doritos::Object donut;
  
  bool isCenter;

  ci::Vec3f scale;

  bool boundHit;

public:
  Donuts();
  //Donuts(int type);
  void init();
  void init(int type);

  void setScale(int type);

  bool isOutBound();

  void draw();
  void update();
};