//
// Created by stach on 16.06.22.
//
#include "utils.h"
#include "unsymmetrized.h"
#include<numeric>
#include <algorithm>
#include "assert.h"

std::vector<int> next_partition(std::vector<int> partition){
    if(is_last_partition(partition))
        return partition;
    std::vector<int> result;
    if(is_last_partition(std::vector<int>(partition.end() - partition.size() + 1, partition.end()))){
        result = std::vector<int>(partition.size(), 0);
        result.at(0) = partition.at(0) - 1;
        result.at(1) = std::accumulate(partition.begin(), partition.end(), 0) - result.at(0);
    } else {
        result = next_partition(std::vector<int>(partition.end() - partition.size() + 1 , partition.end()));
        result.insert(result.begin(), partition.at(0));
    }
    return result;
}


bool is_last_partition(std::vector<int> partition){
    return std::accumulate(partition.begin(), partition.end(), 0) == partition.at(partition.size() - 1);
}

std::vector<std::vector<int>> all_partitions(int A, int n){
    std::vector<int> partition = first_partition(A, n);
    std::vector<std::vector<int>> partitions = std::vector<std::vector<int>>{};
    partitions.push_back(partition);
    while(!is_last_partition(partitions.back())) {
        partitions.push_back(next_partition(partitions.back()));
    }
    return partitions;
}


std::vector<int> first_partition(int A, int n){
    std::vector<int> division = std::vector<int>(n, 0);
    division.at(0) = A;
    return division;
}

std::vector<int> smallest_vector(const std::vector<int> constraits, int sum){
    assert(std::accumulate(constraits.begin(), constraits.end(), 0) >= sum);
    std::vector<int> result = std::vector<int>(constraits.size(), 0);
    int i = result.size() - 1;
    while(i >= 0 and sum > 0){
        result.at(i) = std::min(constraits.at(i), sum);
        sum -= result.at(i);
        i--;
    }
    return result;
}

std::vector<int> biggest_vector(const std::vector<int> constraits, int sum){
    assert(std::accumulate(constraits.begin(), constraits.end(), 0) >= sum);
    std::vector<int> result = std::vector<int>(constraits.size(), 0);
    int i = 0;
    while(i < constraits.size() and sum > 0){
        result.at(i) = std::min(constraits.at(i), sum);
        sum -= result.at(i);
        i++;
    }
    return result;
}

bool is_lex_smaller(const std::vector<int> first, const std::vector<int> second){
    assert(first.size() == second.size());
    for(int i = 0; i < first.size(); i++){
        if(first.at(i) > second.at(i))
            return false;
    }
    return true;
}

bool next_vector_exists(std::vector<int> partition, std::vector<int> constraints){
    int sum = std::accumulate(partition.begin(), partition.end(), 0);
    return is_lex_smaller(smallest_vector(constraints, sum), partition);
}

std::vector<int> next_partition(std::vector<int> partition, std::vector<int> constraints){
    assert(partition.size() == constraints.size());
    if(partition.size() == 1)
        return partition;
    if(!next_vector_exists(partition, constraints)){
        return partition;
    }
    std::vector<int> result;
    if(next_vector_exists(remove_first(partition), remove_first(constraints))){
        result = next_partition(remove_first(partition), remove_first(constraints));
        result.insert(result.begin(), partition.at(0));
    }
    else{
        int sum = std::accumulate(partition.begin(), partition.end(), 0);
        result = biggest_vector(remove_first(constraints), sum - partition.at(0) - 1);
        result.insert(result.begin(), partition.at(0) - 1);
    }
    return result;
}
