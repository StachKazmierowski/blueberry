#include "chop_utils.h"

int sign(int a){
    if(a > 0)
        return 1;
    if(a == 0)
        return 0;
    return -1;
}

vector<vector<long int>> empty_matrix(int size){
    vector<vector<long int>> values;
    for(int i = 0 ; i < size; i++){
        vector<long int> row;
        for(int j = 0; j < size; j++){
            row.push_back(0);
        }
        values.push_back(row);
    }
    return values;
}

vector<vector<int>> empty_clash_matrix(int size){
    vector<vector<int>> values;
    for(int i = 0 ; i < size; i++){
        vector<int> row;
        for(int j = 0; j < size; j++){
            row.push_back(0);
        }
        values.push_back(row);
    }
    return values;
}

vector<vector<int>> clash_matrix(vector<int> s_A, vector<int> s_B){
    int fields_number = s_A.size();
    vector<vector<int>> clash_matrix;
    clash_matrix = empty_clash_matrix(fields_number);
    for(int i = 0; i < fields_number; i++){
        for(int j = 0; j < fields_number; j++){
            clash_matrix.at(i).at(j) = sign(s_A.at(j) - s_B.at(i));
        }
    }
    return clash_matrix;
}

void print_matrix(vector<vector<int>> matrix){
    cout << "====================" << endl;
    int rows_number = matrix.size();
    int columns_number = matrix.at(0).size();
    for(int i = 0; i < rows_number; i++){
        for(int j = 0; j < columns_number; j++){
            cout << matrix.at(i).at(j) << ",";
        }
        cout << endl;
    }
}

void print_matrix(vector<vector<double>> matrix){
    cout << "====================" << endl;
    int rows_number = matrix.size();
    int columns_number = matrix.at(0).size();
    for(int i = 0; i < rows_number; i++){
        for(int j = 0; j < columns_number; j++){
            cout << matrix.at(i).at(j) << ",";
        }
        cout << endl;
    }
}

void print_vector(vector<int> v){
//    cout << "====================" << endl;
    for(int i = 0; i < v.size() ; i++){
        cout << v.at(i) << ",";
    }
    cout << endl;
}

bool check_if_contains(vector<vector<int>> vectors, vector<int> vector){
    if(find(vectors.begin(), vectors.end(), vector) != vectors.end()) {
        return true;
    } else {
        return false;
    }
}

vector<vector<int>> next_divide(vector<vector<int>> divide){
    int fields_number = divide.at(0).size();
    int div_num = divide.size();
    vector<vector<int>> new_divides;
    for(int i =0; i < div_num; i++){
        vector<int> curr_divide = divide.at(i);
        for(int j = 0; j < fields_number; j++){
            if (j == 0 || curr_divide.at(j) < curr_divide.at(j-1)){
                vector<int> new_divide;
                new_divide = curr_divide;
                new_divide[j]++;
                if(!check_if_contains(new_divides, new_divide))
                    new_divides.push_back(new_divide);
            }
        }
    }
    return new_divides;
}

vector<vector<int>> divides_strategies(int resources, int fields_number){
    vector<vector<int>> divides_result;
    vector<int> first_divide;
    for(int i = 0 ; i < fields_number; i++)
        first_divide.push_back(0);
    divides_result.push_back(first_divide);
    for(int i = 0 ; i < resources; i++){
        divides_result = next_divide(divides_result);
    }
    reverse(divides_result.begin(), divides_result.end());
    return divides_result;
}

vector<vector<int>> all_permutations(vector<int> s_A){
    reverse(s_A.begin(), s_A.end());
    vector<vector<int>> result;
    do {
        result.push_back(s_A);
    } while (next_permutation(s_A.begin(), s_A.end()));
    return result;
}

long int k_W(vector<int> s_A, vector<int> s_B){
    long int k_W = 0;
    for (int i = 0; i < s_A.size(); i++){
        if(s_A.at(i) > s_B.at(i))
            k_W++;
    }
    return k_W;
}

long int k_L(vector<int> s_A, vector<int> s_B){
    long int k_L = 0;
    for (int i = 0; i < s_A.size(); i++){
        if(s_A.at(i) < s_B.at(i))
            k_L++;
    }
    return k_L;
}

long int factorial(int n){
    if(n < 0)
        return 0;
    if(n == 0 || n == 1)
        return 1;
    return n* factorial(n-1);
}

long int matrix_sum(vector<vector<long int>> matrix){
    long int sum = 0;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.at(0).size(); j++){
            sum += matrix.at(i).at(j);
        }
    }
    return sum;
}

