#include "RenderWindow.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdint>
#include <print>

RenderWindow::RenderWindow(const unsigned refreshRate) {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return;
  }
  if (!TTF_Init()) {
    SDL_Log("Couldn't initialize TTF: %s", SDL_GetError());
    return;
  }

  auto [w, h] = this->_dimensions;
  if (!createWindow(w, h, "TwoMakesGreat")) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return;
  }

  this->_ttf = TTFPtr(TTF_CreateRendererTextEngine(this->_renderer.get()),
                      RenderWindow::SDLDeleter{});

  if (!this->_ttf.get()) {
    SDL_Log("Couldn't create TTF renderer: %s", SDL_GetError());
    return;
  }

  setFrameRate(refreshRate);
  std::println("Init Success");
}
RenderWindow::~RenderWindow() {
  SDL_DestroyWindow(this->_window);
  TTF_Quit();
  SDL_Quit();
}
void RenderWindow::setFrameRate(const unsigned refreshRate) {
  this->_refreshRate = 1000000000.f / refreshRate;
}

bool RenderWindow::createWindow(const int width, const int height,
                                const char *name) {

  this->_window = SDL_CreateWindow(name, width, height, SDL_WINDOW_RESIZABLE);
  if (this->_window == NULL) {
    SDL_Log("Unable to create window: %s", SDL_GetError());
    return false;
  }

  this->_renderer = RendererPtr(SDL_CreateRenderer(this->_window, NULL),
                                RenderWindow::SDLDeleter{});
  if (this->_renderer.get() == NULL) {
    SDL_Log("Unable to create renderer: %s", SDL_GetError());
    return false;
  }

  std::println("Window and Renderer created sucessfully");

  return true;
}

void RenderWindow::render(bool *isRunning) {
  const uint64_t startTicks = SDL_GetTicksNS();
  SDL_Event event;
  while (SDL_PollEvent(&event))
    if (event.type == SDL_EVENT_QUIT)
      *isRunning = false;
    else if (event.type == SDL_EVENT_WINDOW_RESIZED)
      this->_dimensions = {event.window.data1, event.window.data2};

  SDL_RenderClear(this->_renderer.get());
  if (renderUI() || renderEntities())
    *isRunning = false;

  SDL_RenderPresent(this->_renderer.get());

  const uint64_t endTicks = SDL_GetTicksNS();
  if (const uint64_t left = endTicks - startTicks; left < this->_refreshRate)
    SDL_DelayPrecise(this->_refreshRate - left);

  std::println("FPS:{}", (1000000000.f / (SDL_GetTicksNS() - startTicks)));
}

bool RenderWindow::renderUI() const {
  for (const auto &texture : this->_ui)
    if (texture->render())
      return 1;

  return 0;
}
bool RenderWindow::renderEntities() const {
  for (const auto &entity : this->_entities)
    if (entity->render())
      return 1;
  return 0;
}

RendererWPtr RenderWindow::getRenderer() {
  assert(this->_renderer.get() != nullptr);
  return this->_renderer;
}
TTFWPtr RenderWindow::getTTF() {
  assert(this->_ttf.get() != nullptr);
  return this->_ttf;
}
