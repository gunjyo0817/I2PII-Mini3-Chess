#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy,
 * your policy class should have get_move method
 */
class Minimax{
public:
  static Move get_move(State *state, int depth , bool isMaximise);
  static int get_minimax_score(State *state, int depth, int alpha, int beta, bool isMaximise);
};
