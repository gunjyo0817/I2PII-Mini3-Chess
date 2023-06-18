#include <cstdlib>
#include "../state/state.hpp"
#include "./minimax.hpp"
using namespace std;

/**
 * @brief
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */
Move Minimax::get_move(State *state, int depth) {
  if (!state->legal_actions.size()) state->get_legal_actions();
  if (depth == 0 || state->legal_actions.empty()) return state->legal_actions[0];

  if (state->player) { // maximize
    int best_score = -1000000;
    Move best_move;
    for(auto action : state->legal_actions){
      auto next_state = state->next_state(action);
      auto score = get_minimax_score(next_state, depth-1);
      if (score >= best_score) {
        best_score = score;
        best_move = action;
      }
    }
    return best_move;
  } 
  else { // minimize
    int worst_score = 1000000;
    Move worst_move;
    for(auto action : state->legal_actions){
      auto next_state = state->next_state(action);
      auto score = get_minimax_score(next_state, depth-1); 
      if (score <= worst_score) {
        worst_score = score;
        worst_move = action;
      }
    }
    return worst_move;
  }
}

int Minimax::get_minimax_score(State *state, int depth) {
  if (depth == 0 || state->legal_actions.empty()) return state->evaluate();
  if (state->player){ // maximize
    int best_score = -1000000;
    for (auto action : state->legal_actions) {
      auto next_state = state->next_state(action);
      best_score = max(best_score, get_minimax_score(next_state, depth-1));
    }
    return best_score;
  }
  else { // minimize
    int worst_score = 1000000;
    for (auto action : state->legal_actions){
      auto next_state = state->next_state(action);
      worst_score = min(worst_score, get_minimax_score(next_state, depth-1));
    }
    return worst_score;
  }
}

