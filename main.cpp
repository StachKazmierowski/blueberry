
#include "gurobi_c++.h"
#include "src/algorithm/pureStrategy.h"
#include "src/algorithm/mixedStrategy.h"
#include "src/algorithm/game.h"
#include "src/algorithm/oracle.h"
#include "src/algorithm/algorithm.h"
using namespace std;

int main(){
//    int A = 15, B = 15, n = 10;
//    vector<vector<int>> all_divs = all_divisions(A, n);
//    cout << all_divs.size() << endl;
    Game g = algorithm(20, 20, 15);
    return 0;
}