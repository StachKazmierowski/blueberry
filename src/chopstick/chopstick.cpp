#include "chopstick.h"

vector<vector<vector<long int>>> empty_H_chopstick(int knots_number, int fields_number){
    vector<vector<vector<long int>>> values; // knot, rooks_num, value
    for(int i = 0; i < knots_number; i++){
        vector<vector<long int>> values_0;
        for(int j = 0; j < fields_number + 1; j++){
            vector<long int> values_1;
            for(int j = 0; j < 2 * fields_number + 1; j++){
                values_1.push_back(0);
            }
            values_0.push_back(values_1);
        }
        values.push_back(values_0);
    }
    return values;
}

int vector_sum(vector<long int> v){
    int result = 0;
    for(int i = 0 ; i < v.size(); i++)
        result += v.at(i);
    return result;
}

vector<long int> recurrence_H_chopstick(vector<int> s_A, vector<int> s_B){
    int fields_number = s_A.size();
    vector<vector<int>> clash_mat = clash_matrix(s_A, s_B);
    vector<int> L = find_area_vector(clash_mat, -1);
    vector<int> T = find_area_vector(clash_mat, 0);
    vector<vector<int>> knots = find_knots(L, T);
    vector<vector<vector<long int>>> values = empty_H_chopstick(knots.size(), fields_number);
    vector<int> knot = knots.at(0);
    int i = knot.at(0);
    int j = knot.at(1);
    if(L.at(0) > 0){
        for (int num_rooks = 0; num_rooks <= min(i,j); num_rooks++)
            values[0][num_rooks][fields_number - num_rooks] = single_type_rectangle(i, j, num_rooks);
    } else if (T.at(0) > 0){
        for (int num_rooks = 0; num_rooks <= min(i,j); num_rooks++)
            values[0][num_rooks][fields_number] = single_type_rectangle(i, j, num_rooks);
    } else {
        for (int num_rooks = 0; num_rooks <= min(i,j); num_rooks++)
            values[0][num_rooks][fields_number + num_rooks] = single_type_rectangle(i, j, num_rooks);
    }
    for(int knot_index = 1; knot_index < knots.size() - 1; knot_index++){
        knot = knots.at(knot_index);
        i = knot.at(0);
        j = knot.at(1);
        vector<int> previous_knot = knots[knot_index-1];
        int old_i = previous_knot[0];
        int old_j = previous_knot[1];
        int delta_i = i - old_i;
        int delta_j = j - old_j;
        if(knot_index == 1 && L[0] > 0 && T[0] > 0){ // L and T stripes
            int maximum_rooks_in_T = min(delta_i, j);
            for(int num_rooks = 0; num_rooks <= min(i,j); num_rooks++){
                for(int r_T = 0; r_T <= min(maximum_rooks_in_T, num_rooks); r_T++){
                    int rooks_left = num_rooks - r_T;
                    long int H_tmp = values[0][rooks_left][fields_number - rooks_left];
                    long int bottom = single_type_rectangle(delta_i, j - rooks_left, r_T);
                    values[knot_index][num_rooks][fields_number - rooks_left] = H_tmp * bottom;
                }
            }
        } else if (knot_index == 1 && T[0] == 0 && T[j-1] > 0 && L[0] == 0 && has_single_value(trim_vector(L, j))){ //W and T stripes
            int maximum_rooks_in_T = min(i, delta_j);
            for(int num_rooks = 0; num_rooks <= min(i,j); num_rooks++){
                for(int r_T = 0; r_T <= min(maximum_rooks_in_T, num_rooks); r_T++){
                    int rooks_left = num_rooks - r_T;
                    long int H_tmp = values[0][rooks_left][fields_number + rooks_left];
                    long int right = single_type_rectangle(i - rooks_left, delta_j, r_T);
                    values[knot_index][num_rooks][fields_number + rooks_left] = H_tmp * right;
                }
            }
        }
        else {
            int maximum_rooks_in_L = min(old_i, delta_j);
            int maximum_rooks_in_T = min(delta_i, delta_j);
            int maximum_rooks_in_W = min(delta_i, old_j);
            for(int num_rooks = min_number_of_rooks(i,j,fields_number); num_rooks <= min(i,j); num_rooks++){
                for(int result = -num_rooks; result <= num_rooks; result++){
                    long int sum = 0;
                    for(int r_L = 0; r_L <= min(maximum_rooks_in_L, num_rooks); r_L++) {
                        for (int r_T = 0; r_T <= min(maximum_rooks_in_T, num_rooks); r_T++) {
                            for (int r_W = 0; r_W <= min(maximum_rooks_in_W, num_rooks); r_W++) {
                                int rooks_left = num_rooks - r_W - r_T - r_L;
                                if(rooks_left >= 0 && min_number_of_rooks(old_i, old_j, fields_number) <= rooks_left && 0 <= fields_number + result - r_W + r_L && result - r_W + r_L < fields_number){
                                    long int H_tmp = values[knot_index - 1][rooks_left][fields_number + result - r_W + r_L];
                                    long int bottom = single_type_rectangle(delta_i, old_j - rooks_left, r_W);
                                    long int corner = single_type_rectangle(delta_i - r_W, delta_j, r_T);
                                    long int right = single_type_rectangle(old_i - rooks_left, delta_j - r_T, r_L);
                                    sum += H_tmp * bottom * corner * right;
                                }
                            }
                        }
                    }
                    values[knot_index][num_rooks][fields_number + result] = sum;
                }
            }
        }
    }
    if(knots.size() > 1){
        i = fields_number;
        j = fields_number;
        vector<int> previous_knot = knots[knots.size() - 2];
        int old_i = previous_knot[0];
        int old_j = previous_knot[1];
        int delta_i = i - old_i;
        int delta_j = j - old_j;
        int maximum_rooks_in_L = min(old_i, delta_j);
        int maximum_rooks_in_T = min(delta_i, delta_j);
        int maximum_rooks_in_W = min(delta_i, old_j);
        int num_rooks = fields_number;
        for(int result = -num_rooks; result <= num_rooks; result++) {
            long int sum = 0;
            for (int r_L = 0; r_L <= min(maximum_rooks_in_L, num_rooks); r_L++) {
                for (int r_T = 0; r_T <= min(maximum_rooks_in_T, num_rooks); r_T++) {
                    for (int r_W = 0; r_W <= min(maximum_rooks_in_W, num_rooks); r_W++) {
                        int rooks_left = num_rooks - r_W - r_T - r_L;
                        if (rooks_left >= 0 && min_number_of_rooks(old_i, old_j, fields_number) <= rooks_left &&
                            0 <= fields_number + result - r_W + r_L && result - r_W + r_L < fields_number) {
                            long int H_tmp = values[knots.size() - 2][rooks_left][fields_number + result - r_W + r_L];
                            long int bottom = single_type_rectangle(delta_i, old_j - rooks_left, r_W);
                            long int corner = single_type_rectangle(delta_i - r_W, delta_j, r_T);
                            long int right = single_type_rectangle(old_i - rooks_left, delta_j - r_T, r_L);
                            sum += H_tmp * bottom * corner * right;
                        }
                    }
                }
            }
            values[knots.size()-1][num_rooks][fields_number + result] = sum;
        }
    }
    return values.back().back();
}

double symmetrized_payoff_chopstick(vector<int> s_A, vector<int> s_B){
    int fields_number = s_A.size();
    vector<long int> values = recurrence_H_chopstick(s_A, s_B);
    double payoff = 0;
    for (int result = -fields_number; result <= fields_number; result++){
        payoff += values[fields_number + result] * sign(result);
    }
    payoff /= factorial(fields_number);
    return payoff;
}
