#pragma once
#include "../../Utils/Math/math.h"
#include <SDL3/SDL_render.h>
#include <memory>
class LTexture {
public:
  LTexture() {};
  LTexture(const char *texturePath, std::weak_ptr<SDL_Renderer> renderer);
  LTexture(const LTexture &) = delete;
  LTexture &operator=(const LTexture &) = delete;
  LTexture(LTexture &&) = default;
  bool render(const Utils::Vec2 pos) const;

private:
  struct SDLDeleter {
    void operator()(SDL_Texture *ptr) const { SDL_DestroyTexture(ptr); }
  };
  std::unique_ptr<SDL_Texture, SDLDeleter> _texture = nullptr;
  std::weak_ptr<SDL_Renderer> _renderer;
  SDL_Texture *loadTexture(const char *texturePath);
};
