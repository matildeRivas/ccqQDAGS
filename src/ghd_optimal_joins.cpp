//
// Created by anouk on 24-04-21.
//
#include <algorithm>
#include "ghd.hpp"
#include<ratio>
#include<chrono>
#include<ctime>
#include<omp.h>

using namespace std::chrono;

high_resolution_clock::time_point start_select, stop_select;
double total_time_select = 0.0;
duration<double> time_span_select;


qdag *yannakakis(ghd& root)
{

    // Ejecutar multijoin en todos los niveles
    root.deep_exec_multijoin();
    auto result = root.get_relations();

    // Ejecutar semijoin entre root y nivel 1
    root.constrained_by_children();

    root.constrain_children();

    // multijoin entre nodos para obtener resultado del join
    vector<qdag> producto_punto;
    root.get_subtree_qdags(producto_punto);

    qdag* qResult = multiJoin(producto_punto, false, 1000);

    return qResult;
}

qdag* yannakakis_par(ghd& root)
{
    // Collect all nodes into a flat list
    std::vector<ghd*> node_list;
    root.collect_all_nodes(node_list);

    // Execute exec_multijoin in parallel for all nodes
#pragma omp parallel for
    for (size_t i = 0; i < node_list.size(); ++i) {
        node_list[i]->exec_multijoin();
    }

    // solve_mj = high_resolution_clock::now();

    auto result = root.get_relations();

    // Ejecutar semijoin entre root y nivel 1

    root.constrained_by_children();
    // bottom_up = high_resolution_clock::now();

    root.constrain_children();

    // multijoin entre nodos para obtener resultado del join
    // top_down = high_resolution_clock::now();
    vector<qdag> producto_punto;
    root.get_subtree_qdags(producto_punto);

    qdag* qResult = multiJoin(producto_punto, false, 1000);
    return qResult;
}