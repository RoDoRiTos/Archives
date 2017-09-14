#pragma once
#include "../System/commons.hpp"

class FoodObject{
private:

protected:
  Box box;
  FoodType type;
  FoodVariation variation;

public:
	FoodObject();
	~FoodObject();

	void AddGauge(const int _add, int *_gauge);
	virtual void Update() = 0;
	virtual void Draw() = 0;
  virtual Box GetBox() = 0;
  virtual void SetBox(Box box) = 0;
  virtual FoodType GetFoodType() = 0;
  virtual FoodVariation GetFoodVariation() = 0;
};