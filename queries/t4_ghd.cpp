
#include <fstream>
#include<bits/stdc++.h>
#include<ratio>

using namespace std::chrono;

#include "../includes/ghd.hpp"
#include "../src/ghd_optimal_joins.cpp"

#define AT_X 0
#define AT_Y 1
#define AT_Z 2
#define AT_U 3
#define AT_V 4

std::vector<std::vector<uint64_t>>* read_relation(const std::string filename, uint16_t n_Atts)
{
    std::ifstream input_stream(filename);
    uint64_t x;
    uint16_t i, j = 0;

    std::vector<std::vector<uint64_t>>* relation;
    std::vector<uint64_t> tuple;

    relation = new std::vector<std::vector<uint64_t>>();
    if (!input_stream.good()) {
        cout << "file does not exist: '" << filename << "'" << endl;
        return relation;
    }

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

uint64_t maximum_in_table(std::vector<std::vector<uint64_t>>& table, uint16_t n_columns, uint64_t max_temp)
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
    qdag::att_set att_R;
    qdag::att_set att_S;
    qdag::att_set att_T;
    qdag::att_set att_U;

    att_R.push_back(AT_X);
    att_R.push_back(AT_Y);
    att_S.push_back(AT_X);
    att_S.push_back(AT_Z);
    att_T.push_back(AT_X);
    att_T.push_back(AT_U);
    att_U.push_back(AT_X);
    att_U.push_back(AT_V);

    std::string strRel_R(argv[1]), strRel_S(argv[2]), strRel_T(argv[3]), strRel_U(argv[4]);

    std::vector<std::vector<uint64_t>>* rel_R = read_relation(strRel_R, att_R.size());
    std::vector<std::vector<uint64_t>>* rel_S = read_relation(strRel_S, att_S.size());
    std::vector<std::vector<uint64_t>>* rel_T = read_relation(strRel_T, att_T.size());
    std::vector<std::vector<uint64_t>>* rel_U = read_relation(strRel_U, att_U.size());

    if (!rel_R->size() || !rel_S->size() || !rel_T->size() || !rel_U->size()) {
        return 1;
    }

    uint64_t grid_side = 0;

    grid_side = maximum_in_table(*rel_R, att_R.size(), grid_side);
    grid_side = maximum_in_table(*rel_S, att_S.size(), grid_side);
    grid_side = maximum_in_table(*rel_T, att_T.size(), grid_side);
    grid_side = maximum_in_table(*rel_U, att_U.size(), grid_side);

    grid_side = pow(2, std::ceil(log2(grid_side)));

    // cout << "Grid side: " << grid_side << endl;

    qdag qdag_rel_R(*rel_R, att_R, grid_side, 2, att_R.size());
    qdag qdag_rel_S(*rel_S, att_S, grid_side, 2, att_S.size());
    qdag qdag_rel_T(*rel_T, att_T, grid_side, 2, att_T.size());
    qdag qdag_rel_U(*rel_U, att_U, grid_side, 2, att_U.size());

    high_resolution_clock::time_point start, stop;

    if (strcmp(argv[argc - 3], "mj") == 0) {
        vector<qdag> Q(4);
        Q[0] = qdag_rel_R;
        Q[1] = qdag_rel_S;
        Q[2] = qdag_rel_T;
        Q[3] = qdag_rel_U;

        qdag* test_result;
        start = high_resolution_clock::now();
        test_result = multiJoin(Q, false, 1000);
        stop = high_resolution_clock::now();
    } else {
        ghd root;
        if (strcmp(argv[argc - 1], "1") == 0) {
            vector<qdag> Q_root(2);
            Q_root[0] = qdag_rel_R;
            Q_root[1] = qdag_rel_T;

            vector<qdag> Q_b(2);
            Q_b[0] = qdag_rel_S;
            Q_b[1] = qdag_rel_U;
            // Crear GHDs

            vector<ghd> empty_children(0);
            ghd sub_b = ghd(Q_b, empty_children);
            vector<ghd> level_1;
            level_1.push_back(sub_b);
            root = ghd(Q_root, level_1);

        } else if (strcmp(argv[argc - 1], "2") == 0) {
            vector<qdag> Q_root(2);
            Q_root[0] = qdag_rel_R;
            Q_root[1] = qdag_rel_S;

            vector<qdag> Q_b(2);
            Q_b[0] = qdag_rel_T;
            Q_b[1] = qdag_rel_U;
            // Crear GHD

            vector<ghd> empty_children(0);
            ghd sub_b = ghd(Q_b, empty_children);
            vector<ghd> level_1;
            level_1.push_back(sub_b);
            root = ghd(Q_root, level_1);

        } else if (strcmp(argv[argc - 1], "3") == 0) {
            vector<qdag> Q_root(2);
            Q_root[0] = qdag_rel_R;
            Q_root[1] = qdag_rel_U;

            vector<qdag> Q_b(2);
            Q_b[0] = qdag_rel_T;
            Q_b[1] = qdag_rel_S;
            // Crear GHDs

            vector<ghd> empty_children(0);
            ghd sub_b = ghd(Q_b, empty_children);
            vector<ghd> level_1;
            level_1.push_back(sub_b);
            root = ghd(Q_root, level_1);
        }

        qdag* yan_res;

        start = high_resolution_clock::now();
        if (strcmp(argv[argc - 3], "yk") == 0) {
            yan_res = yannakakis(root);
        } else {
            yan_res = yannakakis_par(root);
        }
        stop = high_resolution_clock::now();
    }

    const std::chrono::duration<double, std::milli> time_span = stop - start;
    double time = time_span.count() / 1000;
    cout << "took " << time << "s" << endl;
    ofstream outfile(argv[argc - 2], ios::app);
    outfile << time << endl;
    outfile.close();

    return 0;
}
