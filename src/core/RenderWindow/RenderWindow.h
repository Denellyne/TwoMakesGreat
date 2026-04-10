#pragma once
#include "Entity/Entity.h"
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
  void pushEntity(Entity *entity) { _entities.emplace_back(EntityPtr(entity)); }
  void pushUITexture(Entity *texture) { _ui.emplace_back(EntityPtr(texture)); }
  void clearEntities() { _entities.clear(); }
  void clearUI() { _ui.clear(); }
  RendererWPtr getRenderer();
  TTFWPtr getTTF();
  const float getRefreshRate() { return this->_refreshRate; }

private:
  struct SDLDeleter {
    void operator()(SDL_Renderer *ptr) const { SDL_DestroyRenderer(ptr); }
    void operator()(TTF_TextEngine *ptr) const {
      TTF_DestroyRendererTextEngine(ptr);
    }
  };
  typedef std::unique_ptr<Entity> EntityPtr;

  bool createWindow(const int width, const int height, const char *name);
  bool renderEntities() const;
  bool renderUI() const;
  void setFrameRate(const unsigned refreshRate);
  void handleInput();

  float _refreshRate = 0.f;
  Utils::Vec2 _dimensions = {1024, 720};
  RendererPtr _renderer{nullptr};
  TTFPtr _ttf{nullptr};
  SDL_Window *_window = nullptr;
  std::vector<EntityPtr> _entities;
  std::vector<EntityPtr> _ui;
};
