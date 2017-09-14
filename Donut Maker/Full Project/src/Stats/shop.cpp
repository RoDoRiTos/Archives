#include "shop.hpp"
#include "cinder/ImageIo.h"
#include <sstream>
#include <string>
#include "cinder/CinderMath.h"

using namespace ci;
using namespace ci::app;

Shop::Shop(){
  active = false;
  for (int i = 0; i < 6; i++){
    upg_qty[i] = 0;
  }

  donut_rotation = Vec3f::zero();

  donut_scale = Vec3f(7.5, 7.5, 7.5);

  mouse = nullptr;
}

void Shop::init(){
  plane.init();
  transparent_blue = loadImage(loadAsset("images/trans_blue.png"));
  transparent_black = loadImage(loadAsset("images/trans_black.png"));
  arrow = loadImage(loadAsset("images/arrow.png"));
  font10 = Font(loadAsset("font/font.ttf"),10);
  font16 = Font(loadAsset("font/font.ttf"), 16);
  for (int i = 0; i < 6; i++){
    std::stringstream upg;
    std::stringstream dark;
    std::stringstream donut;

    upg << "images/upgrades/upgrade" << i << ".png";
    dark << "images/upgrades/upgrade" << i << "_dark.png";
    donut << "images/donut_" << i << ".png";

    gl::Texture temp = loadImage(loadAsset(upg.str()));
    upg_tex.push_back(temp);

    gl::Texture temp_dark = loadImage(loadAsset(dark.str()));
    upg_dark_tex.push_back(temp_dark);

    gl::Texture::Format format;
    format.setWrapS(GL_REPEAT);
    format.setWrapT(GL_REPEAT);

    gl::Texture temp_donut = gl::Texture(loadImage(loadAsset(donut.str())),format);
    donut_tex.push_back(temp_donut);
  }
}

void Shop::setUpgrades(Upg::Data data){
  upgrades.push_back(data);
}

void Shop::updateUpgrades(unsigned short qty, int i){
  upg_qty[i] = qty;
}

void Shop::setActive(bool state){
  active = state;
}

bool Shop::isActive(){
  return active;
}

void Shop::setMouseRef(ci::Vec2f* mouse){
  this->mouse = mouse;
}

bool Shop::checkMouse(float target_sx, float target_ex,
  float target_sy, float target_ey){
  if (mouse->x >= target_sx && mouse->x <= target_ex){
    if (mouse->y >= target_sy && mouse->y <= target_ey){
      return true;
    }
  }
  return false;
}

unsigned __int64 Shop::getPrice(Upg::Data data){
  return data.price * ci::math<double>::pow(data.price_ratio, upg_qty[data.id]);
}

unsigned __int64 Shop::getPrice(Upgrade_ID id){
  return getPrice(upgrades[id]);
}

Upgrade_ID Shop::getUpgradeOnMouse(){
  if (checkMouse(330, 616, 24, 106)){
    return UPGRADE0;
  }
  else if (checkMouse(330, 616, 126, 208)){
    return UPGRADE1;
  }
  else if (checkMouse(330, 616, 228, 310)){
    return UPGRADE2;
  }
  else if (checkMouse(330, 616, 330, 412)){
    return UPGRADE3;
  }
  else if (checkMouse(330, 616, 432, 514)){
    return UPGRADE4;
  }
  else if (checkMouse(330, 616, 534, 616)){
    return UPGRADE5;
  }
  else return null;
}

