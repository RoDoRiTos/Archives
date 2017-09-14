#include "donut.hpp"
#include <sstream>
#include "cinder/rand.h"

using namespace ci;
using namespace ci::app;

Donuts::Donuts(){
  Rand::randomize();
}

void Donuts::init(){
  gl::Texture::Format format;
  format.setWrapS(GL_REPEAT);
  format.setWrapT(GL_REPEAT);
  texture = gl::Texture(loadImage(loadAsset("images/donut_0.png")), format);

  donut.pos = Vec3f::zero();

  donut.rotation = Vec3f::zero();

  scale = Vec3f(50.0f, 50.0f, 50.0f);

  isCenter = true;

  boundHit = false;
}

void Donuts::init(int type){
  std::stringstream path;

  gl::Texture::Format format;
  format.setWrapS(GL_REPEAT);
  format.setWrapT(GL_REPEAT);

  if (type > 5 && type < 0) type = 0;

  path << "images/donut_" << type << ".png";

  texture = gl::Texture(loadImage(loadAsset(path.str())), format);

  donut.pos = Vec3f(Rand::randFloat(-200.0f, 200.0f), 200, Rand::randInt(1, 100));

  donut.rotation = Vec3f::zero();

  scale = Vec3f(5.0f, 5.0f, 5.0f);

  isCenter = false;

  boundHit = false;
}

void Donuts::setScale(int type){
  if (isCenter){
    if (!type){
      scale = Vec3f(50.0f,50.0f,50.0f);
    }
    else{
      scale = Vec3f(55.0f, 55.0f, 55.0f);
    }
  }
}

bool Donuts::isOutBound(){
  return boundHit;
}

void Donuts::update(){
  if (isCenter){
    donut.rotation.y++;
  }
  else{
    donut.pos.y-=2;
    donut.rotation.x += 5;
    if (donut.pos.y <= -200){
      boundHit = true;
    }
  }
}

void Donuts::draw(){
    gl::pushModelView();
    {
      gl::translate(donut.pos);
      gl::rotate(donut.rotation);
      gl::scale(scale);
      gl::color(1, 1, 1);
      texture.bind();
      gl::drawTorus(1, 0.5,32,32);
      texture.unbind();
    }
    gl::popModelView();
}