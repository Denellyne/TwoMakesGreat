#include "RenderWindow.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

RenderWindow::RenderWindow() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return;
  }

  if (!createWindow(1024, 720, "Coop Games")) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return;
  }
  std::cout << "Init Success\n";

  // _entities.emplace_back(std::make_unique<Entities>("./test.png",
  // _renderer));
  render();
}
RenderWindow::~RenderWindow() {
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);
  SDL_Quit();
}

bool RenderWindow::createWindow(int width, int height, const char *name) {

  _window = SDL_CreateWindow(name, width, height, SDL_WINDOW_RESIZABLE);
  if (_window == NULL) {
    SDL_Log("Unable to create window: %s", SDL_GetError());
    return false;
  }

  _renderer = SDL_CreateRenderer(_window, NULL);
  if (_renderer == NULL) {
    SDL_Log("Unable to create renderer: %s", SDL_GetError());
    return false;
  }

  std::cout << "Window and RenderWindow created sucessfully\n";

  return true;
}

void RenderWindow::render() {
  bool isRunning = true;
  while (isRunning) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT)
        isRunning = false;
    }
    SDL_RenderClear(_renderer);
    renderEntities();
    SDL_RenderPresent(_renderer);
  }
}

void RenderWindow::renderEntities() {
  for (auto &entity : _entities)
    entity->render();
}
