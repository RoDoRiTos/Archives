#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "../../lib/framework.hpp"
#include "envSingleton.hpp"
#include "../Utility/Collision/collision.hpp"
#include "../Utility/randomSingleton.hpp"
#include "Resource Manager/resourceManager.hpp"

enum class Position{
  Left,
  Middle,
  Right
};

enum class FoodType{
  Vegetable,
  Metal,
  Insect
};

enum class FoodVariation{
  Var1,
  Var2,
  Var3
};

static void FailCheck(bool result){
  if (!result){
    std::cout << "Load Fail!" << std::endl;
  }
  else{
    std::cout << "Load OK!" << std::endl;
  }
}