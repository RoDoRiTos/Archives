#include "cinder\app\AppNative.h"
#include "cinder\gl\gl.h"
#include "cinder\gl\Light.h"
#include "cinder\Camera.h"
#include "cinder\TriMesh.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/SamplePlayerNode.h"
#include "cinder/audio/NodeEffects.h"
#include "D-NSpace\my_nspace.hpp"
#include "Spawner\spawner.hpp"
#include "Stats\status.hpp"
#include "Title\title.hpp"
#include "SaveData\data_manager.hpp"
#include <memory>

using namespace ci;
using namespace ci::app;

class PresentationProjectApp : public AppNative {
private:
  struct Audio{
    audio::BufferPlayerNodeRef bgm;
    audio::GainNodeRef gain;
  };

  std::unique_ptr<gl::Light> light;

  doritos::Plane plane;

  CameraPersp camera;

  Spawner spawner;

  Status status;

  DataManager data_mgr;

  Title title;

  std::vector<Audio> sound_effects;

  gl::Texture bg;

  float rx, ry, rz;

  Vec2f mouse;

public:
  void prepareSettings(Settings* settings);
  void setupAudio(std::string path, float gain_value);

  void setup();
  void shutdown();
  void mouseDown(MouseEvent event);
  void mouseMove(MouseEvent event);
  void mouseDrag(MouseEvent event);
  void setMouseRef();

  void drawBackground();

  void update();
  void draw();
};

typedef PresentationProjectApp MyApp;

void MyApp::prepareSettings(Settings* settings){
  settings->setWindowSize(doritos::Window::WIDTH, doritos::Window::HEIGHT);
  settings->setFrameRate(60.0f);
}

void MyApp::setupAudio(std::string path, float gain_value){
  Audio temp;

  auto ctx = audio::Context::master();

  audio::SourceFileRef sourceFile = audio::load(loadAsset(path));
  audio::BufferRef buffer = sourceFile->loadBuffer();
  temp.bgm = ctx->makeNode(new audio::BufferPlayerNode(buffer));
  temp.gain = ctx->makeNode(new audio::GainNode(gain_value));

  temp.bgm >> temp.gain >> ctx->getOutput();

  ctx->enable();

  sound_effects.push_back(temp);
}

void PresentationProjectApp::setup()
{
  bg = loadImage(loadAsset("images/stripes.png"));

  plane.init();

  // Light Initialization
  light = std::unique_ptr<gl::Light>(new gl::Light(gl::Light::DIRECTIONAL, 0));
  light->setAmbient(Color(0, 0, 0));
  light->setDiffuse(Color(1.0, 1.0, 1.0));
  light->setDirection(Vec3f(0.0, 0.0, 1.0));

  // Camera Initialization
  camera = CameraPersp(getWindowWidth(), getWindowHeight(),
    35.0, 300.0, 1000.0);

  camera.lookAt(Vec3f(0.0, 0.0, 700.0),
    Vec3f(0.0, 0.0, 0.0));

  //Enable Textures
  gl::enable(GL_TEXTURE_2D);

  //Use Material Color on Lighting
  gl::enable(GL_COLOR_MATERIAL);

  // Culling ON
  gl::enable(GL_CULL_FACE);

  // Lighting ON
  gl::enable(GL_LIGHTING);

  gl::enable(GL_NORMALIZE);

  gl::enableAlphaBlending(true);

  gl::enableDepthRead();
  gl::enableDepthWrite();

  setupAudio("sound/bgm.mp3", 0.5f);
  setupAudio("sound/se_donut.mp3", 0.5f);
  setupAudio("sound/se_menus.mp3", 0.5f);
  setupAudio("sound/se_buy.mp3", 0.5f);

  spawner.init();
  status.init();
  title.init();
  data_mgr.setRef(&status);
  status.loadSaveData(data_mgr.load());
  setMouseRef();
  spawner.setStatusRef(&status);
}

void MyApp::shutdown(){
  data_mgr.save();
}

void PresentationProjectApp::mouseDown(MouseEvent event)
{
  if (title.isActive()){
    title.setActive(false);
  }
  else{
    if (spawner.checkMouse(mouse)){
      if (event.isLeftDown()){
        spawner.spawnDonut();
        status.addDonuts();
        sound_effects[1].bgm->start();
      }
    }
  }

  if (status.getUpgradeOnMouse()){
    if (event.isLeftDown()){
      if (status.buyUpgrade()){
        sound_effects[3].bgm->start();
      }
    }
  }

  if (status.checkMouse() == Menu::STATUS){
    if (event.isLeftDown()){
      status.setPlayerActive(true);
      sound_effects[2].bgm->start();
    }
  }
}

void MyApp::mouseMove(MouseEvent event){
  mouse = event.getPos();
  if (status.checkMouse() == SHOP){
    if (!status.isShopActive()){
      sound_effects[2].bgm->start();
    }
    status.setShopActive(true);
  }
}

void MyApp::mouseDrag(MouseEvent event){
  mouse = event.getPos();
  if (status.checkMouse() == SHOP){
    if (!status.isShopActive()){
      sound_effects[2].bgm->start();
    }
    status.setShopActive(true);
  }
}

void MyApp::setMouseRef(){
  spawner.setMouseRef(&mouse);
  status.setMouseRef(&mouse);
}

void MyApp::drawBackground(){
  gl::pushModelView();
  {
    gl::translate(Vec3f(0, 0, -200));
    gl::rotate(Vec3f(180, 0, 0));
    gl::scale(Vec3f(300, 300, 0));
    bg.bind();
    gl::draw(plane.getMesh());
    bg.unbind();
  }
  gl::popModelView();
}

void PresentationProjectApp::update()
{
  if (!sound_effects[0].bgm->isEnabled()){
    sound_effects[0].bgm->start();
  }

  title.update();
  if (!title.isActive()){
    spawner.update();
    status.update();
    console() << mouse.x << " " << mouse.y << std::endl;
  }
}

void PresentationProjectApp::draw()
{
  gl::clear(Color(0.8, 0.8, 0.8));
  gl::setMatrices(camera);
  light->enable();
  gl::color(1, 1, 1);
  drawBackground();
  spawner.draw();
  status.draw();
  title.draw();
}

CINDER_APP_NATIVE(PresentationProjectApp, RendererGl)
