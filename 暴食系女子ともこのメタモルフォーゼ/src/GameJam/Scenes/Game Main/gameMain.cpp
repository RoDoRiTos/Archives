#include "gameMain.hpp"

GameMain::GameMain(){
  Reset();
  FailCheck(ResTex.Insert("res/gameMain/tomoko.png", TextureKey::GameTomoko));
  FailCheck(ResTex.Insert("res/gameMain/caffeteria.png", TextureKey::GameBG));
  FailCheck(ResTex.Insert("res/gameMain/numbers.png", TextureKey::Numbers));
  FailCheck(ResTex.Insert("res/gameMain/plate.png", TextureKey::Plate));
  FailCheck(ResTex.Insert("res/gameMain/vegetables.png", TextureKey::Vegetables));
  FailCheck(ResTex.Insert("res/gameMain/metal.png", TextureKey::Metal));
  FailCheck(ResTex.Insert("res/gameMain/insect.png", TextureKey::Insect));
  FailCheck(ResMed.Insert("res/sound/gameMain.wav", AudioKey::Game));
  FailCheck(ResMed.Insert("res/sound/eating.wav", AudioKey::Eating));
  FailCheck(ResMed.Insert("res/sound/time_out.wav", AudioKey::TimeOut));
  plates[0] = Box{ Vec2f(-325, -420), Vec2f(150, 150) };
  plates[1] = Box{ Vec2f(-75, -420), Vec2f(150, 150) };
  plates[2] = Box{ Vec2f(175, -420), Vec2f(150, 150) };
  timer_pos[3] = Box{ Vec2f(-150, 400), Vec2f(60, 60) };
  timer_pos[2] = Box{ Vec2f(-90, 400), Vec2f(60, 60) };
  timer_pos[1] = Box{ Vec2f(30, 400), Vec2f(60, 60) };
  timer_pos[0] = Box{ Vec2f(90, 400), Vec2f(60, 60) };
  init_input = false;
  is_game_end = false;
  is_end = false;
  result = { 0, 0, 0 };
  time_limit = TIMELIMITMAX + ENDWAITTIME;
}

void GameMain::Update(){
  if (true == is_game_end){
	  if (ResMed.Get(AudioKey::Game).isPlaying()){
		  ResMed.Get(AudioKey::Game).stop();
	  }
	if (!ResMed.Get(AudioKey::TimeOut).isPlaying()){
		ResMed.Get(AudioKey::TimeOut).play();
	}
  }
  if (true == is_end){
	  scene_manager->ChangeScene(std::shared_ptr<Result>(new Result(result)));
	  return;
  }

  if (!ResMed.Get(AudioKey::Game).isPlaying()){
    ResMed.Get(AudioKey::Game).play();
    ResMed.Get(AudioKey::Game).looping(true);
  }
  if (food_click_limit == 0){
    if (Collision::MouseToBox(App::Get().mousePosition(), food[0]->GetBox())){
      if (App::Get().isPushButton(Mouse::LEFT)){
        ResMed.Get(AudioKey::Eating).play();
        selected.push_back(SelectedFood(Position::Left, food[0]->GetFoodType(), food[0]->GetFoodVariation()));
        AddFood(food[0]->GetFoodType());
        Reset();
      }
    }

    if (App::Get().isPushKey(GLFW_KEY_LEFT_SHIFT) || App::Get().isPushKey('Z') || App::Get().isPushKey(GLFW_KEY_LEFT)){
      ResMed.Get(AudioKey::Eating).play();
      selected.push_back(SelectedFood(Position::Left, food[0]->GetFoodType(), food[0]->GetFoodVariation()));
      AddFood(food[0]->GetFoodType());
      Reset();
    }

    if (Collision::MouseToBox(App::Get().mousePosition(), food[1]->GetBox())){
      if (App::Get().isPushButton(Mouse::LEFT)){
        ResMed.Get(AudioKey::Eating).play();
        selected.push_back(SelectedFood(Position::Middle, food[1]->GetFoodType(), food[1]->GetFoodVariation()));
        AddFood(food[1]->GetFoodType());
        Reset();
      }
    }

    if (App::Get().isPushKey(GLFW_KEY_SPACE) || App::Get().isPushKey('B') ||App::Get().isPushKey(GLFW_KEY_DOWN)){
      ResMed.Get(AudioKey::Eating).play();
      selected.push_back(SelectedFood(Position::Middle, food[1]->GetFoodType(), food[1]->GetFoodVariation()));
      AddFood(food[1]->GetFoodType());
      Reset();
    }

    if (Collision::MouseToBox(App::Get().mousePosition(), food[2]->GetBox())){
      if (App::Get().isPushButton(Mouse::LEFT)){
        ResMed.Get(AudioKey::Eating).play();
        selected.push_back(SelectedFood(Position::Right, food[2]->GetFoodType(), food[2]->GetFoodVariation()));
        AddFood(food[2]->GetFoodType());
        Reset();
      }
    }

    if (App::Get().isPushKey(GLFW_KEY_RIGHT_SHIFT) || App::Get().isPushKey(GLFW_KEY_SLASH) || App::Get().isPushKey(GLFW_KEY_RIGHT)){
      ResMed.Get(AudioKey::Eating).play();
      selected.push_back(SelectedFood(Position::Right, food[2]->GetFoodType(), food[2]->GetFoodVariation()));
      AddFood(food[2]->GetFoodType());
      Reset();
    }
  }

  for (auto& itr : selected){
    itr.Update();
  }

  UpdateList();
  if (true != is_game_end){
	  if (food_click_limit > 0){
		  food_click_limit--;
	  }
  }

  if (init_input){
    time_limit--;
  }

  if (time_limit < ENDWAITTIME){
    is_game_end = true;
  }
  if (time_limit < 0){
	  is_end = true;
  }
}

