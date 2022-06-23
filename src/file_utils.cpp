//
// Created by stach on 16.06.22.
//

#include "file_utils.h"
#include <fstream>
#include <sstream>
#include "algorithm/game.h"


void save_time_to_file(long int miliseconds, int A, int B, int n, std::string path){
    std::ofstream my_file;
    std::stringstream ss;
    ss << path << "time(" << A << "," << B << "," << n << ").txt";
    my_file.open (ss.str());
    ss.clear();
    my_file << miliseconds << "\n";
    my_file.close();
}

void save_support_size_to_file(long int size, int A, int B, int n, std::string path){
    std::ofstream my_file;
    std::stringstream ss;
    ss << path << "support_size(" << A << "," << B << "," << n << ").txt";
    my_file.open (ss.str());
    ss.clear();
    my_file << size << "\n";
    my_file.close();
}

void save_max_values_to_file(Game g, std::string path){
    int A = g.get_A();
    int B = g.get_B();
    int n = g.get_n();
    std::ofstream my_file;
    std::stringstream s1;
    s1 << path << "max_value_A(" << A << "," << B << "," << n << ").txt";
    my_file.open (s1.str());
    s1.clear();
    my_file << g.get_col_strategy().get_max_value() << "\n";
    my_file.close();

    std::stringstream s2;
    s2 << path << "max_value_B(" << A << "," << B << "," << n << ").txt";
    my_file.open (s2.str());
    s2.clear();
    my_file << g.get_row_strategy().get_max_value() << "\n";
    my_file.close();
}

void save_optimal_strategies_to_file(Game g, std::string path){
    int A = g.get_A();
    int B = g.get_B();
    int n = g.get_n();
    std::ofstream my_file;
    std::stringstream s1;
    s1 << path << "optimal_strategy_A(" << A << "," << B << "," << n << ").txt";
    my_file.open (s1.str());
    for(int i = 0; i < g.get_row_strategy().get_size(); i++){
        vector<int> division = g.get_row_strategy().get_strategies().at(i).get_division();
        my_file << vector_to_string(division) << ": " << g.get_row_strategy().get_probabilities().at(i) << "\n";
    }
    my_file.close();

    std::stringstream s2;
    s2 << path << "optimal_strategy_B(" << A << "," << B << "," << n << ").txt";
    my_file.open (s2.str());
    s2.clear();
    for(int i = 0; i < g.get_col_strategy().get_size(); i++){
        vector<int> division = g.get_col_strategy().get_strategies().at(i).get_division();
        my_file << vector_to_string(division) << ": " << g.get_col_strategy().get_probabilities().at(i) << "\n";
    }
    my_file.close();
}

std::string vector_to_string(vector<int> vec) {
    std::stringstream ss;
    ss << "[";
    for (auto it = vec.begin(); it != vec.end(); it++) {
        if (it != vec.begin() and it != vec.end()) {
            ss << ", ";
        }
        ss << *it;
    }
    ss << "]";
    return ss.str();
}
