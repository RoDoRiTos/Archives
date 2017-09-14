#include "sceneManager.hpp"

SceneManager::SceneManager(){
  current_scene = std::make_shared<Title>();
  current_scene->SetManagerRef(this);
  previous_scene = nullptr;
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> scene){
  previous_scene = current_scene;
  current_scene = scene;
  current_scene->SetManagerRef(this);
}

bool SceneManager::UndoChange(){
  if (previous_scene != nullptr){
    current_scene = previous_scene;
    previous_scene = current_scene;
    return true;
  }
  return false;
}

void SceneManager::Update(){
  current_scene->Update();
}

void SceneManager::Draw(){
  current_scene->Draw();
}