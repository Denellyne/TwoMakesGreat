#include "Entity.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <cassert>

Entity::Entity(const char *texturePath, std::weak_ptr<SDL_Renderer> renderer)
    : _texture(LTexture(texturePath, renderer)) {}

bool Entity::render() const { return this->_texture.render(this->_pos); }
