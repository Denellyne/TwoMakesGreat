#pragma once
#include "Entity/Entity.h"
#include <SDL3/SDL.h>
#include <cassert>
#include <memory>
#include <vector>

class RenderWindow {
public:
  RenderWindow() = delete;
  RenderWindow(const unsigned refreshRate);
  ~RenderWindow();
  void render();
  void pushEntity(Entity &&entity) {
    _entities.emplace_back(std::move(entity));
  }
  void clearEntities() { _entities.clear(); }
  void pushUITexture(Entity &&texture) { _ui.emplace_back(std::move(texture)); }
  void clearUI() { _ui.clear(); }
  std::weak_ptr<SDL_Renderer> getRenderer();

private:
  struct SDLDeleter {
    void operator()(SDL_Renderer *ptr) const { SDL_DestroyRenderer(ptr); }
  };
  bool createWindow(const int width, const int height, const char *name);
  bool renderEntities();
  bool renderUI();
  void setFrameRate(const unsigned refreshRate);

  std::shared_ptr<SDL_Renderer> _renderer{nullptr};
  SDL_Window *_window = nullptr;
  float refreshRate = 0.f;
  std::vector<Entity> _entities;
  std::vector<Entity> _ui;
};
