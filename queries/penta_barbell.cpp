//
// Created by anouk on 30-09-24.
//


#include <fstream>
#include<bits/stdc++.h>
#include<ratio>
#include<chrono>
#include<ctime>
#include<iostream>

using namespace std::chrono;


//#include "../src/joins.cpp"
#include "../includes/ghd.hpp"
#include "../src/ghd_optimal_joins.cpp"


std::vector<std::vector<uint64_t>> *read_relation(const std::string filename, uint16_t n_Atts) {
    std::ifstream input_stream(filename);
    uint64_t x;
    uint16_t i, j = 0;

    std::vector<std::vector<uint64_t>> *relation;
    std::vector<uint64_t> tuple;

    relation = new std::vector<std::vector<uint64_t>>();

    input_stream >> x;
    //cout << "contenido "<< x <<endl;
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
    // Setup de GHD: leer qdags que forman nodos
    qdag::att_set att_A;
    qdag::att_set att_B;
    qdag::att_set att_C;
    qdag::att_set att_D;
    qdag::att_set att_E;

    qdag::att_set att_J;

    qdag::att_set att_R;
    qdag::att_set att_S;
    qdag::att_set att_T;
    qdag::att_set att_P;
    qdag::att_set att_Q;

    att_A.push_back(0);
    att_A.push_back(1);

    att_B.push_back(1);
    att_B.push_back(2);

    att_C.push_back(2);
    att_C.push_back(3);

    att_D.push_back(3);
    att_D.push_back(4);

    att_E.push_back(4);
    att_E.push_back(0);

    att_J.push_back(4);
    att_J.push_back(5);

    att_P.push_back(5);
    att_P.push_back(6);

    att_Q.push_back(6);
    att_Q.push_back(7);

    att_R.push_back(7);
    att_R.push_back(8);

    att_S.push_back(8);
    att_S.push_back(9);

    att_T.push_back(9);
    att_T.push_back(5);

    std::string strRel_A(argv[1]), strRel_B(argv[2]), strRel_C(argv[3]), strRel_D(argv[4]), strRel_E(argv[5]), strRel_J(argv[6]), strRel_P(argv[7]), strRel_Q(argv[8]), strRel_R(argv[9]), strRel_S(argv[10]), strRel_T(argv[11]);

    std::vector<std::vector<uint64_t>>* rel_A = read_relation(strRel_A, att_A.size());
    std::vector<std::vector<uint64_t>>* rel_B = read_relation(strRel_B, att_B.size());
    std::vector<std::vector<uint64_t>>* rel_C = read_relation(strRel_C, att_C.size());
    std::vector<std::vector<uint64_t>>* rel_D = read_relation(strRel_D, att_D.size());
    std::vector<std::vector<uint64_t>>* rel_E = read_relation(strRel_E, att_E.size());

    std::vector<std::vector<uint64_t>>* rel_J = read_relation(strRel_J, att_J.size());

    std::vector<std::vector<uint64_t>>* rel_P = read_relation(strRel_P, att_P.size());
    std::vector<std::vector<uint64_t>>* rel_Q = read_relation(strRel_Q, att_Q.size());
    std::vector<std::vector<uint64_t>>* rel_R = read_relation(strRel_R, att_R.size());
    std::vector<std::vector<uint64_t>>* rel_S = read_relation(strRel_S, att_S.size());
    std::vector<std::vector<uint64_t>>* rel_T = read_relation(strRel_T, att_T.size());

    uint64_t grid_side = 128;

    grid_side = maximum_in_table(*rel_A, att_A.size(), grid_side);
    grid_side = maximum_in_table(*rel_B, att_B.size(), grid_side);
    grid_side = maximum_in_table(*rel_C, att_C.size(), grid_side);
    grid_side = maximum_in_table(*rel_D, att_D.size(), grid_side);
    grid_side = maximum_in_table(*rel_E, att_E.size(), grid_side);
    grid_side = maximum_in_table(*rel_J, att_J.size(), grid_side);
    grid_side = maximum_in_table(*rel_P, att_P.size(), grid_side);
    grid_side = maximum_in_table(*rel_Q, att_Q.size(), grid_side);
    grid_side = maximum_in_table(*rel_R, att_R.size(), grid_side);
    grid_side = maximum_in_table(*rel_S, att_S.size(), grid_side);
    grid_side = maximum_in_table(*rel_T, att_T.size(), grid_side);

    grid_side = pow(2, std::ceil(log2(grid_side) ));
    //cout << grid_side << endl;
    qdag qdag_rel_A(*rel_A, att_A, grid_side, 2, att_A.size());
    qdag qdag_rel_B(*rel_B, att_B, grid_side, 2, att_B.size());
    qdag qdag_rel_C(*rel_C, att_C, grid_side, 2, att_C.size());
    qdag qdag_rel_D(*rel_D, att_D, grid_side, 2, att_D.size());
    qdag qdag_rel_E(*rel_E, att_E, grid_side, 2, att_E.size());

    qdag qdag_rel_J(*rel_J, att_J, grid_side, 2, att_J.size());

    qdag qdag_rel_P(*rel_P, att_P, grid_side, 2, att_P.size());
    qdag qdag_rel_Q(*rel_Q, att_Q, grid_side, 2, att_Q.size());
    qdag qdag_rel_R(*rel_R, att_R, grid_side, 2, att_R.size());
    qdag qdag_rel_S(*rel_S, att_S, grid_side, 2, att_S.size());
    qdag qdag_rel_T(*rel_T, att_T, grid_side, 2, att_T.size());

    high_resolution_clock::time_point start, stop;

    if (strcmp(argv[12], "mj") == 0) {
        vector<qdag> test(11);

        test[0] = qdag_rel_A;
        test[1] = qdag_rel_B;
        test[2] = qdag_rel_C;
        test[3] = qdag_rel_D;
        test[4] = qdag_rel_E;
        test[5] = qdag_rel_J;
        test[6] = qdag_rel_P;
        test[7] = qdag_rel_Q;
        test[8] = qdag_rel_R;
        test[9] = qdag_rel_S;
        test[10] = qdag_rel_T;

        qdag* test_result;
        start = high_resolution_clock::now();
        test_result = multiJoin(test, false, 1000);
        stop = high_resolution_clock::now();
    } else {
        // Crear vectores de relacion de cada nodo
        vector<qdag> Q_root(1);

        Q_root[0] = qdag_rel_J;

        vector<qdag> Q_b(5);
        Q_b[0] = qdag_rel_A;
        Q_b[1] = qdag_rel_B;
        Q_b[2] = qdag_rel_C;
        Q_b[3] = qdag_rel_D;
        Q_b[4] = qdag_rel_E;

        vector<qdag> Q_c(5);
        Q_c[0] = qdag_rel_P;
        Q_c[1] = qdag_rel_Q;
        Q_c[2] = qdag_rel_R;
        Q_c[3] = qdag_rel_S;
        Q_c[4] = qdag_rel_T;

        // Crear GHDs
        vector<ghd> empty_children(0);
        ghd sub_b = ghd(Q_b, empty_children);
        ghd sub_c = ghd(Q_c, empty_children);
        vector<ghd> level_1;
        level_1.push_back(sub_b);
        level_1.push_back(sub_c);
        ghd root = ghd(Q_root, level_1);

        qdag* yan_res;
        start = high_resolution_clock::now();
        if (strcmp(argv[12], "yk") == 0) {
            yan_res = yannakakis(root);
        } else {
            yan_res = yannakakis_par(root);
        }
        stop = high_resolution_clock::now();
    }

    const std::chrono::duration<double, std::milli> time_span = stop - start;
    double time = time_span.count() / 1000;
    ofstream outfile(argv[13], ios::app);
    outfile << time << endl;
    outfile.close();

    return 0;
}
