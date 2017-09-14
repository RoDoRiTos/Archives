#pragma once

class SceneManager;

class Scene{
protected:
  SceneManager* scene_manager;
public:
  Scene() = default;
  void SetManagerRef(SceneManager* ref){
    scene_manager = ref;
  }
  virtual void Update() = 0;
  virtual void Draw() = 0;
};