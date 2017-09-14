#pragma once
#include "../Stats/status.hpp"

class DataManager{
private:
  Status* status_ref;
public:

  void setRef(Status* ref);
  void save();
  GameData load();
};