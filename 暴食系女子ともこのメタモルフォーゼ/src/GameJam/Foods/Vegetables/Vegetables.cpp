#include "Vegetables.hpp"

Vegetables::Vegetables(){
  type = FoodType::Vegetable;
  variation = (FoodVariation)Rand::Get()(0, 2);
}

Vegetables::~Vegetables(){

}

void Vegetables::Update(){

}

void Vegetables::Draw(){
  switch (variation){
  case FoodVariation::Var1:
    drawTextureBox(box.pos.x(), box.pos.y(), box.size.x(), box.size.y(),
      0, 0, 256, 256, ResTex.Get(TextureKey::Vegetables));
    break;
  case FoodVariation::Var2:
    drawTextureBox(box.pos.x(), box.pos.y(), box.size.x(), box.size.y(),
      256, 0, 256, 256, ResTex.Get(TextureKey::Vegetables));
    break;
  case FoodVariation::Var3:
    drawTextureBox(box.pos.x(), box.pos.y(), box.size.x(), box.size.y(),
      256, 256, 256, 256, ResTex.Get(TextureKey::Vegetables));
    break;
  }
}

Box Vegetables::GetBox(){
  return box;
}

void Vegetables::SetBox(Box box)
{
  this->box = box;
}

FoodType Vegetables::GetFoodType(){
  return type;
}

FoodVariation Vegetables::GetFoodVariation(){
  return variation;
}