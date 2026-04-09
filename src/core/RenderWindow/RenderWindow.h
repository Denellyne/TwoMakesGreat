#pragma once
#include "Entity/Entity.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cassert>
#include <memory>
#include <vector>

class RenderWindow {
public:
  RenderWindow() = delete;
  RenderWindow(const unsigned refreshRate);
  ~RenderWindow();
  void render(bool *isRunning);
  void pushEntity(Entity *entity) {
    _entities.emplace_back(std::unique_ptr<Entity>(entity));
  }
  void pushUITexture(Entity *texture) {
    _ui.emplace_back(std::unique_ptr<Entity>(texture));
  }
  void clearEntities() { _entities.clear(); }
  void clearUI() { _ui.clear(); }
  std::weak_ptr<SDL_Renderer> getRenderer();
  std::weak_ptr<TTF_TextEngine> getTTF();

  float refreshRate = 0.f;

private:
  struct SDLDeleter {
    void operator()(SDL_Renderer *ptr) const { SDL_DestroyRenderer(ptr); }
    void operator()(TTF_TextEngine *ptr) const {
      TTF_DestroyRendererTextEngine(ptr);
    }
  };
  bool createWindow(const int width, const int height, const char *name);
  bool renderEntities();
  bool renderUI();
  void setFrameRate(const unsigned refreshRate);

  std::shared_ptr<SDL_Renderer> _renderer{nullptr};
  std::shared_ptr<TTF_TextEngine> _ttf{nullptr};
  SDL_Window *_window = nullptr;
  std::vector<std::unique_ptr<Entity>> _entities;
  std::vector<std::unique_ptr<Entity>> _ui;
};
