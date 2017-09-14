#pragma once
#include <string>

enum Upgrade_ID{
  UPGRADE0,
  UPGRADE1,
  UPGRADE2,
  UPGRADE3,
  UPGRADE4,
  UPGRADE5,
  null = -1,
};

namespace Upg{
  struct Upgrade_Effect{
    unsigned __int64 click_effect;
    unsigned __int64 automatic_effect;
    double ratio_effect;
  };
  typedef Upgrade_Effect Effect;

  struct Upgrade_Data{
    Upgrade_ID id;
    unsigned __int64 price;
    float price_ratio;
  };
  typedef Upgrade_Data Data;
}

class Upgrade{
private:
  Upg::Effect effect;
  Upg::Data data;
  unsigned short quantity;
public:
  Upgrade();
  Upgrade(int id);

  Upg::Effect getEffect();
  Upg::Data getData();
  void setQty(unsigned short value);
  void addQty();
  unsigned short getQuantity();
};