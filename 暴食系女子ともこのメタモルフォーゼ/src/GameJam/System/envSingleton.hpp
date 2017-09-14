#pragma once
#include "../../lib/framework.hpp"

class App{
private:
  App() = default;
public:
  App(App&) = delete;
  static AppEnv& Get(){
    static AppEnv instance(720, 960, false, true);
    return instance;
  }
};