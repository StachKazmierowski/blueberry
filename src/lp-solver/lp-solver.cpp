//
// Created by stach on 03.06.22.
//
#include "lp-solver.h"
#include "gurobi_c++.h"
#include "string"
#include <assert.h>
#include "utils.h"

static double MAX_VALUE = 1;
static double MIN_VALUE = -1;

std::vector<double> solve_game(std::vector<std::vector<double>> payoff_matrix){
    // We take row player matrix as an input
    // payoff matrix is a vector of rows
    int cols_number = payoff_matrix.at(0).size();
    std::vector<std::string> names = {};
    for(int i = 0; i < cols_number; i++){
        names.push_back("x_" + std::to_string(i));
    }

    try {
        GRBEnv env = GRBEnv();

        GRBModel model = GRBModel(env);


        std::vector<GRBVar> variables = {};
        for (std::string name : names)
            // Create variables in [0;1]
            variables.push_back(model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, name));

        // Adding game value
        GRBVar game_value = model.addVar(MIN_VALUE, MAX_VALUE, 0.0, GRB_CONTINUOUS, "game_value");

        std::vector<double> ones(cols_number, 1);
        GRBLinExpr expr = 0;
        expr.addTerms(ones.data(), variables.data(), cols_number);
        model.addConstr(expr == 1);

        for (std::vector<double> row : payoff_matrix){
            GRBLinExpr expr = 0;
            expr.addTerms(row.data(), variables.data(), cols_number);
            model.addConstr(expr <= game_value);
        }


        model.setObjective(1 * game_value, GRB_MINIMIZE);


        model.optimize();

        std::vector<double> col_optimal_strategy = {};
        for (GRBVar var : variables){
            col_optimal_strategy.push_back(var.get(GRB_DoubleAttr_X));
        }
        assert_probabilities(col_optimal_strategy);
        return col_optimal_strategy;
    } catch(GRBException e) {
        std::cout << "Error code = " << e.getErrorCode() << std::endl;
        std::cout << e.getMessage() << std::endl;
    } catch(...) {
        std::cout << "Exception during optimization" << std::endl;
    }
    return std::vector<double>();
}
