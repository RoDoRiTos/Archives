#pragma once
#include "../FoodObject.hpp"
#include "../../System/commons.hpp"

class Metal :public FoodObject{
private:

public:
	Metal();
	~Metal();

	virtual void Update();
	virtual void Draw();
  virtual Box GetBox();
  virtual void SetBox(Box box);
  virtual FoodType GetFoodType() override;
  virtual FoodVariation GetFoodVariation() override;
};