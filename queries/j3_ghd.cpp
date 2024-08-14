//
// Created by anouk on 13-08-24.
//

#include <fstream>
#include<bits/stdc++.h>
#include<ratio>
#include<chrono>
#include<ctime>

using namespace std::chrono;

#include "../includes/ghd.hpp"
#include "../src/ghd_optimal_joins.cpp"


#define AT_X 0
#define AT_Y 1
#define AT_Z 2

std::vector<std::vector<uint64_t>> *read_relation(const std::string filename, uint16_t n_Atts) {
    std::ifstream input_stream(filename);
    uint64_t x;
    uint16_t i, j = 0;

    std::vector<std::vector<uint64_t>> *relation;
    std::vector<uint64_t> tuple;

    relation = new std::vector<std::vector<uint64_t>>();

    input_stream >> x;
    while (!input_stream.eof()) {
        tuple.clear();
        for (i = 0; i < n_Atts; i++) {
            tuple.push_back(x);
            input_stream >> x;
        }
        relation->push_back(tuple);
    }

    return relation;
}


uint64_t maximum_in_table(std::vector<std::vector<uint64_t>> &table, uint16_t n_columns, uint64_t max_temp)
{
    uint64_t i, j;

    for (i = 0; i < table.size(); i++)
        for (j = 0; j < n_columns; j++)
            if (table[i][j] > max_temp)
                max_temp = table[i][j];


    return max_temp;
}


int main(int argc, char **argv) {
    qdag::att_set att_R;
    qdag::att_set att_S;
    qdag::att_set att_T;

    att_R.push_back(0); att_R.push_back(1);
    att_S.push_back(2); att_S.push_back(1);
    att_T.push_back(1); att_T.push_back(3);

    std::string strRel_R(argv[1]), strRel_S(argv[2]), strRel_T(argv[3]);

    std::vector<std::vector<uint64_t>>* rel_R = read_relation(strRel_R, att_R.size());
    std::vector<std::vector<uint64_t>>* rel_S = read_relation(strRel_S, att_S.size());
    std::vector<std::vector<uint64_t>>* rel_T = read_relation(strRel_T, att_T.size());

    uint64_t grid_side = 128;

    grid_side = maximum_in_table(*rel_R, att_R.size(), grid_side);
    grid_side = maximum_in_table(*rel_S, att_S.size(), grid_side);
    grid_side = maximum_in_table(*rel_T, att_T.size(), grid_side);

    // TODO: fix grid size -> 2 ** ceil( log2(grid_side) )
    grid_side++;

    qdag qdag_rel_R(*rel_R, att_R, grid_side, 2, att_R.size());
    qdag qdag_rel_S(*rel_S, att_S, grid_side, 2, att_S.size());
    qdag qdag_rel_T(*rel_T, att_T, grid_side, 2, att_T.size());

    // Crear vectores de relacion de cada nodo

    vector<qdag> Q_root(1);
    Q_root[0] = qdag_rel_T;

    vector<qdag> Q_b(2);
    Q_b[0] = qdag_rel_S;
    Q_b[1] = qdag_rel_R;


    // Crear GHDs
    vector<ghd> empty_children(0);
    ghd sub_b = ghd(Q_b, empty_children);
    vector<ghd> level_1;
    level_1.push_back(sub_b);
    ghd root = ghd(Q_root, level_1);

    high_resolution_clock::time_point start, stop;
    double total_time = 0.0;
    duration<double> time_span;

    vector<qdag> test(3);
    test[0] = qdag_rel_R;
    test[1] = qdag_rel_S;
    test[2] = qdag_rel_T;

    qdag* test_result;
    start = high_resolution_clock::now();
    test_result = multiJoin(test, false, 1000);
    stop = high_resolution_clock::now();
    time_span = duration_cast<microseconds>(stop - start);
    total_time = time_span.count();

    cout << grid_side << endl;
    // TODO: imprimir tamano de las relaciones
    // TODO: imprimir ocurrencias en el resultado

    cout << "multijoin ended in " << total_time << " seconds" << endl;

    start = high_resolution_clock::now();

    qdag* yan_res;
    yan_res = yannakakis(root);

    stop = high_resolution_clock::now();
    time_span = duration_cast<microseconds>(stop - start);
    total_time = time_span.count();

    cout << "Yannakakis ended in " << total_time << " seconds" << endl;

    return 0;
}
