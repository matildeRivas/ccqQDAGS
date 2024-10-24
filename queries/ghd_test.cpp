
#include <fstream>
#include<bits/stdc++.h>
#include<ratio>
#include<chrono>
#include<ctime>

using namespace std::chrono;


//#include "../src/joins.cpp"
#include "../includes/ghd.hpp"
#include "../src/ghd_optimal_joins.cpp"



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
    qdag::att_set att_R;
    qdag::att_set att_S;
    qdag::att_set att_T;
    qdag::att_set att_U;

    att_R.push_back(0); att_R.push_back(1);
    att_S.push_back(2); att_S.push_back(1);
    att_T.push_back(1); att_T.push_back(3);

    std::string strRel_R(argv[1]), strRel_S(argv[2]), strRel_T(argv[3]);//, strRel_U(argv[4]);

    std::vector<std::vector<uint64_t>>* rel_R = read_relation(strRel_R, att_R.size());
    //cout<<"R"<<endl;
    std::vector<std::vector<uint64_t>>* rel_S = read_relation(strRel_S, att_S.size());
    //cout<<"s"<<endl;
    std::vector<std::vector<uint64_t>>* rel_T = read_relation(strRel_T, att_T.size());
    //cout<<"t"<<endl;
    //std::vector<std::vector<uint64_t>>* rel_U = read_relation(strRel_U, att_U.size());

    uint64_t grid_side = 128;

    grid_side = maximum_in_table(*rel_R, att_R.size(), grid_side);
    grid_side = maximum_in_table(*rel_S, att_S.size(), grid_side);
    grid_side = maximum_in_table(*rel_T, att_T.size(), grid_side);
    //grid_side = maximum_in_table(*rel_U, att_U.size(), grid_side);

    grid_side = pow(2, std::ceil(log2(grid_side) ));
    cout << grid_side << endl;

    qdag qdag_rel_R(*rel_R, att_R, grid_side, 2, att_R.size());
    //cout << "Built R\n";
    qdag_rel_R.print(cout);
    qdag qdag_rel_S(*rel_S, att_S, grid_side, 2, att_S.size());
    cout << "Built S\n";
    qdag_rel_S.print(cout);
    qdag qdag_rel_T(*rel_T, att_T, grid_side, 2, att_T.size());
    cout << "Built T\n";
    qdag_rel_T.print(cout);
    //cout<<"done"<<endl;
    //qdag qdag_rel_U(*rel_U, att_U, grid_side, 2, att_U.size());


    // Crear vectores de relacion de cada nodo

    vector<qdag> Q_root(1);

    Q_root[0] = qdag_rel_T;
    //Q_root[1] = qdag_rel_S;

    vector<qdag> Q_b(2);
    Q_b[0] = qdag_rel_S;
    Q_b[1] = qdag_rel_R;
    //Q_b[2] = qdag_rel_T;
/*
    vector<qdag> Q_c(3);
    Q_c[0] = qdag_rel_RP;
    Q_c[1] = qdag_rel_SP;
    Q_c[2] = qdag_rel_TP;*/



    // Crear GHDs

    vector<ghd> empty_children(0);
    ghd sub_b = ghd(Q_b, empty_children);
    //ghd sub_c = ghd(Q_c, empty_children);
    vector<ghd> level_1;
    level_1.push_back(sub_b);
    //level_1.push_back(sub_c);
    ghd root = ghd(Q_root, level_1);

    // Ejecutar multijoin en todos los niveles
    /*
    root.deep_exec_multijoin();
    auto result = root.get_relations();
    for (auto rel = result.begin(); rel != result.end(); rel++){
        cout << "resulting qdag root: " << endl;
        rel->print(cout);
        cout << endl;
    }
    auto result_level1 = root.get_child_qdags().front();
    cout << "resulting qdag level 1: " << endl;
    result_level1.print(cout);

    // Ejecutar semijoin entre root y nivel 1
    root.constrained_by_children();
    //cout << "bv de root desp de sj" <<endl;
    //root.get_relations().front().print(cout);
    cout << "active de root desp de sj" <<endl;
    root.get_relations().front().print_active(cout);

    root.constrain_children();
    //cout << "bv de l1 desp de sj" <<endl;
    //root.get_child_qdags().front().print(cout);
    cout << "active de level1 desp de sj" <<endl;
    root.get_child_qdags().front().print_active(cout);

    // multijoin para obtener resultado del join
    vector<qdag> producto_punto(2);
    producto_punto[0] = root.get_relations().front();
    cout << "izq\n";
    producto_punto[0].print(cout);
    producto_punto[1] = root.get_child_qdags().front();
    cout << "der\n";
    producto_punto[1].print(cout);
    cout << "resultado final\n";
    qdag* res = multiJoin(producto_punto, false, 1000);
    res->print(cout);

*/

    high_resolution_clock::time_point start, stop;
    double total_time = 0.0;
    duration<double> time_span;

    vector<qdag> test(3);

    test[0] = qdag_rel_R;
    test[1] = qdag_rel_S;
    test[2] = qdag_rel_T;
    //test[3] = qdag_rel_U;

    qdag* test_result;
    start = high_resolution_clock::now();
    test_result = multiJoin(test, false, 1000);
    stop = high_resolution_clock::now();
    time_span = duration_cast<microseconds>(stop - start);
    total_time = time_span.count();

    cout << "\nmultijoin ended in " << total_time << " seconds" << endl;
    test_result->print(cout);

    cout << endl;
    qdag* yan_res;

    start = high_resolution_clock::now();
    cout << "Yannakakis" << endl;
    yan_res = yannakakis(root);

    stop = high_resolution_clock::now();
    time_span = duration_cast<microseconds>(stop - start);
    total_time = time_span.count();

    cout << "Yannakakis ended in " << total_time << " seconds" << endl;

    //cout << "resultado yannakakis\n";
    //yan_res->print(cout);

    return 0;
}
