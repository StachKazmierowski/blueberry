//
// Created by stach on 16.06.22.
//

#ifndef DOUBLEORACLEALGORITHM_FILE_UTILS_H
#define DOUBLEORACLEALGORITHM_FILE_UTILS_H
#include <string>

void save_time_to_file(long int miliseconds, int A, int B, int n, std::string path);

void save_support_size_to_file(long int size, int A, int B, int n, std::string path);
#endif //DOUBLEORACLEALGORITHM_FILE_UTILS_H
