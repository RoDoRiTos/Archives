#include "../FoodObject.hpp"
#include "../../System/commons.hpp"


class Vegetables :public FoodObject{
private:


public:
	Vegetables();
	~Vegetables();

	virtual void Update();
	virtual void Draw();
  virtual Box GetBox();
  virtual void SetBox(Box box);
  virtual FoodType GetFoodType() override;
  virtual FoodVariation GetFoodVariation() override;
};