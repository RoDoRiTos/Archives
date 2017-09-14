#include "title.hpp"

Title::Title(){
  FailCheck(ResTex.Insert("res/title/title.png", TextureKey::Title));
  FailCheck(ResTex.Insert("res/title/titlelogo.png", TextureKey::Logo));
  FailCheck(ResTex.Insert("res/title/back_button.png", TextureKey::BackButton));
  FailCheck(ResTex.Insert("res/title/gamestart_button.png", TextureKey::StartButton));
  FailCheck(ResTex.Insert("res/title/rules_button.png", TextureKey::RulesButton));
  FailCheck(ResMed.Insert("res/sound/title.wav", AudioKey::Title));
  FailCheck(ResMed.Insert("res/sound/select.wav", AudioKey::Select));
}

void Title::Update(){
  if (!ResMed.Get(AudioKey::Title).isPlaying()){
    ResMed.Get(AudioKey::Title).play();
  }
}

void Title::Draw(){
  App::Get().bgColor(Color::white);
  drawTextureBox(-360, -480, 720, 960, 0, 0, 720, 960, ResTex.Get(TextureKey::Title));
  drawTextureBox(-350, 200, 700, 200, 0, 0, 810, 200, ResTex.Get(TextureKey::Logo));
  Box start_button{ Vec2f(-200, -300), Vec2f(400, 100) };
  drawTextureBox(start_button.pos.x(), start_button.pos.y(), start_button.size.x(), start_button.size.y(),
    52, 213, 414, 87, ResTex.Get(TextureKey::StartButton));
  if (Collision::MouseToBox(App::Get().mousePosition(), start_button)){
    if (App::Get().isPushButton(Mouse::LEFT)){
      ResMed.Get(AudioKey::Select).play();
      ResMed.Get(AudioKey::Title).stop();
      scene_manager->ChangeScene(std::make_shared<GameMain>());
    }
  }

  Box rules_button{ Vec2f(-200, -400), Vec2f(400, 100) };
  drawTextureBox(rules_button.pos.x(), rules_button.pos.y(), rules_button.size.x(), rules_button.size.y(),
    52, 213, 414, 87, ResTex.Get(TextureKey::RulesButton));
  if (Collision::MouseToBox(App::Get().mousePosition(), rules_button)){
    if (App::Get().isPushButton(Mouse::LEFT)){
      ResMed.Get(AudioKey::Select).play();
      scene_manager->ChangeScene(std::make_shared<Explanation>());
    }
  }
}