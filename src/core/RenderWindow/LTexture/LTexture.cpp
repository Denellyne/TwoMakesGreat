#include "LTexture.h"
#include <SDL3_image/SDL_image.h>
#include <cassert>

LTexture::LTexture(const char *texturePath,
                   std::weak_ptr<SDL_Renderer> renderer)
    : _renderer(renderer) {

  this->_texture = std::unique_ptr<SDL_Texture, LTexture::SDLDeleter>(
      loadTexture(texturePath), LTexture::SDLDeleter{});
  assert(this->_texture != nullptr);
}

bool LTexture::render(const Utils::Vec2 pos,
                      const Utils::Vec2 dimensions) const {
  assert(this->_texture != nullptr);
  float x, y;

  if (!SDL_GetTextureSize(this->_texture.get(), &x, &y)) {
    SDL_Log("Unable to get texture parameters: %s", SDL_GetError());
    return 1;
  }

  SDL_FRect rect{pos.m_x, pos.m_y, x, y};
  if (dimensions.m_x != 0 || dimensions.m_y != 0) {
    rect.w = dimensions.m_x;
    rect.h = dimensions.m_y;
  }

  if (!SDL_RenderTexture(this->_renderer.lock().get(), this->_texture.get(),
                         NULL, &rect)) {
    SDL_Log("Rendering texture failure: %s", SDL_GetError());
    return 1;
  }
  return 0;
}

SDL_Texture *LTexture::loadTexture(const char *texturePath) {
  assert(this->_renderer.lock().get() != nullptr);

  SDL_Texture *texture =
      IMG_LoadTexture(this->_renderer.lock().get(), texturePath);
  if (!texture) {
    SDL_Log("Creation of texture failed: %s", SDL_GetError());
    return nullptr;
  }
  return texture;
}
