#pragma once

#include "../System/commons.hpp"

class SelectedFood{
private:
  Box food_box;
  Position init_position;
  FoodType food_type;
  FoodVariation food_variation;

  bool active;
  int counter;

public:
  SelectedFood(Position pos, FoodType type, FoodVariation variation);

  bool IsActive();

  void Update();
  void Draw();

  void DrawVegetable(FoodVariation variation);
  void DrawMetal(FoodVariation variation);
  void DrawInsect(FoodVariation variation);
};