//
// Created by stach on 06.06.22.
//

#ifndef DOUBLEORACLEALGORITHM_GAME_H
#define DOUBLEORACLEALGORITHM_GAME_H
#include "mixedStrategy.h"
#include "utils.h"
#include "lp-solver/lp-solver.h"
#include "oracle.h"
#include <assert.h>

class Game {
protected:
    int A, B, n;
    MixedStrategy row_optimal_strategy;
    MixedStrategy col_optimal_strategy;
public:
    Game(MixedStrategy rowOptimalStrategy, MixedStrategy colOptimalStrategy, int A, int B, int n)
            : col_optimal_strategy(colOptimalStrategy), row_optimal_strategy(rowOptimalStrategy) {
        this->A = A;
        this->B = B;
        this->n = n;
    }

    void update_optimal_strategies(PureStrategy new_row_strategy, PureStrategy new_col_strategy) {
        this->row_optimal_strategy.append_strategy(new_row_strategy);
        this->col_optimal_strategy.append_strategy(new_col_strategy);

        vector<double> row_probabilities = solve_game(row_player_payoff_matrix());
        vector<double> col_probabilities = solve_game(col_player_payoff_matrix());

        this->row_optimal_strategy.set_probabilities(row_probabilities);
        this->col_optimal_strategy.set_probabilities(col_probabilities);
    }

    std::vector<std::vector<double>> row_player_payoff_matrix(){
        std::vector<std::vector<double>> payoff_matrix;
        for (PureStrategy row_strategy : this->row_optimal_strategy.get_strategies()){
            std::vector<double> row;
            for (PureStrategy col_strategy : this->col_optimal_strategy.get_strategies()){
                row.push_back(row_strategy.payoff(col_strategy));
            }
            payoff_matrix.push_back(row);
        }
        return payoff_matrix;
    }

    int get_A(){
        return this->A;
    }

    int get_B(){
        return this->B;
    }

    int get_n(){
        return this->n;
    }

    std::vector<std::vector<double>> col_player_payoff_matrix(){
        return transpose(row_player_payoff_matrix());
    }

    bool contains_row_strategy(PureStrategy pureStrategy){
        return this->row_optimal_strategy.contains(pureStrategy);
    }

    bool contains_col_strategy(PureStrategy pureStrategy){
        return this->col_optimal_strategy.contains(pureStrategy);
    }

    PureStrategy best_row_response(){
        return Oracle::find_best_response(this->col_optimal_strategy,
                                          first_lex_division(A, n, this->col_optimal_strategy.get_max_value() + 1));
    }

    PureStrategy best_col_response(){
        return Oracle::find_best_response(this->row_optimal_strategy,
                                          first_lex_division(B, n, this->row_optimal_strategy.get_max_value() + 1));
    }

    int get_row_support_size(){
        return this->row_optimal_strategy.support_size();
    }

    MixedStrategy get_row_strategy(){
        return this->row_optimal_strategy;
    }

    MixedStrategy get_col_strategy(){
        return this->col_optimal_strategy;
    }
};





#endif //DOUBLEORACLEALGORITHM_GAME_H
