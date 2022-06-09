//
// Created by stach on 06.06.22.
//

#ifndef GUROBI_TEMPLATE_UTILS_H
#define GUROBI_TEMPLATE_UTILS_H
#include<vector>

std::vector<int> next_division(std::vector<int> division);

std::vector<std::vector<int>> all_divisions(int A, int n);

bool is_last_division(std::vector<int> division);

std::vector<int> starting_division(int A, int n);

std::vector<int> first_division(int A, int n);

std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> A);

#endif //GUROBI_TEMPLATE_UTILS_H
