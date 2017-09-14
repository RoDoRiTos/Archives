#include "../D-NSpace/my_nspace.hpp"
#include "cinder/gl/gl.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Font.h"

enum Title_Status{
  ONTITLE,
  MOVING,
  INACTIVE,
};

struct Transform{
  ci::Vec3f pos;
  ci::Vec3f rotate;
  ci::Vec3f scale;

  Transform(){
    pos = ci::Vec3f::zero();
    rotate = ci::Vec3f::zero();
    scale = ci::Vec3f::one();
  }
};

class Title{
private:
  doritos::Plane plane;

  Transform title;

  Transform back;

  bool active;

  float sin_wave;
  float sin_w;

  Title_Status state;

  ci::gl::Texture texture;

  ci::Font font50;
  ci::Font font30;

public:
  Title();
  void init();
  bool isActive();
  void setActive(bool state);

  void update();
  void draw();
};