vector<vector<long int>> h(vector<int> s_A, vector<int> s_B){
    int fields_number = s_A.size();
    vector<vector<long int>> values;
    values = empty_matrix(fields_number + 1);
    vector<vector<int>> permutations;
    permutations = all_permutations(s_A);
    for (int i = 0; i < permutations.size(); i++){
        vector<int> permutation = permutations.at(i);
        long int kW = k_W(permutation, s_B);
        long int kL = k_L(permutation, s_B);
        values.at(kW).at(kL)++;
    }
    long int scale = (long int)(factorial(fields_number) / matrix_sum(values));
    for(int i = 0; i < values.size(); i++){
        for(int j = 0; j < values.at(0).size(); j++){
            values.at(i).at(j) *= scale;
        }
    }
    return values;
}

vector<int> find_area_vector(vector<vector<int>> clash_mat, int area){
    vector<int> L;
    int fields_number = clash_mat.size();
    for (int i = 0; i < fields_number ; i++){
        int cells_in_L = 0;
        for (int j = 0; j < fields_number ; j++){
            if(clash_mat.at(j).at(i) == area)
                cells_in_L++;
        }
        L.push_back(cells_in_L);
    }
    return L;
}

bool has_single_value(vector<int> v){
    if(set<int>(v.begin(), v.end()).size() == 1)
        return true;
    return false;
}

int number_of_same_values_at_tail(vector<int> v){
    int width = 0;
    for (int i = v.size() - 1; i >= 0; i--){
        if(v.at(i) == v.back())
            width++;
        else
            break;
    }
    return width;
}

int height_to_cutoff(vector<int> L, vector<int> T, int current_height){
    if(L.back() + T.back() < current_height)
        return current_height - (L.back() + T.back());
    if(L.back() == current_height)
        return 0;
    if(T.back() > 0){
        if (has_single_value(T) && has_single_value(L))
            return T.back();
        else if (has_single_value(L) && L.back() == 0 && T.at(0) < current_height)
            return 0;
        else
            return T.back();
    }
    cerr << ("height_to_cutoff FUNCTION FAILED TO RETURN VALUES") << endl;
    return -1;
}

vector<int> add_vectors(vector<int> a, vector<int> b){
    vector<int> result;
    for (int i = 0; i < a.size(); i++){
        result.push_back(a.at(i) + b.at(i));
    }
    return result;
}

int width_to_cutoff(vector<int> L, vector<int> T, int current_height){
    if(L.back() + T.back() < current_height)
        return 0;
    if(L.back() == current_height)
        return number_of_same_values_at_tail(L);
    if(T.back() > 0){
        if (has_single_value(T) && has_single_value(L))
            return 0;
        else if (has_single_value(L) && L.back() == 0 && T.at(0) < current_height)
            return number_of_same_values_at_tail(T);
        else
            return min(number_of_same_values_at_tail(L), number_of_same_values_at_tail(add_vectors(L, T)));
    }
    cerr << ("height_to_cutoff FUNCTION FAILED TO RETURN VALUES") << endl;
    return -1;
}

vector<int> trim_vector(vector<int> v, int number_of_elements){
    vector<int> result;
    for (int i = 0; i < number_of_elements; i++){
        result.push_back(v.at(i));
    }
    return result;
}

vector<vector<int>> find_knots(vector<int> L, vector<int> T){ //TODO następny krok
    int fields_number = L.size();
    int i = fields_number;
    int j = fields_number;
    int current_height = fields_number;
    vector<vector<int>> knots;
    vector<int> knot;
    knot.push_back(i);
    knot.push_back(j);
    knots.push_back(knot);
    while (L.size() > 0){
        int height_to_remove = height_to_cutoff(L, T, current_height);
        int width_to_remove = width_to_cutoff(L, T, current_height);
        i -= height_to_remove;
        j -= width_to_remove;
        current_height -= height_to_remove;
        if(width_to_remove > 0){
            L = trim_vector(L, j);
            T = trim_vector(T, j);
        }
        if(i > 0 && j > 0){
            vector<int> knot;
            knot.push_back(i);
            knot.push_back(j);
            knots.push_back(knot);
        } else {
            break;
        }
    }
    reverse(knots.begin(), knots.end());
    return knots;
}

long int newton_symbol(int n, int k){
    if(n < 0 || k < 0 || k > n)
        return 0;
    return int(factorial(n) / (factorial(n - k) * factorial(k)));
}

long int single_type_rectangle(int cols_num, int rows_num, int rooks_num){
    if(cols_num < 0 or rows_num < 0 or rooks_num < 0)
        return 0;
    if(rooks_num > cols_num or rooks_num > rows_num)
        return 0;
    return newton_symbol(rows_num, rooks_num) * newton_symbol(cols_num, rooks_num) * factorial(rooks_num);
}

int min_number_of_rooks(int i, int j, int n){
    int delta_i = n - i;
    int delta_j = n - j;
    int r_1 = min(delta_i, j);
    int r_3 = min(i, delta_j);
    int r_2 = min(delta_i - r_1, delta_j - r_3);
    return n - (r_1 + r_2 + r_3);
}

