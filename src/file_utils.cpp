//
// Created by stach on 16.06.22.
//

#include "file_utils.h"
#include <fstream>
#include <sstream>


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