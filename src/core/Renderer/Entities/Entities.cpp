#include "Entities.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <cassert>

Entities::Entities(const char *texturePath, SDL_Renderer *renderer)
    : _renderer(renderer) {

  _texture = loadTexture(texturePath);
  assert(_texture != nullptr);
}
Entities::~Entities() {
  SDL_DestroyTexture(_texture);

  _texture = nullptr;
}

void Entities::render() {
  assert(_texture != nullptr);

  float x, y;

  SDL_GetTextureSize(_texture, &x, &y);

  SDL_FRect rect{_pos.m_x, _pos.m_y, x, y};
  if (SDL_RenderTexture(_renderer, _texture, NULL, NULL) == false)
    SDL_Log("Rendering texture failure: %s", SDL_GetError());
}

SDL_Texture *Entities::loadTexture(const char *texturePath) {

  SDL_Texture *texture = IMG_LoadTexture(_renderer, texturePath);
  if (texture == NULL) {
    SDL_Log("Creation of texture failed: %s", SDL_GetError());
    return nullptr;
  }
  return texture;
}
