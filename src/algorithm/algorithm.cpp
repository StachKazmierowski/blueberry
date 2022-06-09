//
// Created by stach on 09.06.22.
//

#include "algorithm.h"

Game algorithm(int A, int B, int n){
    PureStrategy row_starting_strategy = PureStrategy(starting_division(A, n));
    PureStrategy col_starting_strategy = PureStrategy(starting_division(B, n));

    MixedStrategy row_starting_mixed_strategy = MixedStrategy(vector<PureStrategy>{row_starting_strategy}, vector<double>{1});
    MixedStrategy col_starting_mixed_strategy = MixedStrategy(vector<PureStrategy>{col_starting_strategy}, vector<double>{1});

    Game game = Game(row_starting_mixed_strategy, col_starting_mixed_strategy, A, B, n);

    while(true){
        PureStrategy best_row_response = game.best_row_response();
        PureStrategy best_col_response = game.best_col_response();
        if(game.contains_row_strategy(best_row_response) and game.contains_col_strategy(best_col_response)){
            break;
        }
        game.update_optimal_strategies(best_row_response, best_col_response);
    }
    return game;
}