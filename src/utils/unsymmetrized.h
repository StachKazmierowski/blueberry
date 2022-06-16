//
// Created by stach on 16.06.22.
//

#ifndef DOUBLEORACLEALGORITHM_UNSYMMETRIZED_H
#define DOUBLEORACLEALGORITHM_UNSYMMETRIZED_H
#include "vector"

std::vector<int> next_partition(std::vector<int> division);

bool is_last_partition(std::vector<int> partition);

std::vector<std::vector<int>> all_divisions(int A, int n);

std::vector<int> first_partition(int A, int n);

std::vector<std::vector<int>> all_partitions(int A, int n);


#endif //DOUBLEORACLEALGORITHM_UNSYMMETRIZED_H
