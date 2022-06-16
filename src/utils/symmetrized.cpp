//
// Created by stach on 16.06.22.
//

#include "symmetrized.h"
#include<numeric>
#include <algorithm>
#include "utils.h"

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
bool is_last_division(std::vector<int> division){
    if(division.size() <= 1){
        return true;
    }
    if(division.front() - division.back() > 1)
        return false;
    return true;
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

std::vector<int> first_response(int A, int n, int max_value){
    int first_value = max_value + 1;
    std::vector<int> response = std::vector<int>(n, 0);
    int i = 0;
    while(A >= first_value){
        response.at(i) = first_value;
        A -= first_value;
        i++;
    }
    response.at(i) = A;
    return response;
}