#include <cstdlib>
#include "../state/state.hpp"
#include "./submission.hpp"
using namespace std;

/**
 * @brief
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */
Move Minimax::get_move(State* state, int depth, bool isMaximise){
  if(!state->legal_actions.size()) state->get_legal_actions();
  if(depth == 0 || state->legal_actions.empty()) return state->legal_actions[0];

  int best_score = -99999;
  Move best_move;

  int value = 0;
  for(auto action : state->legal_actions){
    auto nextState = state->next_state(action);
    value = get_minimax_score(nextState, depth-1, -100000, 100000, !isMaximise);
    if(value >= best_score){
      best_score = value;
      best_move = action;
    }
  }
  return best_move;
}

int Minimax::get_minimax_score(State* state, int depth, int alpha, int beta, bool isMaximise){
  if(depth == 0 || state->legal_actions.empty()) return state->evaluate();
  int value = 0;
  if(isMaximise){
    int bestMove = -99999;
    for(auto action : state->legal_actions){
      auto next_state = state->next_state(action);
      value = get_minimax_score(next_state, depth-1, alpha, beta, false);
      bestMove = max(bestMove, value);
      alpha = max(alpha, bestMove);
      if(beta <= alpha){
        break;
      }
    }
    return bestMove;
  } 
  else{
    int bestMove = 99999;
    for(auto action : state->legal_actions){
      auto next_state = state->next_state(action);
      value = get_minimax_score(next_state, depth-1, alpha, beta, true);
      bestMove = min(bestMove, value);
      beta = min(beta, bestMove);
      if(beta <= alpha){
        break;
      }
    }
    return bestMove;
  }
}