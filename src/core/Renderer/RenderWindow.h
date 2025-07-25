#pragma once
#include "Entities/Entities.h"
#include <SDL3/SDL.h>
#include <cassert>
#include <memory>
#include <vector>

class RenderWindow {
public:
  RenderWindow();
  ~RenderWindow();

private:
  bool createWindow(int width, int height, const char *name);
  void render();
  void renderEntities();

  SDL_Renderer *_renderer = nullptr;
  SDL_Window *_window = nullptr;
  std::vector<std::unique_ptr<Entities>> _entities;
};
