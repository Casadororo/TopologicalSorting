#include <bits/stdc++.h>
#include <graphviz/cgraph.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdlib.h>

using namespace std;

// Ordenação topológica usando algoritmo de Kahn
void topologicalSort(Agraph_t *g) {
    // Contador de vertices visitados, para detectar ciclos
    int visited_vertices = 0;

    // Número de vértices no grafo
    int vertices_n = agnnodes(g);

    // Vetor para armazenar o grau de entrada de cada vértice
    vector<int> in_degree(vertices_n, 0);

    // Fila para armazenar os vértices com grau de entrada 0
    queue<Agnode_t *> q;

    // Calcula o grau de entrada de cada vértice
    for (Agnode_t *n = agfstnode(g); n; n = agnxtnode(g, n)) {
        in_degree[AGSEQ(n)-1] = agdegree(g, n, true, false);
        if (in_degree[AGSEQ(n)-1] == 0)
            q.push(n);
    }

    // Vetor para armazenar a ordenação topológica
    vector<char *> top_order;

    Agnode_t *u;
    Agnode_t *v;
    Agedge_t *e;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        top_order.push_back(agnameof(u));

        for (e = agfstout(g, u); e; e = agnxtout(g, e)) {
            v = aghead(e);
            if (--in_degree[AGSEQ(v)-1] == 0)
                q.push(v);
        }

        visited_vertices++;
    }

    // Verifica se existe um ciclo no grafo a partir do número de vértices visitados e o numero de vertices no grafo
    if (visited_vertices != vertices_n) {
        cout << "Error: Graph contains a cycle." << endl;
        return;
    }

    size_t i = 0;
    for (; i < top_order.size() - 1; i++)
        cout << top_order[i] << ", ";
    cout << top_order[i];
}

int main() {
    Agraph_t *g = agread(stdin, NULL);

    if (g == NULL) {
        cerr << "Error: Could not read graph." << endl;
        return EXIT_FAILURE;
    }

    if(agisdirected(g) == 0){
        cerr << "Error: Graph is not directed." << endl;
        return EXIT_FAILURE;
    }

    topologicalSort(g);
    agclose(g);

    return 0;
}
