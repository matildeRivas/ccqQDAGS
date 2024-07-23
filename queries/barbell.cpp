
#include <fstream>
#include<bits/stdc++.h>
#include<ratio>
#include<chrono>
#include<ctime>

using namespace std::chrono;


//#include "../src/joins.cpp"
#include "../includes/ghd.hpp"
#include "../src/ghd_optimal_joins.cpp"

high_resolution_clock::time_point start_select, stop_select;
double total_time_select = 0.0;
duration<double> time_span_select;

#define AT_X 0
#define AT_Y 1
#define AT_Z 2
#define AT_XP 3
#define AT_YP 4
#define AT_ZP 5

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


uint64_t maximum_in_table(std::vector<std::vector<uint64_t>> &table, uint16_t n_columns, uint64_t max_temp) {
    uint64_t i, j;

    for (i = 0; i < table.size(); i++)
        for (j = 0; j < n_columns; j++)
            if (table[i][j] > max_temp)
                max_temp = table[i][j];


    return max_temp;
}


int main(int argc, char **argv) {
    // Setup de GHD: leer qdags que forman nodos
    qdag::att_set att_R;
    qdag::att_set att_S;
    qdag::att_set att_T;
    qdag::att_set att_U;
    qdag::att_set att_RP;
    qdag::att_set att_SP;
    qdag::att_set att_TP;


    att_R.push_back(AT_X);
    att_R.push_back(AT_Y);

    att_S.push_back(AT_Y);
    att_S.push_back(AT_Z);

    att_T.push_back(AT_X);
    att_T.push_back(AT_Z);

    att_U.push_back(AT_X);
    att_U.push_back(AT_XP);

    att_RP.push_back(AT_XP);
    att_RP.push_back(AT_YP);

    att_SP.push_back(AT_YP);
    att_SP.push_back(AT_ZP);

    att_TP.push_back(AT_XP);
    att_TP.push_back(AT_ZP);

    std::string strRel_R(argv[1]), strRel_S(argv[2]), strRel_T(argv[3]), strRel_U(argv[4]), strRel_RP(argv[5]), strRel_SP(argv[6]), strRel_TP(argv[7]);
    std::vector<std::vector<uint64_t>> *rel_R = read_relation(strRel_R, att_R.size());
    std::vector<std::vector<uint64_t>> *rel_S = read_relation(strRel_S, att_S.size());
    std::vector<std::vector<uint64_t>> *rel_T = read_relation(strRel_T, att_T.size());
    std::vector<std::vector<uint64_t>> *rel_U = read_relation(strRel_U, att_U.size());
    std::vector<std::vector<uint64_t>> *rel_RP = read_relation(strRel_RP, att_RP.size());
    std::vector<std::vector<uint64_t>> *rel_SP = read_relation(strRel_SP, att_SP.size());
    std::vector<std::vector<uint64_t>> *rel_TP = read_relation(strRel_TP, att_TP.size());

    uint64_t grid_side = 32;

    grid_side = maximum_in_table(*rel_R, att_R.size(), grid_side);
    grid_side = maximum_in_table(*rel_S, att_S.size(), grid_side);
    grid_side = maximum_in_table(*rel_T, att_T.size(), grid_side);
    grid_side = maximum_in_table(*rel_RP, att_RP.size(), grid_side);
    grid_side = maximum_in_table(*rel_SP, att_SP.size(), grid_side);
    grid_side = maximum_in_table(*rel_TP, att_TP.size(), grid_side);
    grid_side = maximum_in_table(*rel_U, att_U.size(), grid_side);

    grid_side++;

    qdag qdag_rel_R(*rel_R, att_R, grid_side, 2, att_R.size());
    qdag qdag_rel_S(*rel_S, att_S, grid_side, 2, att_S.size());
    qdag qdag_rel_T(*rel_T, att_T, grid_side, 2, att_T.size());
    qdag qdag_rel_U(*rel_U, att_U, grid_side, 2, att_U.size());
    qdag qdag_rel_RP(*rel_RP, att_RP, grid_side, 2, att_RP.size());
    qdag qdag_rel_SP(*rel_SP, att_SP, grid_side, 2, att_SP.size());
    qdag qdag_rel_TP(*rel_TP, att_TP, grid_side, 2, att_TP.size());
    // Crear vectores de relacion de cada nodo

    vector<qdag> Q_root(1);

    Q_root[0] = qdag_rel_U;

    vector<qdag> Q_b(3);
    Q_b[0] = qdag_rel_R;
    Q_b[1] = qdag_rel_S;
    Q_b[2] = qdag_rel_T;

    vector<qdag> Q_c(3);
    Q_c[0] = qdag_rel_RP;
    Q_c[1] = qdag_rel_SP;
    Q_c[2] = qdag_rel_TP;



    // Crear GHDs

    vector<ghd> empty_children(0);
    ghd sub_b = ghd(Q_b, empty_children);
    ghd sub_c = ghd(Q_c, empty_children);
    vector<ghd> level_1;
    level_1.push_back(sub_b);
    level_1.push_back(sub_c);
    ghd root = ghd(Q_root, level_1);

    high_resolution_clock::time_point start, stop;
    double total_time = 0.0;
    duration<double> time_span;

    qdag* yan_res;

    start = high_resolution_clock::now();

    yan_res = yannakakis(root);

    stop = high_resolution_clock::now();
    time_span = duration_cast<microseconds>(stop - start);
    total_time = time_span.count();

    cout << "Yannakakis ended in " << total_time << " seconds" << endl;

    cout << "resultado yannakakis\n";
    yan_res->print(cout);

    return 0;
}
