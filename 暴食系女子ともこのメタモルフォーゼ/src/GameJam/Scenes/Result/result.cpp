#include "result.hpp"

Result::Result(ResultData result)
{
  FailCheck(ResTex.Insert("res/result/dash.png", TextureKey::ResultDash));
  FailCheck(ResTex.Insert("res/result/door.png", TextureKey::ResultToilet));
  FailCheck(ResTex.Insert("res/result/failure.png", TextureKey::ResultFailure));
  FailCheck(ResTex.Insert("res/result/insect.png", TextureKey::ResultInsect));
  FailCheck(ResTex.Insert("res/result/metal.png", TextureKey::ResultMetal));
  FailCheck(ResTex.Insert("res/result/perfect_tomoko.png", TextureKey::ResultPerfect));
  FailCheck(ResTex.Insert("res/result/secret.png", TextureKey::ResultSecret));
  FailCheck(ResTex.Insert("res/result/retry.png", TextureKey::RetryButton));
  FailCheck(ResTex.Insert("res/result/title.png", TextureKey::BackTitleButton));
  FailCheck(ResMed.Insert("res/sound/dash.wav", AudioKey::Dash));
  FailCheck(ResMed.Insert("res/sound/restroom.wav", AudioKey::Restroom));
  FailCheck(ResMed.Insert("res/sound/result.wav", AudioKey::Result));
  FailCheck(ResMed.Insert("res/sound/perfect.wav", AudioKey::Success));
  FailCheck(ResMed.Insert("res/sound/failure.wav", AudioKey::Failure));
  this->result = result;
  CheckSuccess();
}

void Result::Update(){
  if (animation_count % 180 == 0 || App::Get().isPushButton(Mouse::LEFT))
  {
    AnimationChange();
  }

  if (animation == Animation::Dash){
    if (!ResMed.Get(AudioKey::Dash).isPlaying()){
      ResMed.Get(AudioKey::Dash).play();
    }
  }

  if (animation == Animation::Door){
    ResMed.Get(AudioKey::Dash).stop();
    if (!ResMed.Get(AudioKey::Restroom).isPlaying()){
      ResMed.Get(AudioKey::Restroom).play();
    }
  }

  if (animation == Animation::FadingOut){
    ResMed.Get(AudioKey::Restroom).stop();
  }

  AnimationUpdate();

  animation_count++;
  if (select_active)
    Select();
}

void Result::Draw(){
  App::Get().bgColor(Color::white);

  if (animation == Animation::Dash){
    drawTextureBox(-360, -480, 720, 960, 0, 0, 720, 960, ResTex.Get(TextureKey::ResultDash));
  }

  if (animation == Animation::Door || animation == Animation::FadingOut){
    drawTextureBox(-360, -480, 720, 960, 0, 0, 720, 960, ResTex.Get(TextureKey::ResultToilet));
  }

  font.size(50);

  //直すべき？
  if (animation == Animation::Select)
  {
    drawTextureBox(-360, -480, 720, 960, 0, 0, 720, 960, form);

    drawTextureBox(title_f.pos.x(), title_f.pos.y(), title_f.size.x(), title_f.size.y(),
      0, 0, 110, 32, ResTex.Get(TextureKey::BackTitleButton));

    drawTextureBox(retry_f.pos.x(), retry_f.pos.y(), retry_f.size.x(), retry_f.size.y(),
      0, 0, 110, 32, ResTex.Get(TextureKey::RetryButton));

    /*font.draw("タイトルへ", title_f.pos, Color::white);
    font.draw("リトライ", retry_f.pos, Color::white);*/
  }
  // フェイド用
  drawFillBox(background.pos.x(), background.pos.y(), background.size.x(), background.size.y(), Color(1, 1, 1, fadinf_a));

}

void Result::Select()
{

  if (Collision::MouseToBox(App::Get().mousePosition(), title_f)){
    if (App::Get().isPushButton(Mouse::LEFT)){
      App::Get().flushInput();
      StopBgm();
      scene_manager->ChangeScene(std::make_shared<Title>());
    }
  }

  if (Collision::MouseToBox(App::Get().mousePosition(), retry_f)){
    if (App::Get().isPushButton(Mouse::LEFT)){
      App::Get().flushInput();
      StopBgm();
      scene_manager->ChangeScene(std::make_shared<GameMain>());
    }
  }

}



void Result::AnimationChange()
{
  //TODO:切り替えはどうするか考える
  switch (animation)
  {
  case Animation::Dash:
    animation = Animation::Door;
    break;
  case Animation::Door:
    animation = Animation::FadingOut;
    break;
  case Animation::FadingOut:
    break;
  case Animation::Select:
    break;
  default:
    break;
  }

  TimeReset();

}

void Result::AnimationUpdate()
{

  switch (animation)
  {
  case Animation::Dash:
    break;
  case Animation::Door:
    break;
  case Animation::FadingOut:
    if (FadingOut())
    {
      animation = Animation::Select;
    }
    break;
  case Animation::Select:
    BgmPlay();
    if (FadingIn())
    {
      Select();
    }
    break;
  default:
    break;
  }
}

void Result::TimeReset()
{
  animation_count = 0;
}

bool Result::FadingOut()
{
  if (1 > fadinf_a)
  {
    fadinf_a += 0.01;
    return false;
  }
  if (1 <= fadinf_a){
    return true;
  }
}

bool Result::FadingIn()
{
  if (0 < fadinf_a)
  {
    fadinf_a -= 0.01;
    return false;
  }
  if (0 >= fadinf_a){
    return true;
  }
}


// 分岐
// 音楽、画像が変わる


void Result::BgmPlay()
{

   if (type == Type::Failure)
   {
     if (!ResMed.Get(AudioKey::Failure).isPlaying())
     {
       ResMed.Get(AudioKey::Failure).play();
     }
   }
   else if (type == Type::Success ||type == Type::Secret)
   {
     if (!ResMed.Get(AudioKey::Success).isPlaying())
     {
       ResMed.Get(AudioKey::Success).play();
     }
   }
   else
   {
     if (!ResMed.Get(AudioKey::Result).isPlaying())
     {
       ResMed.Get(AudioKey::Result).play();
     }
   }
}


void Result::TypeDecision()
{
  if (result.vegetable > result.metal)
  {

    if (result.vegetable > result.insect)
    {
      type = Type::Success;
      form = ResTex.Get(TextureKey::ResultPerfect);
    }
    else 
    {
      type = Type::Insect;
      form = ResTex.Get(TextureKey::ResultInsect);
    }
  }
  else
  {
    if (result.metal > result.insect)
    {
      type = Type::Metal;
      form = ResTex.Get(TextureKey::ResultMetal);
    }
    else
    {
      type = Type::Insect;
      form = ResTex.Get(TextureKey::ResultInsect);
    }
  }
}

void Result::CheckSuccess()
{
  TypeDecision();

  if (result.vegetable < SUCCESSMIN)
  {
    type = Type::Failure;
    form = ResTex.Get(TextureKey::ResultFailure);
  } 

  if (result.vegetable == SECRET_V&&
      result.metal == SECRET_M &&
      result.insect == SECRET_I){
    type = Type::Secret;
    form = ResTex.Get(TextureKey::ResultSecret);
  }
}


void Result::StopBgm()
{

  if (type == Type::Failure)
  {
      ResMed.Get(AudioKey::Failure).stop();
  }
  else if (type == Type::Success || type == Type::Secret)
  {
      ResMed.Get(AudioKey::Success).stop();
  }
  else
  {
      ResMed.Get(AudioKey::Result).stop();
  }
}
