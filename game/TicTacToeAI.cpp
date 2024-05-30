//
// Created by Wiktor on 23.05.2024.
//

#include "TicTacToeAI.h"

using namespace std;

std::string TicTacToeAI::printGameState(int state) {
    if (WIN == state) return "Wygrałeś";
    else if (DRAW == state) return "Remis";
    else if (LOSS == state) return "Komputer wygrał";
    else return "Niepoprawny status";
}

vector<pair<int, int>> TicTacToeAI::getLegalMoves() {
    vector<pair<int, int>> legal_moves;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != AI_MARKER && board[i][j] != PLAYER_MARKER) {
                legal_moves.emplace_back(i, j);
            }
        }
    }

    return legal_moves;
}

bool TicTacToeAI::positionOccupied(pair<int, int> pos) {
    vector<pair<int, int>> legal_moves = this->getLegalMoves();

    for (int i = 0; i < legal_moves.size(); i++) {
        if (pos.first == legal_moves[i].first && pos.second == legal_moves[i].second){
            return false;
        }
    }
    return true;
}

vector<pair<int, int>> TicTacToeAI::getOccupiedPositions(char marker) {
    vector<pair<int, int>> occupied_positions;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (marker == board[i][j]) {
                occupied_positions.emplace_back(i, j);
            }
        }
    }
    return occupied_positions;
}

bool TicTacToeAI::boardIsFull() {
    vector<pair<int, int>> legal_moves = this->getLegalMoves();
    return legal_moves.empty();
}

bool TicTacToeAI::gameIsWon(vector<std::pair<int, int>> occupied_positions) {
    bool game_won;

    for (auto curr_win_state : this->winning_states) {
        game_won = true;
        for (int j = 0; j < 3; j++){
            if (!(find(std::begin(occupied_positions), std::end(occupied_positions), curr_win_state[j]) != std::end(occupied_positions))){
                game_won = false;
                break;
            }
        }
        if (game_won) break;
    }
    return game_won;
}

char TicTacToeAI::getOpponentMarker(char marker) {
    char opponent_marker;
    if (marker == PLAYER_MARKER) {
        opponent_marker = AI_MARKER;
    } else {
        opponent_marker = PLAYER_MARKER;
    }
    return opponent_marker;
}

int TicTacToeAI::getBoardState(char marker) {
    char opponent_marker = TicTacToeAI::getOpponentMarker(marker);
    vector<pair<int, int>> occupied_positions = this->getOccupiedPositions(marker);
    bool is_won = this->gameIsWon(occupied_positions);
    if (is_won) return WIN;
    occupied_positions = this->getOccupiedPositions(opponent_marker);
    bool is_lost = this->gameIsWon(occupied_positions);
    if (is_lost) return LOSS;
    bool is_full = this->boardIsFull();
    if (is_full) return DRAW;
    return DRAW;
}

pair<int, pair<int, int>> TicTacToeAI::minimaxOptimization(char marker, int depth, int alpha, int beta) {
    // Initialize best move
    pair<int, int> best_move = std::make_pair(-1, -1);
    int best_score = (marker == AI_MARKER) ? LOSS : WIN;

    // If we hit a terminal state (leaf node), return the best score and move
    if (this->boardIsFull() || DRAW != this->getBoardState(AI_MARKER)) {
        best_score = this->getBoardState(AI_MARKER);
        return std::make_pair(best_score, best_move);
    }

    std::vector<std::pair<int, int>> legal_moves = this->getLegalMoves();

    for (auto curr_move : legal_moves) {
        board[curr_move.first][curr_move.second] = marker;

        // Maximizing player's turn
        if (marker == AI_MARKER) {
            int score = this->minimaxOptimization(PLAYER_MARKER, depth + 1, alpha, beta).first;
            // Get the best scoring move
            if (best_score < score) {
                best_score = score - depth * 10;
                best_move = curr_move;
                // Check if this branch's best move is worse than the best
                // option of a previously search branch. If it is, skip it
                alpha = std::max(alpha, best_score);
                board[curr_move.first][curr_move.second] = EMPTY_SPACE;
                if (beta <= alpha) break;
            }
        } else {
            int score = this->minimaxOptimization(AI_MARKER, depth + 1, alpha, beta).first;
            if (best_score > score) {
                best_score = score + depth * 10;
                best_move = curr_move;
                // Check if this branch's best move is worse than the best
                // option of a previously search branch. If it is, skip it
                beta = std::min(beta, best_score);
                board[curr_move.first][curr_move.second] = EMPTY_SPACE;
                if (beta <= alpha) break;
            }
        }
        board[curr_move.first][curr_move.second] = EMPTY_SPACE; // Undo move
    }
    return std::make_pair(best_score, best_move);
}

bool TicTacToeAI::gameIsDone() {

    if (this->boardIsFull()) return true;
    if (DRAW != this->getBoardState(AI_MARKER)) return true;
    return false;
}

TicTacToeAI::TicTacToeAI(char (&grid)[3][3]) : board(grid) {}