void GameMain::Draw(){
  App::Get().bgColor(Color::maroon);

  drawTextureBox(-360, -480, 720, 960, 0, 0, 720, 960, ResTex.Get(TextureKey::GameBG));

  drawTextureBox(-360, -580, 720, 960, 0, 0, 720, 960, ResTex.Get(TextureKey::GameTomoko));

  if (is_game_end != true){
    DisplayedTimer(time_limit);
  }
  else{
    /* "I—¹"‚Ì•¶Žš•\‹L */

  }

  for (int i = 0; i < 3; i++)
  {
    drawTextureBox(plates[i].pos.x(), plates[i].pos.y(), plates[i].size.x(), plates[i].size.y(),
      0, 0, 512, 512, ResTex.Get(TextureKey::Plate));
    food[i]->Draw();
  }

  for (auto itr : selected){
    itr.Draw();
  }
}

void GameMain::Reset()
{
  pattern = rand(1, 6);
  Shuffle();
  init_input = true;
  food_click_limit = FOODCLICKLIMIT;
}

void GameMain::Shuffle()
{
  switch (pattern)
  {
  case 1:
    food.clear();
    food.emplace_back(std::make_shared<Vegetables>());
    food.emplace_back(std::make_shared<Metal>());
    food.emplace_back(std::make_shared<Insect>());
    break;
  case 2:
    food.clear();
    food.emplace_back(std::make_shared<Vegetables>());
    food.emplace_back(std::make_shared<Insect>());
    food.emplace_back(std::make_shared<Metal>());
    break;
  case 3:
    food.clear();
    food.emplace_back(std::make_shared<Insect>());
    food.emplace_back(std::make_shared<Vegetables>());
    food.emplace_back(std::make_shared<Metal>());
    break;
  case 4:
    food.clear();
    food.emplace_back(std::make_shared<Insect>());
    food.emplace_back(std::make_shared<Metal>());
    food.emplace_back(std::make_shared<Vegetables>());
    break;
  case 5:
    food.clear();
    food.emplace_back(std::make_shared<Metal>());
    food.emplace_back(std::make_shared<Insect>());
    food.emplace_back(std::make_shared<Vegetables>());
    break;
  case 6:
    food.clear();
    food.emplace_back(std::make_shared<Metal>());
    food.emplace_back(std::make_shared<Vegetables>());
    food.emplace_back(std::make_shared<Insect>());
    break;
  }
  SetFoodPos();
}



