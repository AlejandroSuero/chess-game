#include "FEN.h"

std::vector<std::string> FEN::parse(const std::string &fen)
{
  std::vector<std::string> pieces;
  int pos = 0;
  for (int i = 0; i <= fen.size(); i++)
  {
    if (fen[i] == ' ')
    {
      pieces.push_back(fen.substr(pos, i - pos));
      pos = i + 1;
    }
  }
  pieces.push_back(fen.substr(pos, fen.size() - pos));
  return pieces;
}

std::vector<std::string> FEN::get_initial_positions()
{
  std::vector<std::string> initial_positions;
  std::string initial_position =
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  initial_positions = parse(initial_position);
  return initial_positions;
}

std::string FEN::get_positions(const std::vector<std::string> &positions)
{
  return positions[0];
}
