#pragma once

#include "../../System/Scene Manager/sceneManager.hpp"
#include "../Result/result.hpp"
#include "../../System/commons.hpp"
#include "../../Foods/FoodObject.hpp"
#include "../../Foods/selectedFood.hpp"
#include "../../Foods/Insect/Insect.hpp"
#include "../../Foods/Metal/Metal.hpp"
#include "../../Foods/Vegetables/Vegetables.hpp"
#include "../../Foods/resultData.hpp"
#include <fstream>
#include <vector>

#define FOODTEXTURESIZE 100
#define FOODTOFOODLENGTH 200
#define TIMELIMITMAX 600
#define ENDWAITTIME 60 * 2
#define FOODCLICKLIMIT 5

class GameMain : public Scene{
private:
  void LoadSettings();
  std::vector<std::shared_ptr<FoodObject>> food;
  std::list<SelectedFood> selected;
  Box plates[3];
  ResultData result;

  Random rand;
  Font timer_font = Font("res/meiryo.ttc");
  int time_limit = TIMELIMITMAX;
  std::vector<int> time_vector;
  Box timer_pos[4];
  bool init_input;
  bool is_game_end;
  bool is_end;
  int pattern = rand(1, 6);
  int food_click_limit = 0;

public:
  GameMain();
  void Update() override;
  void Draw() override;
  void Shuffle();
  void Reset();
  void SetFoodPos();
  void UpdateList();
  void DisplayedTimer(int _time);
  void SwitchNomber(int _value,Box _box);
  void AddFood(FoodType foodtype);
};