//
// Created by anouk on 24-04-21.
//
#include <algorithm>
#include "ghd.hpp"

qdag *yannakakis(ghd root)
{
    // Ejecutar multijoin en todos los niveles
    root.deep_exec_multijoin();
    auto result = root.get_relations();

    // Ejecutar semijoin entre root y nivel 1
    root.constrained_by_children();

    root.constrain_children();

    // multijoin entre nodos para obtener resultado del join
    //todo: obtener todas las relaciones, no solo el siguiente nivel
    vector<qdag> producto_punto;
    root.get_subtree_qdags(producto_punto);

    qdag* qResult = multiJoin(producto_punto, false, 1000);

    return qResult;
}