void Shop::drawUpg(){
  std::stringstream price0;

  price0 << "Price: " << doritos::Func::filterValue(getPrice(upgrades[0]));
  gl::pushModelView();
  {
    gl::translate(Vec3f(0, -125, 0)); 
    gl::pushModelView();
    {
      gl::drawStringCentered(price0.str(), Vec2f(22, 8), ColorA(0, 0, 0, 1), font10);
      gl::drawStringCentered("Quantity", Vec2f(-40, -15), ColorA(0, 0, 0, 1), font10);
      gl::pushModelView();
      {
        gl::translate(Vec3f(0, 0, -1));
        gl::drawStringCentered(std::to_string(upg_qty[0]),Vec2f(-40,0),ColorA(0,0,0,1),font16);
      }
      gl::popModelView();
    }
    gl::popModelView();

    gl::pushModelView();
    {
      gl::translate(Vec3f(-100, 0, 0));
      gl::rotate(donut_rotation);
      gl::scale(donut_scale);
      donut_tex[0].bind();
      gl::drawTorus(1, 0.5, 32, 32);
      donut_tex[0].unbind();
    }
    gl::popModelView();

    gl::pushModelView();
    {
      gl::scale(Vec3f(70, 20, 0));
      if (checkMouse(330, 616, 24, 106)){
        upg_dark_tex[0].bind();
      }
      else{
        upg_tex[0].bind();
      }
      gl::draw(plane.getMesh());
      upg_dark_tex[0].unbind();
      upg_tex[0].unbind();
    }
    gl::popModelView();

  }
  gl::popModelView();

  std::stringstream price1;

  price1 << "Price: " << doritos::Func::filterValue(getPrice(upgrades[1]));

  gl::pushModelView();
  {
    gl::translate(Vec3f(0, -75, 0));
    gl::pushModelView();
    {
      gl::drawStringCentered(price1.str(), Vec2f(22, 8), ColorA(0, 0, 0, 1), font10);
      gl::drawStringCentered("Quantity", Vec2f(-40, -15), ColorA(0, 0, 0, 1), font10);
      gl::pushModelView();
      {
        gl::translate(Vec3f(0, 0, -1));
        gl::drawStringCentered(std::to_string(upg_qty[1]), Vec2f(-40, 0), ColorA(0, 0, 0, 1), font16);
      }
      gl::popModelView();
    }
    gl::popModelView();

    gl::pushModelView();
    {
      gl::translate(Vec3f(-100, 0, 0));
      gl::rotate(donut_rotation);
      gl::scale(donut_scale);
      donut_tex[1].bind();
      gl::drawTorus(1, 0.5, 32, 32);
      donut_tex[1].unbind();
    }
    gl::popModelView();

    gl::pushModelView();
    {
      gl::scale(Vec3f(70, 20, 0));
      if (checkMouse(330, 616, 126, 208)){
        upg_dark_tex[1].bind();
      }
      else{
        upg_tex[1].bind();
      }
      gl::draw(plane.getMesh());
      upg_dark_tex[1].unbind();
      upg_tex[1].unbind();
    }
    gl::popModelView();
  }
  gl::popModelView();

  std::stringstream price2;

  price2 << "Price: " << doritos::Func::filterValue(getPrice(upgrades[2]));

  gl::pushModelView();
  {
    gl::translate(Vec3f(0, -25, 0));
    gl::pushModelView();
    {
      gl::drawStringCentered(price2.str(), Vec2f(22, 8), ColorA(0, 0, 0, 1), font10);
      gl::drawStringCentered("Quantity", Vec2f(-40, -15), ColorA(0, 0, 0, 1), font10);
      gl::pushModelView();
      {
        gl::translate(Vec3f(0, 0, -1));
        gl::drawStringCentered(std::to_string(upg_qty[2]), Vec2f(-40, 0), ColorA(0, 0, 0, 1), font16);
      }
      gl::popModelView();
    }
    gl::popModelView();

    gl::pushModelView();
    {
      gl::translate(Vec3f(-100, 0, 0));
      gl::rotate(donut_rotation);
      gl::scale(donut_scale);
      donut_tex[2].bind();
      gl::drawTorus(1, 0.5, 32, 32);
      donut_tex[2].unbind();
    }
    gl::popModelView();

    gl::pushModelView(); 
    {
    gl::scale(Vec3f(70, 20, 0));
    if (checkMouse(330, 616, 228, 310)){
      upg_dark_tex[2].bind();
    }
    else{
      upg_tex[2].bind();
    }
    gl::draw(plane.getMesh());
    upg_dark_tex[2].unbind();
    upg_tex[2].unbind();
    }
    gl::popModelView();

  }
  gl::popModelView();

  std::stringstream price3;

  price3 << "Price: " << doritos::Func::filterValue(getPrice(upgrades[3]));

  gl::pushModelView();
  {
    gl::translate(Vec3f(0, 25, 0));
    gl::pushModelView();
    {
      gl::drawStringCentered(price3.str(), Vec2f(22, 8), ColorA(0, 0, 0, 1), font10);
      gl::drawStringCentered("Quantity", Vec2f(-40, -15), ColorA(0, 0, 0, 1), font10);
      gl::pushModelView();
      {
        gl::translate(Vec3f(0, 0, -1));
        gl::drawStringCentered(std::to_string(upg_qty[3]), Vec2f(-40, 0), ColorA(0, 0, 0, 1), font16);
      }
      gl::popModelView();
    }
    gl::popModelView();

    gl::pushModelView();
    {
      gl::translate(Vec3f(-100, 0, 0));
      gl::rotate(donut_rotation);
      gl::scale(donut_scale);
      donut_tex[3].bind();
      gl::drawTorus(1, 0.5, 32, 32);
      donut_tex[3].unbind();
    }
    gl::popModelView();

    gl::pushModelView();
    {
    gl::scale(Vec3f(70, 20, 0));
    if (checkMouse(330, 616, 330, 412)){
      upg_dark_tex[3].bind();
    }
    else{
      upg_tex[3].bind();
    }
    gl::draw(plane.getMesh());
    upg_dark_tex[3].unbind();
    upg_tex[3].unbind();
    }
    gl::popModelView();
  }
  gl::popModelView();

  std::stringstream price4;

  price4 << "Price: " << doritos::Func::filterValue(getPrice(upgrades[4]));

  gl::pushModelView();
  {
    gl::translate(Vec3f(0, 75, 0));
    gl::pushModelView();
    {
      gl::drawStringCentered(price4.str(), Vec2f(22, 8), ColorA(0, 0, 0, 1), font10);
      gl::drawStringCentered("Quantity", Vec2f(-40, -15), ColorA(0, 0, 0, 1), font10);
      gl::pushModelView();
      {
        gl::translate(Vec3f(0, 0, -1));
        gl::drawStringCentered(std::to_string(upg_qty[4]), Vec2f(-40, 0), ColorA(0, 0, 0, 1), font16);
      }
      gl::popModelView();
    }
    gl::popModelView();

    gl::pushModelView();
    {
      gl::translate(Vec3f(-100, 0, 0));
      gl::rotate(donut_rotation);
      gl::scale(donut_scale);
      donut_tex[4].bind();
      gl::drawTorus(1, 0.5, 32, 32);
      donut_tex[4].unbind();
    }
    gl::popModelView();

    gl::pushModelView();
    {
    gl::scale(Vec3f(70, 20, 0));
    if (checkMouse(330, 616, 432, 514)){
      upg_dark_tex[4].bind();
    }
    else{
      upg_tex[4].bind();
    }
    gl::draw(plane.getMesh());
    upg_dark_tex[4].unbind();
    upg_tex[4].unbind();
    }
    gl::popModelView();
  }
  gl::popModelView();

  std::stringstream price5;

  price5 << "Price: " << doritos::Func::filterValue(getPrice(upgrades[5]));

  gl::pushModelView();
  {
    gl::translate(Vec3f(0, 125, 0));
    gl::pushModelView();
    {
      gl::drawStringCentered(price5.str(), Vec2f(22, 8), ColorA(0, 0, 0, 1), font10);
      gl::drawStringCentered("Quantity", Vec2f(-40, -15), ColorA(0, 0, 0, 1), font10);
      gl::pushModelView();
      {
        gl::translate(Vec3f(0, 0, -1));
        gl::drawStringCentered(std::to_string(upg_qty[5]), Vec2f(-40, 0), ColorA(0, 0, 0, 1), font16);
      }
      gl::popModelView();
    }
    gl::popModelView();

    gl::pushModelView();
    {
      gl::translate(Vec3f(-100, 0, 0));
      gl::rotate(donut_rotation);
      gl::scale(donut_scale);
      donut_tex[5].bind();
      gl::drawTorus(1, 0.5, 32, 32);
      donut_tex[5].unbind();
    }
    gl::popModelView();

    gl::pushModelView();
    {
    gl::scale(Vec3f(70, 20, 0));
    if (checkMouse(330, 616, 534, 616)){
      upg_dark_tex[5].bind();
    }
    else{
      upg_tex[5].bind();
    }
    gl::draw(plane.getMesh());
    upg_dark_tex[5].unbind();
    upg_tex[5].unbind();
    }
    gl::popModelView();
  }
  gl::popModelView();
}

void Shop::update(){
  donut_rotation.y++;
}

void Shop::draw(){
  if (!active){
    gl::pushModelView();
    {
      gl::translate(Vec3f(150, 0, 200));
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
      gl::translate(Vec3f(75, 0, 200));
      gl::rotate(Vec3f(180, 0, 0));

      gl::pushModelView();
      {
        gl::scale(Vec3f(80, 155, 0));
        transparent_blue.bind();
        gl::draw(plane.getMesh());
        transparent_blue.unbind();
      }
      gl::popModelView();

      gl::pushModelView();
      {
        gl::translate(Vec3f(0, 0, -1));
        drawUpg();
      }
      gl::popModelView();
    }
    gl::popModelView();
  }
}