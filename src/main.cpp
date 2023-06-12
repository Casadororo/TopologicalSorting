#include <bits/stdc++.h>
#include <graphviz/gvc.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Ordenação topológica usando algoritmo de Kahn
void topologicalSort(Agraph_t *g) {
    int vertices_n = agnnodes(g);

    // Vetor para armazenar o grau de entrada de cada vértice
    vector<int> in_degree(vertices_n, 0);

    // Fila para armazenar os vértices com grau de entrada 0
    queue<Agnode_t *> q;

    // Calcula o grau de entrada de cada vértice
    for (Agnode_t *n = agfstnode(g); n; n = agnxtnode(g, n)) {
        in_degree[AGSEQ(n)] = agdegree(g, n, true, false);
        cout << agnameof(n) << " " << in_degree[AGSEQ(n)] << endl;
        if (in_degree[AGSEQ(n)] == 0)
            q.push(n);
    }

    // Contador de vertices visitados, para detectar ciclos
    int visited_vertices = 0;

    // Vetor para armazenar a ordenação topológica
    vector<char *> top_order;

    cout << endl;

    Agnode_t *u;
    while (!q.empty()) {
        u = q.front();
        cout << agnameof(u) << " " << in_degree[AGSEQ(u)] << endl;
        q.pop();
        top_order.push_back(agnameof(u));

        Agedge_t *e;
        for(e = agfstout(g, u); e; e = agnxtout(g, e)){
            Agnode_t *v = aghead(e);
            if (--in_degree[AGSEQ(v)] == 0)
                q.push(v);
        }

        visited_vertices++;
    }

    if (visited_vertices != vertices_n) {
        cout << "There exists a cycle in the graph\n";
        return;
    }

    cout << "(";
    size_t i = 0;
    for (; i < top_order.size() - 1; i++)
        cout << top_order[i] << ", ";
    cout << top_order[i] << ")" << endl;
}

// Driver program to test above functions
int main() {

    GVC_t *gvc = gvContext();
    Agraph_t *g = agread(stdin, NULL);
    if (g == NULL) {
        fprintf(stderr, "Error: Could not read graph.\n");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen("test/image2.png", "wb");

    gvLayout(gvc, g, "dot");
    gvRender(gvc, g, "png", fp);
    gvFreeLayout(gvc, g);

    cout << "Following is a Topological Sort of\n";
    topologicalSort(g);
    agclose(g);

    return 0;
}