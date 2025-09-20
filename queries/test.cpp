
#include <bits/stdc++.h>
#include <chrono>
#include <ctime>
#include <fstream>
#include <ratio>

using namespace std::chrono;

#include "../includes/ghd.hpp"
#include "../src/ghd_optimal_joins.cpp"

#define AT_X 0
#define AT_Y 1
#define AT_Z 2
#define AT_YP 3
#define AT_ZP 4

int main(int argc, char** argv)
{
    // Setup de GHD: leer qdags que forman nodos
    qdag::att_set att_R;
    qdag::att_set att_S;
    qdag::att_set att_T;

    att_R.push_back(0);
    att_R.push_back(1);
    att_R.push_back(2);
    att_R.push_back(3);
    att_R.push_back(4);
    std::string strRel_R(argv[1]);

    std::vector<std::vector<uint64_t>>* rel_R = read_relation(strRel_R, att_R.size());

    uint64_t grid_side = 32;

    grid_side = maximum_in_table(*rel_R, att_R.size(), grid_side);
    grid_side = pow(2, std::ceil(log2(grid_side)));

    qdag qdag_rel_R(*rel_R, att_R, grid_side, 2, att_R.size());

    auto rels = { rel_R};
    cout << "read all relations, with a total of " << relations_size(rels) << " tuples" << endl;

    vector<qdag> qdags = { qdag_rel_R};
    cout << qdag_rel_R.size() << " bytes" << endl;
    qdag_rel_R.print(cout);
    return 0;
}
