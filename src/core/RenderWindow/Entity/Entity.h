#pragma once
#include "../LTexture/LTexture.h"
#include "../typedef.h"
#include <SDL3/SDL_render.h>

class Entity {
public:
  Entity(const char *texturePath, RendererWPtr renderer,
         const Utils::Vec2 pos = {0, 0}, const Utils::Vec2 dimensions = {0, 0});
  virtual bool render(const Utils::Vec2 &dimensions) const;
  void setPos(Utils::Vec2 pos) { this->_pos = pos; }

protected:
  LTexture _texture;
  Utils::Vec2 _pos{0, 0};
  Utils::Vec2 _dimensions{0, 0};
};
