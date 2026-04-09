#pragma once
#include "../LTexture/LTexture.h"
#include <SDL3/SDL_render.h>
class Entity {
public:
  Entity(const char *texturePath, std::weak_ptr<SDL_Renderer> renderer,
         Utils::Vec2 pos = {0, 0}, Utils::Vec2 dimensions = {0, 0});
  virtual bool render() const;

protected:
  LTexture _texture;
  Utils::Vec2 _pos{0, 0};
  Utils::Vec2 _dimensions{0, 0};
};
