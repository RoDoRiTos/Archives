#include "player.hpp"
#include <sstream>
#include <vector>
#include "cinder/ImageIo.h"
#include "cinder/CinderMath.h"
#include "../D-NSpace/my_nspace.hpp"

using namespace ci;
using namespace ci::app;

Player::Player(){
  clicks = 0;
  clicks_total = 0;
  donuts = 0;
  donuts_total = 0;
  per_sec = 0;
  per_click = 0;
  active = false;
}

void Player::init(){
  transparent_red = loadImage(loadAsset("images/trans_red.png"));
  arrow = loadImage(loadAsset("images/arrow2.png"));
  plane.init();
  font40 = Font(loadAsset("font/font.ttf"), 40);
  font30 = Font(loadAsset("font/font.ttf"), 30);
  font16 = Font(loadAsset("font/font.ttf"), 16);
}

void Player::setActive(bool state){
  active = state;
}

bool Player::isActive(){
  return active;
}

void Player::addClick(){
  clicks++;
  addClicksTotal();
}

unsigned __int64 Player::getClicksTotal(){
  return clicks_total;
}

void Player::setClicksTotal(unsigned __int64 value){
  clicks_total = value;
}

void Player::addClicksTotal(){
  clicks_total++;
}

unsigned __int64 Player::getDonuts(){
  return donuts;
}

void Player::setDonuts(unsigned __int64 value){
  donuts = value;
}

void Player::addDonuts(unsigned __int64 value){
  donuts += value;
  addDonutsTotal(value);
}

void Player::subDonuts(unsigned __int64 value){
  if (value > donuts) { return; }
  donuts -= value;
}

unsigned __int64 Player::getDonutsTotal(){
  return donuts_total;
}

void Player::setDonutsTotal(unsigned __int64 value){
  donuts_total = value;
}

void Player::addDonutsTotal(unsigned __int64 value){
  donuts_total += value;
}

void Player::setPerSecDonuts(unsigned __int64 value){
  per_sec = value;
}

void Player::setPerClickDonuts(unsigned __int64 value){
  per_click = value;
}

void Player::update(){
  
}

void Player::draw(){
  std::string donuts_str;
  std::string per_click_str;
  std::string per_sec_str;

  donuts_str = doritos::Func::filterValue(donuts) + " Donuts";
  per_click_str = doritos::Func::filterValue(per_click) + " Donuts per/Click";
  per_sec_str = doritos::Func::filterValue(per_sec) + " Donuts per/sec";


  gl::pushModelView();
  {
    gl::translate(Vec3f(0.0f, 150.0f, 0.0f));
    gl::rotate(Vec3f(180.0f, 0.0f, 0.0f));
    gl::drawStringCentered(donuts_str, Vec2f(0,-50), ColorA(0, 0, 0, 1), font40);
    gl::drawStringCentered(per_click_str, Vec2f::zero(), ColorA(0, 0, 0, 1), font40);
    gl::drawStringCentered(per_sec_str, Vec2f(0,300), ColorA(0, 0, 0, 1), font40);
  }
  gl::popModelView();

  if (!active){
    gl::pushModelView();
    {
      gl::translate(Vec3f(-150, 0, 200));
      gl::rotate(Vec3f(180, 0, 0));
      gl::scale(Vec3f(10, 20, 0));
      arrow.bind();
      gl::draw(plane.getMesh());
      arrow.unbind();
    }
    gl::popModelView();
  }
  else{
    gl::pushModelView();
    {
      gl::translate(Vec3f(-75, 0, 200));
      gl::rotate(Vec3f(180, 0, 0));

      gl::pushModelView();
      {
      gl::scale(Vec3f(80, 155, 0));
      transparent_red.bind();
      gl::draw(plane.getMesh());
      transparent_red.unbind();
      }
      gl::popModelView();

      gl::pushModelView();
      {
        gl::translate(Vec3f(0, 0, -1));

        gl::pushModelView();
        {
          gl::translate(Vec3f(0, -140, 0));
          gl::drawStringCentered("Game", Vec2f::zero(), ColorA(1, 1, 1, 1), font30);
          gl::drawStringCentered("Stats", Vec2f(0, 30), ColorA(1, 1, 1, 1), font30);
        }
        gl::popModelView();
        
        gl::pushModelView();
        {
          gl::translate(Vec3f(0, -60, 0));
          gl::drawStringCentered("Total Donuts:", Vec2f::zero(), ColorA(1, 1, 1, 1), font16);
          gl::drawStringCentered(doritos::Func::filterValue(donuts_total), Vec2f(0,30), ColorA(1, 1, 1, 1), font16);
          gl::drawStringCentered("Clicks (This Game):", Vec2f(0,60), ColorA(1, 1, 1, 1), font16);
          gl::drawStringCentered(doritos::Func::filterValue(clicks), Vec2f(0, 90), ColorA(1, 1, 1, 1), font16);
          gl::drawStringCentered("Clicks (Total):", Vec2f(0,120), ColorA(1, 1, 1, 1), font16);
          gl::drawStringCentered(doritos::Func::filterValue(clicks_total), Vec2f(0, 150), ColorA(1, 1, 1, 1), font16);
        }
        gl::popModelView();
        
      }
      gl::popModelView();

    }
    gl::popModelView();
  }

}