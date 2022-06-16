//
// Created by stach on 16.06.22.
//

#include "experiment.h"
#include "algorithm/algorithm.h"
#include "file_utils.h"
static string TIME_PATH = "../times/";
static string SUPPORT_SIZE_PATH = "../support_sizes/";


void run_experiment(int A, int B, int n){
    auto start = chrono::steady_clock::now();
    Game g = algorithm(A, B, n);
    auto end = chrono::steady_clock::now();
    int support_size = g.get_row_support_size();
    int time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    save_time_to_file(time, A, B, n, TIME_PATH);
    save_support_size_to_file(support_size, A, B, n, SUPPORT_SIZE_PATH);
}