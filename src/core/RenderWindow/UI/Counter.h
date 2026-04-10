#pragma once
#include "../Entity/Entity.h"
#include "../typedef.h"
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cassert>
#include <memory>
#include <string>

class Counter : public Entity {
public:
  Counter(const char *texturePath, RendererWPtr renderer, TTFWPtr ptr,
          const Utils::Vec2 pos = {0, 0}, const Utils::Vec2 dimensions = {0, 0},
          unsigned *const counter = 0)
      : Entity(texturePath, renderer, pos, dimensions), _ttf(ptr),
        _counter(counter) {
    _font = FontPtr(TTF_OpenFont("../res/fonts/font.ttf", this->_fontSize));
  }
  bool render(const Utils::Vec2 &dimensions) const override {
    assert(this->_font.get() != nullptr);
    assert(this->_ttf.lock().get() != nullptr);

    if (this->_texture.render(this->_pos, this->_dimensions, dimensions))
      return 1;

    const float x = this->_pos.m_x +
                    (std::abs(this->_dimensions.m_x - this->_fontSize) / 2);
    const float y = this->_pos.m_y +
                    (std::abs(this->_dimensions.m_y - this->_fontSize) / 2);

    if (SDL_Surface *surface = TTF_RenderText_Solid(
            this->_font.get(), std::to_string(*this->_counter).c_str(), 0,
            {0, 0, 0, 255});
        !surface) {
      SDL_Log("Couldn't render ttf text: %s", SDL_GetError());
      return 1;
    } else {
      if (SDL_Texture *texture = SDL_CreateTextureFromSurface(
              this->_texture.getRenderer().lock().get(), surface);
          !texture) {

        SDL_DestroySurface(surface);
        SDL_Log("Couldn't create texture from surface: %s", SDL_GetError());
        return 1;
      } else {
        SDL_DestroySurface(surface);
        if (LTexture::renderTexture(texture, this->_texture.getRenderer(),
                                    {x, y}, {this->_fontSize, this->_fontSize},
                                    dimensions)) {
          SDL_Log("Couldn't render text: %s", SDL_GetError());
          SDL_DestroyTexture(texture);
          return 1;
        }
        SDL_DestroyTexture(texture);
      }
    }
    return 0;
  }
  void setCounter(unsigned *const counter) { this->_counter = counter; }

private:
  struct TTFDeleter {
    void operator()(TTF_Font *ptr) const { TTF_CloseFont(ptr); }
  };

  typedef std::unique_ptr<TTF_Font, TTFDeleter> FontPtr;

  const float _fontSize = 32.f;
  TTFWPtr _ttf{};
  unsigned *_counter = nullptr;
  FontPtr _font{nullptr};
  // make texture for string and only create it again if the val changes
};
