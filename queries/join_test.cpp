
#include <fstream>
#include<bits/stdc++.h>
#include<ratio>

using namespace std::chrono;


//#include "../src/joins.cpp"
#include "../includes/ghd.hpp"

high_resolution_clock::time_point start_select, stop_select;
double total_time_select = 0.0;
duration<double> time_span_select;

#define AT_X1 6
#define AT_X2 5
#define AT_X3 3
#define AT_X4 7


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

uint64_t removeContinuousZeros(uint64_t seq) {
    uint64_t result = 0;
    int count = 0;

    // Process each 4-bit block from the rightmost side
    for (int i = 0; i < 64; i += 4) {
        // Extract the current 4-bit block
        uint64_t block = seq & 0xF;

        if (block != 0) {
            // Append the non-zero block to the result
            result |= (block << count);
            count += 4;
        }

        // Move to the next 4-bit block
        seq >>= 4;
    }

    return result;
}



int main(int argc, char** argv)
{
    qdag::att_set att_R;
    qdag::att_set att_S;
    qdag::att_set att_T;
    qdag::att_set att_Q;

    att_R.push_back(AT_X1); att_R.push_back(AT_X2);
    att_S.push_back(AT_X2); att_S.push_back(AT_X3);
    att_T.push_back(AT_X3); att_T.push_back(AT_X4);//att_T.push_back(AT_X3);

    att_Q.push_back(AT_X3); att_Q.push_back(AT_X1);//att_Q.push_back(AT_X1);

    std::string strRel_R(argv[1]), strRel_S(argv[2]), strRel_T(argv[3]), strRel_Q(argv[4]);
    std::vector<std::vector<uint64_t>>* rel_R = read_relation(strRel_R, att_R.size());
    std::vector<std::vector<uint64_t>>* rel_S = read_relation(strRel_S, att_S.size());
    std::vector<std::vector<uint64_t>>* rel_T = read_relation(strRel_T, att_T.size());
    std::vector<std::vector<uint64_t>>* rel_Q = read_relation(strRel_Q, att_Q.size());

    uint64_t grid_side = 32;

    grid_side = maximum_in_table(*rel_R, att_R.size(), grid_side);
    grid_side = maximum_in_table(*rel_S, att_S.size(), grid_side);
    grid_side = maximum_in_table(*rel_T, att_T.size(), grid_side);
    grid_side = maximum_in_table(*rel_Q, att_Q.size(), grid_side);

    grid_side++;

    //cout << "Grid side: " << grid_side << endl;

    qdag qdag_rel_R(*rel_R, att_R, grid_side, 2, att_R.size());
    qdag qdag_rel_S(*rel_S, att_S, grid_side, 2, att_S.size());
    qdag qdag_rel_T(*rel_T, att_T, grid_side, 2, att_T.size());
    qdag qdag_rel_Q(*rel_Q, att_Q, grid_side, 2, att_Q.size());

    std::ostream &output_stream = cout;
    cout << "izquierda:\n";
    qdag_rel_R.print(output_stream);
    cout << "\nderecha:\n";
    qdag_rel_S.print(output_stream);
    cout << endl;
    qdag_rel_T.print(output_stream);

    cout << endl;
    qdag_rel_Q.print(output_stream);

    vector<qdag> Q(3);

    Q[0] = qdag_rel_R;
    Q[1] = qdag_rel_S;
    Q[2] = qdag_rel_T;

    qdag *Join_Result;
    //Join_Result = multiJoin(Q, false, 1000);
    cout << "\n result:\n";
    //Join_Result->print(output_stream);
    semiJoin(Q, false, 1000);
    cout << "\n active:\n";
    Q[0].print_active(output_stream);

    vector<qdag> Q_pt2(2);

    Q_pt2[0] = qdag_rel_R;
    Q_pt2[1] = qdag_rel_Q;

    qdag *Join_Result2;
    // Join_Result2 = multiJoin(Q_pt2, false, 1000);
    // cout << "\n result:\n";
    // Join_Result2->print(output_stream);
    semiJoin(Q_pt2, false, 1000);
    cout << "\n active:\n";
    Q_pt2[0].print_active(output_stream);
    //Q_pt2[0].print(output_stream);

    // seq = 20720;
    //uint64_t result = removeContinuousZeros(seq);

    //std::cout << "Original: " << seq << std::endl;
    //std::cout << "Result: " << result << std::endl;
    return 0;
}
