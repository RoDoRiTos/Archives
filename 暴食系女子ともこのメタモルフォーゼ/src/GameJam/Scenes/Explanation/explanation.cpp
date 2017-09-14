#include "explanation.hpp"

Explanation::Explanation(){
  FailCheck(ResTex.Insert("res/title/rule.png", TextureKey::Rules));
}

void Explanation::Update(){

}

void Explanation::Draw(){
  App::Get().bgColor(Color::white);

  drawTextureBox(-256, -200, 512, 600, 0, 0, 512, 512, ResTex.Get(TextureKey::Rules));
  Box return_title_box{ Vec2f(-200, -400), Vec2f(400, 100) };
  drawTextureBox(return_title_box.pos.x(), return_title_box.pos.y(), return_title_box.size.x(), return_title_box.size.y(),
    52, 213, 414, 87, ResTex.Get(TextureKey::BackButton));
  if (Collision::MouseToBox(App::Get().mousePosition(), return_title_box)){
    if (App::Get().isPushButton(Mouse::LEFT)){
      ResMed.Get(AudioKey::Select).play();
      scene_manager->ChangeScene(std::make_shared<Title>());
    }
  }

}