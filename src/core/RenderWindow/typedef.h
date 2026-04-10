#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
typedef std::weak_ptr<SDL_Renderer> RendererWPtr;
typedef std::shared_ptr<SDL_Renderer> RendererPtr;
typedef std::shared_ptr<TTF_TextEngine> TTFPtr;
typedef std::weak_ptr<TTF_TextEngine> TTFWPtr;
