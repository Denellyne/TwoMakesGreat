#pragma once
#include "../LTexture/LTexture.h"
#include <SDL3/SDL_render.h>
class Entity {
public:
  Entity(const char *texturePath, std::weak_ptr<SDL_Renderer> renderer);
  bool render() const;

private:
  LTexture _texture;
  Utils::Vec2 _pos{0, 0};
};
