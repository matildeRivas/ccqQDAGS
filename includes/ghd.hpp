//
// Created by anouk on 08-08-23.
//

#ifndef CCQ_QDAGS_GHD_HPP
#define CCQ_QDAGS_GHD_HPP

#include <inttypes.h>
#include <vector>
#include "qdags.hpp"
#include "../src/joins.cpp"

using namespace std;

class ghd {
    vector<qdag> relations;
    vector<ghd> children;

public:

    ghd() = default;

    ghd(vector<qdag> qdags, vector<ghd> subtrees) {
        relations = qdags;
        children = subtrees;
    }

    vector<qdag> get_relations(){
        return relations;
    }

    vector<qdag> get_child_qdags(){
        // This will be used during semijoin, so there will only be 1 qdag per vector
        vector<qdag> results;
        for (auto child = children.begin(); child != children.end(); child++){
            results.push_back(child->get_relations().front());
        }
        return results;
    }

    void set_relations(vector<qdag> new_relations){
        relations = new_relations;
    }

    void ex_multijoin(){
        qdag* join_result = multiJoin(relations, false, 1000);
        relations.clear();
        relations.push_back(*join_result);
        relations.shrink_to_fit();
        cout << "terminó un mj" << endl;
    }

    void deep_ex_multijoin(){
        cout << "llamado a deep ex" << endl;
        ex_multijoin();
        for (auto child = children.begin(); child != children.end(); child++){
            child->deep_ex_multijoin();
        }
    }

    void constrained_by_children(){
        // semijoin entre nodo y sus hijos. Debo pasarle un vector en el cual el primer elemento sea
        // mi qdag, y el resto son los qdag de children
        // esto debería alterar mi qdag
        vector<qdag> rels = get_child_qdags();
        rels.insert(rels.begin(), relations.front());
        semiJoin(rels, false, 1000);
    }
};

#endif //CCQ_QDAGS_GHD_HPP
