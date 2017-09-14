#include "selectedFood.hpp"

SelectedFood::SelectedFood(Position pos, FoodType type, FoodVariation variation){
  switch (pos){
  case Position::Left:
    food_box = { Vec2f(-325, -400), Vec2f(150, 150) };
    break;
  case Position::Middle:
    food_box = { Vec2f(-75, -400), Vec2f(150, 150) };
    break;
  case Position::Right:
    food_box = { Vec2f(175, -400), Vec2f(150, 150) };
    break;
  }

  init_position = pos;
  food_type = type;
  food_variation = variation;
  active = true;

  counter = 0;
}

bool SelectedFood::IsActive(){
  return active;
}

void SelectedFood::Update(){
  if (counter >= 60){
    active = false;
  }

  if (init_position == Position::Left){
    food_box.pos.x() += (250.0f / 60.0f);
    food_box.pos.y() += (450.0f / 60.0f);
  }

  if (init_position == Position::Middle){
    food_box.pos.y() += (450.0f / 60.0f);
  }
    
  if (init_position == Position::Right){
    food_box.pos.x() -= (250.0f / 60.0f);
    food_box.pos.y() += (450.0f / 60.0f);
  }

  counter++;
}

void SelectedFood::Draw(){
  switch (food_type){
  case FoodType::Vegetable:
    DrawVegetable(food_variation);
    break;
  case FoodType::Metal:
    DrawMetal(food_variation);
    break;
  case FoodType::Insect:
    DrawInsect(food_variation);
    break;
  }
}

void SelectedFood::DrawVegetable(FoodVariation variation){
  switch(food_variation){
  case FoodVariation::Var1:
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      0, 0, 256, 256, ResTex.Get(TextureKey::Vegetables));
    break;
  case FoodVariation::Var2:
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      256, 0, 256, 256, ResTex.Get(TextureKey::Vegetables));
    break;
  case FoodVariation::Var3:
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      256, 256, 256, 256, ResTex.Get(TextureKey::Vegetables));
    break;
  default: 
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      0, 0, 256, 256, ResTex.Get(TextureKey::Vegetables));
    break;
  }
}

void SelectedFood::DrawMetal(FoodVariation variation){
  switch (food_variation){
  case FoodVariation::Var1:
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      0, 0, 256, 256, ResTex.Get(TextureKey::Metal));
    break;
  case FoodVariation::Var2:
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      256, 0, 256, 256, ResTex.Get(TextureKey::Metal));
    break;
  case FoodVariation::Var3:
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      256, 256, 256, 256, ResTex.Get(TextureKey::Metal));
    break;
  default:
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      0, 0, 256, 256, ResTex.Get(TextureKey::Metal));
    break;
  }
}

void SelectedFood::DrawInsect(FoodVariation variation){
  switch (food_variation){
  case FoodVariation::Var1:
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      0, 0, 256, 256, ResTex.Get(TextureKey::Insect));
    break;
  case FoodVariation::Var2:
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      256, 0, 256, 256, ResTex.Get(TextureKey::Insect));
    break;
  case FoodVariation::Var3:
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      256, 256, 256, 256, ResTex.Get(TextureKey::Insect));
    break;
  default:
    drawTextureBox(food_box.pos.x(), food_box.pos.y(), food_box.size.x(), food_box.size.y(),
      0, 0, 256, 256, ResTex.Get(TextureKey::Insect));
    break;
  }
}