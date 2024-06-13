#pragma once

#include "SDL_Handler.h"
#include <SDL.h>

class ChessLoop
{
public:
  void run();

public:
  SDL_Handler m_handler;
};
