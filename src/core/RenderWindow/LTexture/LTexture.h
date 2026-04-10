#pragma once
#include "../../Utils/Math/math.h"
#include "../typedef.h"
#include <SDL3/SDL_render.h>
#include <memory>
class LTexture {
public:
  LTexture() {};
  LTexture(const char *texturePath, RendererWPtr renderer);
  LTexture(const LTexture &) = delete;
  LTexture &operator=(const LTexture &) = delete;
  LTexture(LTexture &&) = default;
  bool render(const Utils::Vec2 pos, const Utils::Vec2 dimensions) const;
  SDL_Texture *getTexture() const { return this->_texture.get(); }
  std::weak_ptr<SDL_Renderer> getRenderer() const { return this->_renderer; }

private:
  struct SDLDeleter {
    void operator()(SDL_Texture *ptr) const { SDL_DestroyTexture(ptr); }
  };
  typedef std::unique_ptr<SDL_Texture, SDLDeleter> TexturePtr;

  TexturePtr _texture = nullptr;
  RendererWPtr _renderer;
  SDL_Texture *loadTexture(const char *texturePath);
};
