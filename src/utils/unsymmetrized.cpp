//
// Created by stach on 16.06.22.
//

#include "unsymmetrized.h"
#include<numeric>
#include <algorithm>

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
