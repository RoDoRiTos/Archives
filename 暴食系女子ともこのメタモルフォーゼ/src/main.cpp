#include "GameJam/System/Scene Manager/sceneManager.hpp"
#include "GameJam/System/commons.hpp"

int main() {
  App::Get();
  SceneManager manager;
  while (App::Get().isOpen()) {
    App::Get().begin();
    
    manager.Update();
    manager.Draw();

    App::Get().end();
  }
}
