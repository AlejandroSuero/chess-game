#include <string>
#include <vector>

namespace FEN
{
std::vector<std::string> parse(const std::string &fen);
std::vector<std::string> get_initial_positions();
std::string get_positions(const std::vector<std::string> &positions);
}; // namespace FEN
