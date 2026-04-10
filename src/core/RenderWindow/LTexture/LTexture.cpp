#include "LTexture.h"
#include "../defines.h"
#include <SDL3_image/SDL_image.h>
#include <cassert>

LTexture::LTexture(const char *texturePath, RendererWPtr renderer)
    : _renderer(renderer) {

  this->_texture = TexturePtr(loadTexture(texturePath), LTexture::SDLDeleter{});
  assert(this->_texture != nullptr);
}

bool LTexture::render(const Utils::Vec2 &pos, const Utils::Vec2 &dimensions,
                      const Utils::Vec2 &windowDimensions) const {
  assert(this->_texture != nullptr);

  if (const auto rect = scaleToWindowSize(this->_texture.get(), pos, dimensions,
                                          windowDimensions);
      rect.has_value()) {
    if (!SDL_RenderTexture(this->_renderer.lock().get(), this->_texture.get(),
                           NULL, &rect.value())) {
      SDL_Log("Rendering texture failure: %s", SDL_GetError());
      return 1;
    }
  } else
    return 1;
  return 0;
}
bool LTexture::renderTexture(SDL_Texture *const texture, RendererWPtr renderer,
                             const Utils::Vec2 &pos,
                             const Utils::Vec2 &dimensions,
                             const Utils::Vec2 &windowDimensions) {
  assert(texture != nullptr);
  assert(renderer.lock().get() != nullptr);
  if (const auto rect =
          scaleToWindowSize(texture, pos, dimensions, windowDimensions);
      rect.has_value()) {
    if (!SDL_RenderTexture(renderer.lock().get(), texture, NULL,
                           &rect.value())) {
      SDL_Log("Rendering texture failure: %s", SDL_GetError());
      return 1;
    }
  } else
    return 1;

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

constexpr std::optional<SDL_FRect>
LTexture::scaleToWindowSize(SDL_Texture *const texture, const Utils::Vec2 &pos,
                            const Utils::Vec2 &dimensions,
                            const Utils::Vec2 &windowDimensions) {

  const float scalerX = (windowDimensions.m_x / windowWidth);
  const float scalerY = (windowDimensions.m_y / windowHeight);

  SDL_FRect rect{pos.m_x * scalerX, pos.m_y * scalerY, 0, 0};
  if (dimensions.m_x != 0 || dimensions.m_y != 0) {
    rect.w = dimensions.m_x;
    rect.h = dimensions.m_y;
  } else {
    float x, y;

    if (!SDL_GetTextureSize(texture, &x, &y)) {
      SDL_Log("Unable to get texture parameters: %s", SDL_GetError());
      return std::nullopt;
    }
    rect.w = x;
    rect.h = y;
  }
  rect.w *= scalerX;
  rect.h *= scalerY;
  return rect;
}
