#pragma once

#include <memory>
#include "scene.hpp"
#include "../../Scenes/Title/title.hpp"

class SceneManager{
private:
  std::shared_ptr<Scene> current_scene;
  std::shared_ptr<Scene> previous_scene;

public:
  SceneManager();

  void ChangeScene(std::shared_ptr<Scene> scene);
  bool UndoChange();

  void Update();
  void Draw();
};