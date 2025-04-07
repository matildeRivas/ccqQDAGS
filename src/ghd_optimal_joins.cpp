//
// Created by anouk on 24-04-21.
//
#include <algorithm>
#include "ghd.hpp"

qdag *yannakakis(ghd root)
{
    cout << " Ejecutar multijoin en todos los niveles" << endl;
    root.deep_exec_multijoin();
    auto result = root.get_relations();

    cout << " Ejecutar semijoin entre root y nivel 1" << endl;
    root.constrained_by_children();

    root.constrain_children();

    // root.get_relations()[0].print(cout);

    cout << "multijoin entre nodos para obtener resultado del join" << endl;
    //todo: obtener todas las relaciones, no solo el siguiente nivel
    vector<qdag> producto_punto;
    root.get_subtree_qdags(producto_punto);

    qdag* qResult = multiJoin(producto_punto, false, 1000);

    /** parallel version
     * qdag *yannakakis(ghd root)
{
    high_resolution_clock::time_point start, solve_mj, bottom_up, top_down, stop;
    double total_time = 0.0;
    duration<double> time_span_mj, time_span_bu, time_span_td, time_span_pp;
    // Ejecutar multijoin en todos los niveles
    start = high_resolution_clock::now();

    // Collect all nodes into a flat list
    std::vector<ghd*> node_list;
    root.collect_all_nodes(node_list);

    // Execute exec_multijoin in parallel for all nodes
    #pragma omp parallel for
    for (size_t i = 0; i < node_list.size(); ++i) {
        node_list[i]->exec_multijoin();
    }


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
     */

    return qResult;
}