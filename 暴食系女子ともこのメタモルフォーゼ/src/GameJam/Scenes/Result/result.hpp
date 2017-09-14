#pragma once

#include "../../System/Scene Manager/sceneManager.hpp"
#include "../Title/title.hpp"
#include "../../System/commons.hpp"
#include "../../Utility/Collision/collision.hpp"
#include "../../Foods/resultData.hpp"
#define SUCCESSMIN 10
#define SECRET_V 6
#define SECRET_M 7
#define SECRET_I 3



class Result : public Scene{
private:

  // 名前は(仮)
  enum class Animation
  {
    Dash,
    Door,
    FadingOut, 
    Select,
  };

  enum class Type
  {
    Insect,
    Metal,
    Success,
    Failure,
    Secret,

  };

  Font font = Font("res/meiryo.ttc");
  Box title_f = Box{ Vec2f(-250, -400), Vec2f(200, 50) };
  Box retry_f = Box{ Vec2f(50, -400), Vec2f(200, 50) };
  Box background = Box{ Vec2f(-360, -480), Vec2f(720, 960) };
  Box keepout = Box{ Vec2f(-360, 960), Vec2f(720, 960) };
  int animation_count = 1;     // トイレに駆け込むシーンの切り替え時間
  bool select_active = false;
  Animation animation = Animation::Dash;
  float fadinf_a = 0;
  ResultData result;
  Type type;
  Texture form;

public:
  Result() = default;
  explicit Result(ResultData result);
  void Update() override;
  void Draw() override;
  void Select();
  void AnimationChange();
  void AnimationUpdate();
  bool FadingOut();
  bool FadingIn();
  void TimeReset();
  void BgmPlay();
  void TypeDecision(/*struct*/);
  void CheckSuccess();
  void StopBgm();
};