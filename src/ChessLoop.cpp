#include "ChessLoop.h"
#include "SDL_Handler.h"

void Chess::Run()
{
  SDL_Handler handler;
  while (handler.handling_events)
  {
    handler.handle_events();
  }
};
