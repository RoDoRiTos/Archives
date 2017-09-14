#pragma once

#include "../System/commons.hpp"
#include <ctime>

class Rand{
private:
  Rand() = default;
public:
  Rand(Rand&) = delete;
  static Random& Get(){
    static Random rand;
    rand.setSeed((u_int)time(nullptr));
    return rand;
  }
};