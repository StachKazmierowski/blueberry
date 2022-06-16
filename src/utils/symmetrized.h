//
// Created by stach on 16.06.22.
//

#ifndef DOUBLEORACLEALGORITHM_SYMMETRIZED_H
#define DOUBLEORACLEALGORITHM_SYMMETRIZED_H

#include<vector>

bool is_last_division(std::vector<int> division);

std::vector<int> starting_division(int A, int n);

std::vector<int> first_response(int A, int n, int max_value);

std::vector<int> first_division(int A, int n);

std::vector<int> next_division(std::vector<int> division);

#endif //DOUBLEORACLEALGORITHM_SYMMETRIZED_H
