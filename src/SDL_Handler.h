#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

class SDL_Handler
{
public:
  SDL_Handler();
  ~SDL_Handler();
  void init();
  void clean_up();
  void render_background();
  void render_board();
  void render_pieces();
  void render_numbers(int rank, int file, int y, int x, SDL_Color text_color);
  void handle_events();
  void render_texture(SDL_Rect p_src, SDL_Rect p_dst, SDL_Texture *p_texture);
  SDL_Texture *load_texture(const char *p_path);
  TTF_Font *load_font(const char *p_path);

public:
  bool handling_events = true;
  const char *PIECES_PATH = "../resources/images/Pieces.png";
  const char *FONT_PATH = "../resources/fonts/HackNerdFont-Regular.ttf";

private:
  const int m_SCREEN_WIDTH = 900;
  const int m_SCREEN_HEIGHT = 900;
  const int m_BOARD_SIZE = 720;
  const int m_CELL_SIZE = m_BOARD_SIZE / 8;
  const int m_PIECE_SIZE = 333;

private:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  SDL_Event m_event{};
  SDL_Texture *m_texture{};
  SDL_Surface *m_surface{};
  TTF_Font *m_font{};
  int m_board_width = m_BOARD_SIZE;
  int m_board_height = m_BOARD_SIZE;
  int m_win_width = m_SCREEN_WIDTH;
  int m_win_height = m_SCREEN_HEIGHT;
#if defined(__APPLE__) || defined(__MACH__)
  Uint32 m_time_left();
  Uint32 m_next_time = SDL_GetTicks() + 60;
#endif
};
