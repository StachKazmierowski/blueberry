#ifndef HEDGE_CPP_UTILS_H
#define HEDGE_CPP_UTILS_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <chrono>
#include <omp.h>

using namespace std;

vector<vector<int>> clash_matrix(vector<int> s_A, vector<int> s_B);

int sign(int a);

bool check_if_contains(vector<vector<int>> vectors, vector<int> vector);

vector<vector<int>> next_divide(vector<vector<int>> divide);

vector<vector<int>> all_permutations(vector<int> s_A);

vector<vector<int>> divides_strategies(int resources, int fields_number);

long int k_W(vector<int> s_A, vector<int> s_B);

long int k_L(vector<int> s_A, vector<int> s_B);

long int factorial(int n);

int matrix_sum(vector<vector<int>> matrix);

vector<int> find_area_vector(vector<vector<int>> clash_mat, int area);

vector<vector<long int>> empty_matrix(int size);

vector<vector<int>> empty_clash_matrix(int size);

int height_to_cutoff(vector<int> L, vector<int> T, int current_height);

int width_to_cutoff(vector<int> L, vector<int> T, int current_height);

bool has_single_value(vector<int> v);

int same_values_at_tail(vector<int> v);

vector<int> add_vectors(vector<int> a, vector<int> b);

vector<int> trim_vector(vector<int> v, int number_of_elements);

vector<vector<int>> find_knots(vector<int> L, vector<int> T);

long int newton_symbol(int n, int k);

long int single_type_rectangle(int cols_num, int rows_num, int rooks_num);

int min_number_of_rooks(int i, int j, int n);

void number_of_different_clash_matrices(int A, int B, int n, int (*aggregation_function)(int, int, int));

#endif
