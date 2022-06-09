
#include "gurobi_c++.h"
#include "src/algorithm/pureStrategy.h"
#include "src/algorithm/mixedStrategy.h"
#include "src/algorithm/game.h"
#include "src/algorithm/oracle.h"
#include "src/algorithm/algorithm.h"
using namespace std;

int main(int argc, char **argv){
    if (argc != 4) {
        cout << "Usage:\n"
                "Number of playerA's troops\n"
                "Number of playerB's troops\n"
                "Number of battlefields\n";
        return 1;
    }
    auto A = (int) strtol(argv[1], nullptr, 10);
    auto B = (int) strtol(argv[2], nullptr, 10);
    auto n = (int) strtol(argv[3], nullptr, 10);

    auto start = chrono::steady_clock::now();
    Game g = algorithm(A, B, n);
    auto end = chrono::steady_clock::now();
    cout << "Elapsed time in milliseconds: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms" << endl;
    return 0;
}