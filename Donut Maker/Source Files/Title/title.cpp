#include "title.hpp"
#include "cinder/ImageIo.h"
#include "cinder/CinderMath.h"

using namespace ci;
using namespace ci::app;

Title::Title(){
  active = true;
  state = ONTITLE;
  title.pos = Vec3f(0,0,250);
  back.pos = Vec3f(0,0,0);
  back.rotate = Vec3f(180, 0, 0);
  back.scale = Vec3f(150,150,0);
  sin_wave = 0.0f;
  sin_w = 0.0f;
}

void Title::init(){
  plane.init();
  texture = loadImage(loadAsset("images/stripes_reversed.png"));
  font50 = Font(loadAsset("font/font.ttf"), 60);
  font30 = Font(loadAsset("font/font.ttf"), 30);
}

bool Title::isActive(){
  return active;
}

void Title::setActive(bool state){
  active = state;
}

void Title::update(){
  sin_w+=0.1;
  sin_wave = ci::math<float>::sin(sin_w);
  if (!active){
    state = MOVING;
  }

  if (state == MOVING){
    title.pos.y += 5.0f;
  }

  if (title.pos.y >= 300.0f){
    state = INACTIVE;
  }
}

void Title::draw(){
  if (state != INACTIVE){
    gl::pushModelView();
    {
      gl::translate(title.pos);
      gl::rotate(title.rotate);
      gl::scale(title.scale);

      gl::pushModelView();
      {
        gl::translate(back.pos);
        gl::rotate(back.rotate);
        gl::scale(back.scale);
        texture.bind();
        gl::draw(plane.getMesh());
        texture.unbind();
      }
      gl::popModelView();

      gl::pushModelView();
      {
        gl::translate(Vec3f(0.0f, 120.0f, 1.0f));
        gl::rotate(Vec3f(180.0f, 0.0f, 0.0f));
        gl::drawStringCentered("Donut", Vec2f(0.0f, 0.0f), ColorA(0, 0, 0, 1), font50);
        gl::drawStringCentered("Maker", Vec2f(0.0f, 50.0f), ColorA(0, 0, 0, 1), font50);
      }
      gl::popModelView();

      gl::pushModelView();
      {
        gl::translate(Vec3f(0.0f, -50.0f + sin_wave * 10, 1.0f));
        gl::rotate(Vec3f(180.0f, 0.0f, 0.0f));
        gl::drawStringCentered("Click to Play", Vec2f(0.0f, 0.0f), ColorA(0, 0, 0, 1), font30);
      }
      gl::popModelView();

    }
    gl::popModelView();
  }
}