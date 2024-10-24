//
// Created by anouk on 24-04-21.
//
#include <algorithm>
#include "ghd.hpp"
#include<ratio>
#include<chrono>
#include<ctime>

using namespace std::chrono;

high_resolution_clock::time_point start_select, stop_select;
double total_time_select = 0.0;
duration<double> time_span_select;


qdag *yannakakis(ghd root)
{
    high_resolution_clock::time_point start, solve_mj, bottom_up, top_down, stop;
    double total_time = 0.0;
    duration<double> time_span_mj, time_span_bu, time_span_td, time_span_pp;
    // Ejecutar multijoin en todos los niveles
    start = high_resolution_clock::now();

    root.deep_exec_multijoin();

    //solve_mj = high_resolution_clock::now();

    auto result = root.get_relations();

    // Ejecutar semijoin entre root y nivel 1


    root.constrained_by_children();
    //bottom_up = high_resolution_clock::now();

    root.constrain_children();

    // multijoin entre nodos para obtener resultado del join
    //top_down = high_resolution_clock::now();
    vector<qdag> producto_punto;
    root.get_subtree_qdags(producto_punto);

    qdag* qResult = multiJoin(producto_punto, false, 1000);
    //stop = high_resolution_clock::now();

    //time_span_mj = duration_cast<microseconds>(solve_mj - start);
    //total_time = time_span_mj.count();

    //cout << "node multijoin ended in " << total_time << " seconds" << endl;

    //time_span_bu = duration_cast<microseconds>(bottom_up - solve_mj);
    //total_time = time_span_bu.count();

    //cout << "bottom up ended in " << total_time << " seconds" << endl;

    //time_span_td = duration_cast<microseconds>(top_down - bottom_up);
    //total_time = time_span_td.count();

    //cout << "top down ended in " << total_time << " seconds" << endl;

    //time_span_pp = duration_cast<microseconds>(stop - top_down);
    //total_time = time_span_pp.count();

    //cout << "final multijoin " << total_time << " seconds" << endl;

    return qResult;
}