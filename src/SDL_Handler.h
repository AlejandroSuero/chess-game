#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2_image/SDL_image.h>

class SDL_Handler
{
public:
  SDL_Handler();
  ~SDL_Handler();
  void init();
  void clean_up();
  void render_background();
  void render_board();
  void handle_events();
  void render_texture(SDL_Texture *texture, int t_x, int t_y, int x, int y);
  SDL_Texture *load_texture(const char *path);

public:
  bool handling_events = true;
  const char *PIECES_PATH = "../resources/Pieces.png";

private:
  const int m_SCREEN_WIDTH = 900;
  const int m_SCREEN_HEIGHT = 900;
  const int m_BOARD_SIZE = 720;
  const int m_CELL_SIZE = m_BOARD_SIZE / 8;

private:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  SDL_Event m_event{};
  SDL_Texture *m_texture{};
  int m_win_width = m_SCREEN_WIDTH;
  int m_win_height = m_SCREEN_HEIGHT;
#if defined(__APPLE__) || defined(__MACH__)
  Uint32 m_time_left();
  Uint32 m_next_time = SDL_GetTicks() + 60;
#endif
};
