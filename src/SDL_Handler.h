#pragma once

#include <SDL.h>

class SDL_Handler
{
public:
  SDL_Handler();
  ~SDL_Handler();
  void init();
  void clean_up();
  void render_background(int width, int height);
  void render_board(int win_width, int win_height);
  void handle_events();

public:
  bool handling_events = true;

private:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  SDL_Event m_event;
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 800;
  const int BOARD_WIDTH = 640;
  const int BOARD_HEIGHT = 640;
  int m_win_width = SCREEN_WIDTH;
  int m_win_height = SCREEN_HEIGHT;
};
