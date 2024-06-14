#include "SDL_Handler.h"
#include <iostream>

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
  std::cout << "Bye!" << std::endl;
  SDL_Quit();
}

SDL_Handler::~SDL_Handler() { clean_up(); }

void SDL_Handler::render_background()

{
  SDL_SetRenderDrawColor(m_renderer, 0, 0xFF, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(m_renderer);
  render_board();
  SDL_RenderPresent(m_renderer);
}

void SDL_Handler::render_board()
{
  // keep board on screen no matter the window size
  int board_width = m_win_width > BOARD_WIDTH ? BOARD_WIDTH : m_win_width;
  int board_height = m_win_height > BOARD_HEIGHT ? BOARD_HEIGHT : m_win_height;
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
      // normalize screen size to 8x8 squares
      int square_size = 0;
      if (board_width / 8 > board_height / 8)
        square_size = board_width / 8;
      else
        square_size = board_height / 8;

#pragma region draw squares
      int offset_x = (m_win_width / 2) - (board_width / 2);
      int offset_y = (m_win_height / 2) - (board_height / 2);
      rect.x = offset_x + (square_size)*file;
      rect.y = offset_y + (square_size)*rank;
      rect.w = square_size;
      rect.h = square_size;
      SDL_RenderFillRect(m_renderer, &rect);
#pragma endregion
    }
  }
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
#if defined(__APPLE__) || defined(__MACH__) // MacOS incompatible with SDL_WaitEvent
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
        if (m_win_height - BOARD_HEIGHT < 0)
        {
          m_win_height = BOARD_HEIGHT;
        }
        else if (m_win_width - BOARD_WIDTH < 0)
        {
          m_win_width = BOARD_WIDTH;
        }
        SDL_SetWindowSize(m_window, m_win_width, m_win_height);
        break;
      }
    default:
      switch (m_event.type)
      {
      case SDL_KEYDOWN:
        if (m_event.key.keysym.sym == SDLK_ESCAPE)
          handling_events = false;
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
  render_background();
};

void SDL_Handler::init()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "SDL could not initialize! SDL_Error:\n"
              << SDL_GetError() << std::endl;
    return;
  }

  m_window = SDL_CreateWindow(
      "Chess Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (m_window == nullptr)
  {
    std::cout << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return;
  }
  m_renderer = SDL_CreateRenderer(
      m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (m_renderer == nullptr)
  {
    std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return;
  }
}
