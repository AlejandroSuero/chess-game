#include "SDL_Handler.h"
#include "FEN.h"
#include <SDL2_image/SDL_image.h>
#include <string>
#include <vector>

SDL_Handler::SDL_Handler()
{
  m_window = nullptr;
  m_renderer = nullptr;
  m_texture = nullptr;
  m_font = nullptr;
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
  if (m_font != nullptr)
    TTF_CloseFont(m_font);
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Handler cleaned up");
  SDL_Quit();
}

SDL_Handler::~SDL_Handler() { clean_up(); }

void SDL_Handler::render_background()

{
  SDL_RenderClear(m_renderer);
  SDL_SetRenderDrawColor(m_renderer, 32, 32, 32, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(m_renderer);
  render_board();
  render_pieces();
  SDL_RenderPresent(m_renderer);
}

void SDL_Handler::render_texture(SDL_Rect src, SDL_Rect dst,
                                 SDL_Texture *texture)
{
  if (texture == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Unable to render texture! ERROR: %s", SDL_GetError());
    return;
  }
  dst.w = dst.h = m_CELL_SIZE;
  SDL_RenderCopy(m_renderer, texture, &src, &dst);
}

void SDL_Handler::render_board()
{
  // keep board on screen no matter the window size
  m_board_width = m_win_width > m_BOARD_SIZE ? m_BOARD_SIZE : m_win_width;
  m_board_height = m_win_height > m_BOARD_SIZE ? m_BOARD_SIZE : m_win_height;
  SDL_Color text_color = {255, 255, 255, 255};
  for (int file = 0; file < 8; file++)
  {
    for (int rank = 0; rank < 8; rank++)
    {
      bool is_white = (file + rank) % 2 == 0;
      if (is_white)
      {
        SDL_SetRenderDrawColor(m_renderer, 236, 210, 183, SDL_ALPHA_OPAQUE);
        text_color = {159, 106, 91, SDL_ALPHA_OPAQUE};
      }
      else
      {
        SDL_SetRenderDrawColor(m_renderer, 159, 106, 91, SDL_ALPHA_OPAQUE);
        text_color = {236, 210, 183, SDL_ALPHA_OPAQUE};
      }
      SDL_Rect rect;

#pragma region draw squares
      int offset_x = (m_win_width / 2) - (m_board_width / 2);
      int offset_y = (m_win_height / 2) - (m_board_height / 2);
      int x = offset_x + (m_CELL_SIZE)*rank;
      int y = offset_y + (m_CELL_SIZE)*file;
      rect.x = x;
      rect.y = y;
      rect.w = rect.h = m_CELL_SIZE;
      SDL_RenderFillRect(m_renderer, &rect);
#pragma endregion
      render_numbers(rank, file, y, x, text_color);
    }
  }
}

void SDL_Handler::render_numbers(int rank, int file, int y, int x,
                                 SDL_Color text_color)
{
  char *text = new char[1];
  if (rank == 0)
  {
    text[0] = '8' - file;
    m_surface = TTF_RenderText_Blended(m_font, text, text_color);
    SDL_Texture *text_texture =
        SDL_CreateTextureFromSurface(m_renderer, m_surface);
    SDL_Rect text_rect;
    // place text in the bottom left corner of the cell
    text_rect.x = x;
    text_rect.y = y;
    text_rect.w = m_surface->w;
    text_rect.h = m_surface->h;
    SDL_RenderCopy(m_renderer, text_texture, nullptr, &text_rect);
  }
  if (file == 7)
  {
    // render 'a' through 'h' on the bottom left corner of the cell
    text[0] = 'a' + rank;
    m_surface = TTF_RenderText_Blended(m_font, text, text_color);
    SDL_Texture *text_texture =
        SDL_CreateTextureFromSurface(m_renderer, m_surface);
    SDL_Rect text_rect;
    // place text in the bottom left corner of the cell
    text_rect.x = x + m_CELL_SIZE - m_surface->w;
    text_rect.y = y + m_CELL_SIZE - m_surface->h;
    text_rect.w = m_surface->w;
    text_rect.h = m_surface->h;
    SDL_RenderCopy(m_renderer, text_texture, nullptr, &text_rect);
  }
  delete[] text;
}

void SDL_Handler::render_pieces()
{
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
        int x = (m_win_width / 2) - (m_board_width / 2) + file;
        int y = m_win_height / 2 - m_BOARD_SIZE / 2 + (m_CELL_SIZE)*rank;
        SDL_Rect src;
        SDL_Rect dst;
        switch (c)
        {
        case 'r':
          src.x = m_PIECE_SIZE * 4;
          src.y = m_PIECE_SIZE;
          src.w = src.h = m_PIECE_SIZE;
          break;
        case 'b':
          src.x = m_PIECE_SIZE * 2;
          src.y = m_PIECE_SIZE;
          src.w = src.h = m_PIECE_SIZE;
          break;
        case 'k':
          src.x = 0;
          src.y = m_PIECE_SIZE;
          src.w = src.h = m_PIECE_SIZE;
          break;
        case 'q':
          src.x = m_PIECE_SIZE;
          src.y = m_PIECE_SIZE;
          src.w = src.h = m_PIECE_SIZE;
          break;
        case 'n':
          src.x = m_PIECE_SIZE * 3;
          src.y = m_PIECE_SIZE;
          src.w = src.h = m_PIECE_SIZE;
          break;
        case 'p':
          src.x = m_PIECE_SIZE * 5;
          src.y = m_PIECE_SIZE;
          src.w = src.h = m_PIECE_SIZE;
          break;
        case 'R':
          src.x = m_PIECE_SIZE * 4;
          src.y = 0;
          src.w = src.h = m_PIECE_SIZE;
          break;
        case 'B':
          src.x = m_PIECE_SIZE * 2;
          src.y = 0;
          src.w = src.h = m_PIECE_SIZE;
          break;
        case 'N':
          src.x = m_PIECE_SIZE * 3;
          src.y = 0;
          src.w = src.h = m_PIECE_SIZE;
          break;
        case 'P':
          src.x = m_PIECE_SIZE * 5;
          src.y = 0;
          src.w = src.h = m_PIECE_SIZE;
          break;
        case 'K':
          src.x = 0;
          src.y = 0;
          src.w = src.h = m_PIECE_SIZE;
          break;
        case 'Q':
          src.x = m_PIECE_SIZE;
          src.y = 0;
          src.w = src.h = m_PIECE_SIZE;
          break;
        default:
          break;
        }
        file += m_CELL_SIZE;
        dst.x = x;
        dst.y = y;
        dst.w = dst.h = m_CELL_SIZE;
        render_texture(src, dst, m_texture);
      }
    }
  }
};

SDL_Texture *SDL_Handler::load_texture(const char *path)
{
  SDL_Surface *image = nullptr;
  image = IMG_Load(path);
  if (image == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Unable to load image. ERROR: %s", SDL_GetError());
    return nullptr;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, image);
  if (texture == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Unable to create texture. ERROR: %s", SDL_GetError());
    return nullptr;
  }
  return texture;
}

TTF_Font *SDL_Handler::load_font(const char *path)
{
  TTF_Font *font = TTF_OpenFont(path, 16);
  if (font == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load font. ERROR: %s",
                 TTF_GetError());
    return nullptr;
  }
  return font;
};

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
  m_texture = load_texture(PIECES_PATH);
  if (m_texture == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Unable to load texture! ERROR: %s", SDL_GetError());
    return;
  }
  if (TTF_Init() == -1)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load font! ERROR: %s",
                 TTF_GetError());
    return;
  }
  m_font = load_font(FONT_PATH);
  if (m_font == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load font! ERROR: %s",
                 TTF_GetError());
    return;
  }
}
