#include "SDL_Handler.h"
#include <iostream>

SDL_Handler::SDL_Handler()
{
  m_window = nullptr;
  m_renderer = nullptr;
}

void SDL_Handler::clean_up()
{
  if (m_window != nullptr)
    SDL_DestroyWindow(m_window);
  if (m_renderer != nullptr)
    SDL_DestroyRenderer(m_renderer);
  std::cout << "Bye!" << std::endl;
  SDL_Quit();
}

SDL_Handler::~SDL_Handler() { clean_up(); }

void SDL_Handler::render_background()
{
  SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(m_renderer);
  SDL_SetRenderDrawColor(m_renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(m_renderer);
  SDL_RenderPresent(m_renderer);
}

bool SDL_Handler::init()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }
  else
  {
    std::cout << "SDL initialized" << std::endl;
  }

  m_window = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (m_window == nullptr)
  {
    std::cout << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }
  m_renderer = SDL_CreateRenderer(
      m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (m_renderer == nullptr)
  {
    std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  return true;
}
