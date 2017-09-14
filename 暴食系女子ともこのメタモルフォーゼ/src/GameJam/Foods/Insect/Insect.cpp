#include "Insect.hpp"

Insect::Insect(){
  type = FoodType::Insect;
  variation = (FoodVariation)Rand::Get()(0, 2);
}

Insect::~Insect(){

}

void Insect::Update(){

}

void Insect::Draw(){
  switch (variation){
  case FoodVariation::Var1:
    drawTextureBox(box.pos.x(), box.pos.y(), box.size.x(), box.size.y(),
      0, 0, 256, 256, ResTex.Get(TextureKey::Insect));
    break;
  case FoodVariation::Var2:
    drawTextureBox(box.pos.x(), box.pos.y(), box.size.x(), box.size.y(),
      256, 0, 256, 256, ResTex.Get(TextureKey::Insect));
    break;
  case FoodVariation::Var3:
    drawTextureBox(box.pos.x(), box.pos.y(), box.size.x(), box.size.y(),
      256, 256, 256, 256, ResTex.Get(TextureKey::Insect));
    break;
  }
}

Box Insect::GetBox(){
  return box;
}

void Insect::SetBox(Box box)
{
  this->box = box;
}

FoodType Insect::GetFoodType(){
  return type;
}

FoodVariation Insect::GetFoodVariation(){
  return variation;
}