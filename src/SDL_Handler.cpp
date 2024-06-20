#include "SDL_Handler.h"
#include "FEN.h"
#include <SDL2_image/SDL_image.h>
#include <string>
#include <vector>

SDL_Handler::SDL_Handler()
{
  m_window = nullptr;
  m_renderer = nullptr;
  init();
}

void SDL_Handler::clean_up()
{
  if (m_window != nullptr)
    SDL_DestroyWindow(m_window);
  if (m_renderer != nullptr)
    SDL_DestroyRenderer(m_renderer);
  if (m_texture != nullptr)
    SDL_DestroyTexture(m_texture);
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Handler cleaned up");
  SDL_Quit();
}

SDL_Handler::~SDL_Handler() { clean_up(); }

void SDL_Handler::render_background()

{
  SDL_RenderClear(m_renderer);
  SDL_SetRenderDrawColor(m_renderer, 0, 0xFF, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(m_renderer);
  render_board();
  SDL_RenderPresent(m_renderer);
}

void SDL_Handler::render_texture(SDL_Texture *texture, int t_x, int t_y, int x,
                                 int y)
{
  SDL_Rect src;
  SDL_Rect dst;
  src.x = t_x;
  src.y = t_y;
  src.w = 333;
  src.h = 333;
  dst.x = x;
  dst.y = y;
  dst.w = dst.h = m_CELL_SIZE;
  SDL_RenderCopy(m_renderer, texture, &src, &dst);
}

void SDL_Handler::render_board()
{
  m_texture = load_texture(PIECES_PATH);
  // keep board on screen no matter the window size
  int board_width = m_win_width > m_BOARD_SIZE ? m_BOARD_SIZE : m_win_width;
  int board_height = m_win_height > m_BOARD_SIZE ? m_BOARD_SIZE : m_win_height;
  for (int file = 0; file < 8; file++)
  {
    for (int rank = 0; rank < 8; rank++)
    {
      bool is_white = (file + rank) % 2 == 0;
      if (is_white)
        SDL_SetRenderDrawColor(m_renderer, 197, 172, 170, SDL_ALPHA_OPAQUE);
      else
        SDL_SetRenderDrawColor(m_renderer, 89, 44, 42, SDL_ALPHA_OPAQUE);
      SDL_Rect rect;

#pragma region draw squares
      int offset_x = (m_win_width / 2) - (board_width / 2);
      int offset_y = (m_win_height / 2) - (board_height / 2);
      int x = offset_x + (m_CELL_SIZE)*rank;
      int y = offset_y + (m_CELL_SIZE)*file;
      rect.x = x;
      rect.y = y;
      rect.w = rect.h = m_CELL_SIZE;
      SDL_RenderFillRect(m_renderer, &rect);
#pragma endregion
#pragma region draw pieces

#pragma endregion
    }
  }
  std::vector<std::string> fen = FEN::get_initial_positions();
  std::string initial_fen = FEN::get_positions(fen);
  int file = 0;
  int rank = 0;
  for (char c : initial_fen)
  {
    if (c == '/')
    {
      file = 0;
      rank++;
    }
    else
    {
      if (std::isdigit(c))
        file += (c - '0') * m_CELL_SIZE;
      else
      {
        int x = (m_win_width / 2) - (board_width / 2) + file;
        int y = m_win_height / 2 - m_BOARD_SIZE / 2 + (m_CELL_SIZE)*rank;
        switch (c)
        {
        case 'r':
          render_texture(m_texture, 333 * 4, 333, x, y);
          break;
        case 'b':
          render_texture(m_texture, 333 * 2, 333, x, y);
          break;
        case 'k':
          render_texture(m_texture, 0, 333, x, y);
          break;
        case 'q':
          render_texture(m_texture, 333, 333, x, y);
          break;
        case 'n':
          render_texture(m_texture, 333 * 3, 333, x, y);
          break;
        case 'p':
          render_texture(m_texture, 333 * 5, 333, x, y);
          break;
        case 'R':
          render_texture(m_texture, 333 * 4, 0, x, y);
          break;
        case 'B':
          render_texture(m_texture, 333 * 2, 0, x, y);
          break;
        case 'N':
          render_texture(m_texture, 333 * 3, 0, x, y);
          break;
        case 'P':
          render_texture(m_texture, 333 * 5, 0, x, y);
          break;
        case 'K':
          render_texture(m_texture, 0, 0, x, y);
          break;
        case 'Q':
          render_texture(m_texture, 333, 0, x, y);
          break;
        default:
          break;
        }
        file += m_CELL_SIZE;
      }
    }
  }
}

SDL_Texture *SDL_Handler::load_texture(const char *path)
{
  SDL_Texture *texture = nullptr;
  texture = IMG_LoadTexture(m_renderer, path);
  if (texture == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Unable to load image. ERROR: %s", SDL_GetError());
    return nullptr;
  }
  return texture;
}

#if defined(__APPLE__) || defined(__MACH__)
Uint32 SDL_Handler::m_time_left()
{
  Uint32 now;
  now = SDL_GetTicks();
  if (m_next_time < now)
    return 0;
  else
    return m_next_time - now;
}
#endif

void SDL_Handler::handle_events()
{
#if defined(__APPLE__) ||                                                      \
    defined(__MACH__) // MacOS incompatible with SDL_WaitEvent
  m_next_time = SDL_GetTicks() + 60;
  while (SDL_PollEvent(&m_event))
#else
  while (SDL_WaitEvent(&m_event))
#endif
  {
    switch (m_event.type)
    {
    case SDL_QUIT:
      break;
    case SDL_WINDOWEVENT:
      switch (m_event.window.event)
      {
      case SDL_WINDOWEVENT_RESIZED:
      case SDL_WINDOWEVENT_SIZE_CHANGED:
        m_win_width = m_event.window.data1;
        m_win_height = m_event.window.data2;
        if (m_win_height - m_BOARD_SIZE < 0)
        {
          m_win_height = m_BOARD_SIZE;
        }
        else if (m_win_width - m_BOARD_SIZE < 0)
        {
          m_win_width = m_BOARD_SIZE;
        }
        SDL_SetWindowSize(m_window, m_win_width, m_win_height);
        render_background();
        break;
      }
    default:
      switch (m_event.type)
      {
      case SDL_KEYDOWN:
        if (m_event.key.keysym.sym == SDLK_ESCAPE)
          handling_events = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (m_event.button.button == SDL_BUTTON_LEFT)
          render_background();
        break;
      default:
        break;
      }
#if defined(__APPLE__) || defined(__MACH__)
      SDL_Delay(m_time_left());
#endif
      break;
    }
  }
};

void SDL_Handler::init()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "SDL could not initialize! SDL_Error: %s", SDL_GetError());
    return;
  }

  m_window = SDL_CreateWindow(
      "Chess Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      m_SCREEN_WIDTH, m_SCREEN_HEIGHT,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (m_window == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Window could not be created! SDL_Error: %s", SDL_GetError());
    return;
  }
  m_renderer = SDL_CreateRenderer(
      m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (m_renderer == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Renderer could not be created! SDL_Error: %s",
                 SDL_GetError());
    return;
  }
}
