#pragma once
#include "../../Utils/Math/math.h"
#include <SDL3/SDL_render.h>
class Entities {
public:
  Entities(const char *texturePath, SDL_Renderer *renderer);
  ~Entities();
  void render();
  SDL_Texture *loadTexture(const char *texturePath);

private:
  SDL_Texture *_texture = nullptr;
  SDL_Renderer *_renderer;
  Utils::Vec2 _pos{0, 0};
};
