
#include <fstream>
#include<bits/stdc++.h>
#include<ratio>

using namespace std::chrono;


//#include "../src/joins.cpp"
#include "../includes/ghd.hpp"

high_resolution_clock::time_point start_select, stop_select;
double total_time_select = 0.0;
duration<double> time_span_select;

#define AT_X1 0
#define AT_X2 1
#define AT_X3 2
#define AT_X4 3
#define AT_X5 4
#define AT_X6 5

std::vector<std::vector<uint64_t>>* read_relation(const std::string filename, uint16_t n_Atts)
{
    std::ifstream input_stream(filename);
    uint64_t x;
    uint16_t i, j=0;

    std::vector<std::vector<uint64_t>>* relation;
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



int main(int argc, char** argv)
{
    // Setup de GHD: leer qdags que forman nodos
    qdag::att_set att_R;
    qdag::att_set att_S;
    qdag::att_set att_T;
    qdag::att_set att_X;
    qdag::att_set att_W;

    att_R.push_back(AT_X1); att_R.push_back(AT_X2);
    att_S.push_back(AT_X2); att_S.push_back(AT_X3);
    att_T.push_back(AT_X3); att_T.push_back(AT_X4);//att_T.push_back(AT_X3);
    att_X.push_back(AT_X1); att_X.push_back(AT_X2);//att_Q.push_back(AT_X1);
    att_W.push_back(AT_X1); att_W.push_back(AT_X3);


    std::string strRel_R(argv[1]), strRel_S(argv[2]), strRel_T(argv[3]), strRel_X(argv[4]), strRel_W(argv[5]);
    std::vector<std::vector<uint64_t>>* rel_R = read_relation(strRel_R, att_R.size());
    std::vector<std::vector<uint64_t>>* rel_S = read_relation(strRel_S, att_S.size());
    std::vector<std::vector<uint64_t>>* rel_T = read_relation(strRel_T, att_T.size());
    std::vector<std::vector<uint64_t>>* rel_X = read_relation(strRel_X, att_X.size());
    std::vector<std::vector<uint64_t>>* rel_W = read_relation(strRel_W, att_W.size());

    uint64_t grid_side = 32;

    grid_side = maximum_in_table(*rel_R, att_R.size(), grid_side);
    grid_side = maximum_in_table(*rel_S, att_S.size(), grid_side);
    grid_side = maximum_in_table(*rel_T, att_T.size(), grid_side);
    grid_side = maximum_in_table(*rel_X, att_X.size(), grid_side);
    grid_side = maximum_in_table(*rel_W, att_W.size(), grid_side);

    grid_side++;

    //cout << "Grid side: " << grid_side << endl;

    qdag qdag_rel_R(*rel_R, att_R, grid_side, 2, att_R.size());
    qdag qdag_rel_S(*rel_S, att_S, grid_side, 2, att_S.size());
    qdag qdag_rel_T(*rel_T, att_T, grid_side, 2, att_T.size());
    qdag qdag_rel_X(*rel_X, att_X, grid_side, 2, att_X.size());
    qdag qdag_rel_W(*rel_W, att_W, grid_side, 2, att_W.size());

    // Crear vectores de relacion de cada nodo

    vector<qdag> Q_a(3);

    Q_a[0] = qdag_rel_R;
    Q_a[1] = qdag_rel_S;
    Q_a[2] = qdag_rel_T;

    vector<qdag> Q_b(2);

    Q_b[0] = qdag_rel_X;
    Q_b[1] = qdag_rel_W;

    // Crear GHDs

    vector<ghd> empty_children(0);
    ghd sub = ghd(Q_b, empty_children);
    vector<ghd> level_1;
    level_1.push_back(sub);
    ghd root = ghd(Q_a, level_1);

    // Ejecutar multijoin en todos los niveles

    root.deep_ex_multijoin();
    auto result = root.get_relations();
    for (auto rel = result.begin(); rel != result.end(); rel++){
        cout << "resulting qdag: " << endl;
        rel->print(cout);
    }


    return 0;
}
