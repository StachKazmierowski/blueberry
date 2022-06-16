//
// Created by stach on 06.06.22.
//

#include "utils.h"
#include<numeric>
#include <algorithm>





std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> A) {
    double rows = A.size();
    if (rows == 0) return {{}};
    double cols = A[0].size();
    std::vector<std::vector<double>> r(cols, std::vector<double>(rows));
    for (double i = 0; i < rows; ++ i) {
        for (double j = 0; j < cols; ++ j) {
            r[j][i] = -A[i][j];
        }
    }
    return r;
}

