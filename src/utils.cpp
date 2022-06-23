//
// Created by stach on 06.06.22.
//

#include "utils.h"
#include<vector>
#include<numeric>
#include <algorithm>
#include <assert.h>

bool is_last_division(std::vector<int> division){
    if(division.size() <= 1){
        return true;
    }
    if(division.front() - division.back() > 1)
        return false;
    return true;
}


std::vector<int> next_division(std::vector<int> division){
    if(division.size() == 1)
        return division;

    if(is_last_division(division)) //What should we do here?
        return division;

    std::vector<int> result;

    if(is_last_division(std::vector<int>(division.end() - division.size() + 1, division.end()))){
        result = std::vector<int>(division.size(), 0);
        result.at(0) = division.at(0) - 1;
        int sum = std::accumulate(division.begin(), division.end(), 0) - result.at(0);
        int i = 1;
        while(sum > 0 ){
            result.at(i) = std::min(result.at(i-1), sum);
            sum -= result.at(i);
            i++;
        }
    } else {
        result = next_division(std::vector<int>(division.end() - division.size() + 1 , division.end()));
        result.insert(result.begin(), division.at(0));
    }
    return result;
}

std::vector<std::vector<int>> all_divisions(int A, int n){
    std::vector<int> division = first_division(A, n);
    std::vector<std::vector<int>> divisions = std::vector<std::vector<int>>{};
    divisions.push_back(division);
    while(!is_last_division(divisions.back())) {
        divisions.push_back(next_division(divisions.back()));
    }
    return divisions;
}

std::vector<int> starting_division(int A, int n){
    int rest = A - n * (A/n);
    std::vector<int> division = std::vector<int>(n, A/n);
    for (int i = 0; i < rest; i++){
        division.at(i) += 1;
    }
    return division;
}

std::vector<int> first_division(int A, int n){
    std::vector<int> division = std::vector<int>(n, 0);
    division.at(0) = A;
    return division;
}

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

void assert_probabilities(std::vector<double> probabilities){
    double sum = 0;
    for(double element : probabilities){
        assert(element >= 0);
        sum += element;
    }
    assert(0.99999 < sum and sum < 1.00001);
}
