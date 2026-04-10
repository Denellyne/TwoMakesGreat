#pragma once
#include "../Utils/Math/math.h"
#include "defines.h"
#include "typedef.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cassert>
#include <vector>

class RenderWindow {
public:
  RenderWindow() = delete;
  RenderWindow(const unsigned refreshRate = 60);
  ~RenderWindow();
  void render(bool *isRunning);
  void pushEntity(EntityPtr entity) { _entities.emplace_back(entity); }
  void pushUITexture(EntityPtr texture) { _ui.emplace_back(texture); }
  void clearEntities() { _entities.clear(); }
  void clearUI() { _ui.clear(); }
  RendererWPtr getRenderer();
  TTFWPtr getTTF();
  float getRefreshRate() const { return this->_refreshRate; }

private:
  struct SDLDeleter {
    void operator()(SDL_Renderer *ptr) const { SDL_DestroyRenderer(ptr); }
    void operator()(TTF_TextEngine *ptr) const {
      TTF_DestroyRendererTextEngine(ptr);
    }
  };

  bool createWindow(const int width, const int height, const char *name);
  bool renderEntities() const;
  bool renderUI() const;
  void setFrameRate(const unsigned refreshRate);
  void handleInput();

  float _refreshRate = 0.f;
  Utils::Vec2 _dimensions = {windowWidth, windowHeight};
  RendererPtr _renderer{nullptr};
  TTFPtr _ttf{nullptr};
  SDL_Window *_window = nullptr;
  std::vector<EntityPtr> _entities;
  std::vector<EntityPtr> _ui;
};
