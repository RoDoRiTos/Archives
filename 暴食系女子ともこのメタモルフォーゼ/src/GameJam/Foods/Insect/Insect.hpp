#pragma once
#include "../FoodObject.hpp"
#include "../../System/commons.hpp"

class Insect :public FoodObject{
private:

public:
	Insect();
	~Insect();

	virtual void Update();
	virtual void Draw();
  virtual Box GetBox();
  virtual void SetBox(Box box);
  virtual FoodType GetFoodType() override;
  virtual FoodVariation GetFoodVariation() override;
};