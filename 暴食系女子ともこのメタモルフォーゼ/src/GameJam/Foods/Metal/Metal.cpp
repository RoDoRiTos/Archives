#include "Metal.hpp"

Metal::Metal(){
  type = FoodType::Metal;
  variation = (FoodVariation)Rand::Get()(0, 2);
}

Metal::~Metal(){
	
}

void Metal::Update(){

}

void Metal::Draw(){
  switch (variation){
  case FoodVariation::Var1:
    drawTextureBox(box.pos.x(), box.pos.y(), box.size.x(), box.size.y(),
      0, 0, 256, 256, ResTex.Get(TextureKey::Metal));
    break;
  case FoodVariation::Var2:
    drawTextureBox(box.pos.x(), box.pos.y(), box.size.x(), box.size.y(),
      256, 0, 256, 256, ResTex.Get(TextureKey::Metal));
    break;
  case FoodVariation::Var3:
    drawTextureBox(box.pos.x(), box.pos.y(), box.size.x(), box.size.y(),
      256, 256, 256, 256, ResTex.Get(TextureKey::Metal));
    break;
  }
}

Box Metal::GetBox(){
  return box;
}

void Metal::SetBox(Box box)
{
  this->box = box;
}

FoodType Metal::GetFoodType(){
  return type;
}

FoodVariation Metal::GetFoodVariation(){
  return variation;
}