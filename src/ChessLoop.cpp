#include "ChessLoop.h"

void ChessLoop::run()
{
  if (!m_handler.init())
    return;
  bool quit = false;
  while (!quit)
  {
    while (SDL_PollEvent(&m_handler.m_event))
    {
      switch (m_handler.m_event.type)
      {
      case SDL_QUIT:
        quit = true;
        break;
      default:
        switch (m_handler.m_event.type)
        {
        case SDL_KEYDOWN:
          if (m_handler.m_event.key.keysym.sym == SDLK_ESCAPE)
            quit = true;
          break;
        default:
          break;
        }
        break;
      }
    }
    m_handler.render_background();
  }
};
