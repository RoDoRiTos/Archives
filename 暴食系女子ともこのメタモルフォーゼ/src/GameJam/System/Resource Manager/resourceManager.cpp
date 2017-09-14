#include "resourceManager.hpp"

bool hidden::AudioManager::Insert(std::string filepath, AudioKey key){
  std::map<AudioKey, Media>::iterator it = resource.find(key);

  if (it != resource.end()){
    return false;
  }

  Media temp(filepath);
  resource.insert(std::make_pair(key, temp));
  return true;
}

Media hidden::AudioManager::Get(AudioKey key){
  return resource.find(key)->second;
}

bool hidden::TextureManager::Insert(std::string filepath, TextureKey key){
  std::map<TextureKey, Texture>::iterator it = resource.find(key);

  if (it != resource.end()){
    return false;
  }

  Texture temp(filepath);
  resource.insert(std::make_pair(key, temp));
  return true;
}

Texture hidden::TextureManager::Get(TextureKey key){
  return resource.find(key)->second;
}