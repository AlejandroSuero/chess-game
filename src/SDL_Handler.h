#pragma once

#include <SDL.h>

class SDL_Handler
{
public:
  SDL_Handler();
  ~SDL_Handler();
  bool init();
  void clean_up();
  void render_background();

public:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  SDL_Event m_event;

  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;
};