void GameMain::SetFoodPos()
{
  food[0]->SetBox(Box{ Vec2f(-325, -400), Vec2f(150, 150) });
  food[1]->SetBox(Box{ Vec2f(-75, -400), Vec2f(150, 150) });
  food[2]->SetBox(Box{ Vec2f(175, -400), Vec2f(150, 150) });
}

void GameMain::UpdateList(){
  std::list<SelectedFood>::iterator itr = selected.begin();

  if (selected.size() > 1){
    for (itr; itr != selected.end(); itr++){
      if (!itr->IsActive()){
        itr = selected.erase(itr);
      }
    }
  }
  else{
    if (!itr->IsActive()){
      selected.clear();
    }
  }
}

void GameMain::DisplayedTimer(int _time){
	unsigned int time = ((_time - ENDWAITTIME) * 10) / 6;
  while (time > 0){
    time_vector.push_back(time % 10);
    time /= 10;
  }
  timer_font.size(60);

  for (int i = 0; i != time_vector.size(); ++i){
    SwitchNomber(time_vector[i], timer_pos[i]);
  }

  for (int i = 3; i > time_vector.size() - 1; --i){
    drawTextureBox(timer_pos[i].pos.x(), timer_pos[i].pos.y(), timer_pos[i].size.x(), timer_pos[i].size.y(),
      128, 64, 64, 64, ResTex.Get(TextureKey::Numbers));
  }

  time_vector.clear();
}

void GameMain::SwitchNomber(int _value, Box _box){
  switch (_value){
  case 0:
    drawTextureBox(_box.pos.x(), _box.pos.y(), _box.size.x(), _box.size.y(),
      128, 64, 64, 64, ResTex.Get(TextureKey::Numbers));
    break;

  case 1:
    drawTextureBox(_box.pos.x(), _box.pos.y(), _box.size.x(), _box.size.y(),
      0, 0, 64, 64, ResTex.Get(TextureKey::Numbers));
    break;

  case 2:
    drawTextureBox(_box.pos.x(), _box.pos.y(), _box.size.x(), _box.size.y(),
      64, 0, 64, 64, ResTex.Get(TextureKey::Numbers));
    break;

  case 3:
    drawTextureBox(_box.pos.x(), _box.pos.y(), _box.size.x(), _box.size.y(),
      128, 0, 64, 64, ResTex.Get(TextureKey::Numbers));
    break;

  case 4:
    drawTextureBox(_box.pos.x(), _box.pos.y(), _box.size.x(), _box.size.y(),
      192, 0, 64, 64, ResTex.Get(TextureKey::Numbers));
    break;

  case 5:
    drawTextureBox(_box.pos.x(), _box.pos.y(), _box.size.x(), _box.size.y(),
      256, 0, 64, 64, ResTex.Get(TextureKey::Numbers));
    break;

  case 6:
    drawTextureBox(_box.pos.x(), _box.pos.y(), _box.size.x(), _box.size.y(),
      320, 0, 64, 64, ResTex.Get(TextureKey::Numbers));
    break;

  case 7:
    drawTextureBox(_box.pos.x(), _box.pos.y(), _box.size.x(), _box.size.y(),
      384, 0, 64, 64, ResTex.Get(TextureKey::Numbers));
    break;

  case 8:
    drawTextureBox(_box.pos.x(), _box.pos.y(), _box.size.x(), _box.size.y(),
      0, 64, 64, 64, ResTex.Get(TextureKey::Numbers));
    break;

  case 9:
    drawTextureBox(_box.pos.x(), _box.pos.y(), _box.size.x(), _box.size.y(),
      64, 64, 64, 64, ResTex.Get(TextureKey::Numbers));
    break;

  default:
    drawTextureBox(_box.pos.x(), _box.pos.y(), _box.size.x(), _box.size.y(),
      128, 64, 64, 64, ResTex.Get(TextureKey::Numbers));
  }
}

void GameMain::AddFood(FoodType foodtype){
  switch (foodtype){
  case FoodType::Vegetable:
    result.vegetable += 1;
    break;
  
  case FoodType::Metal:
    result.metal += 1;
    break;

  case FoodType::Insect:
    result.insect += 1;
    break;
  }
}