#include <bits/stdc++.h>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdlib.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

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
        in_degree[AGSEQ(n)] = agdegree(g, n, true, false);
        if (in_degree[AGSEQ(n)] == 0)
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
            if (--in_degree[AGSEQ(v)] == 0)
                q.push(v);
        }

        visited_vertices++;
    }

    // Verifica se existe um ciclo no grafo a partir do número de vértices visitados e o numero de vertices no grafo
    if (visited_vertices != vertices_n) {
        cout << "Error: Graph contains a cycle." << endl;
        return;
    }

    for (size_t i = 0; i < top_order.size() - 1; i++)
        cout << top_order[i] << ", ";
    cout << top_order[i];
}

//Find a unique name for a file
fs::path uniqueName(const std::string &name) {
    fs::path possibleName{name};
    auto stem = possibleName.stem().string();
    auto ext = possibleName.extension().string();
    for (int i=1; fs::exists(possibleName); ++i) {
        std::ostringstream fn;
        fn << stem << i << ext;
        possibleName.replace_filename(fn.str());
    }
    return possibleName;
}

// Driver program to test above functions
int main() {
    GVC_t *gvc = gvContext();
    Agraph_t *g = agread(stdin, NULL);

    if (g == NULL) {
        cerr << "Error: Could not read graph." << endl;
        return EXIT_FAILURE;
    }

    if(agisdirected(g) == 0){
        cerr << "Error: Graph is not directed." << endl;
        return EXIT_FAILURE;
    }

    fs::path uniquePath = uniqueName("test/image.png");
    FILE *fp = fopen(uniquePath.c_str(), "wb");

    gvLayout(gvc, g, "dot");
    gvRender(gvc, g, "png", fp);
    gvFreeLayout(gvc, g);

    topologicalSort(g);
    agclose(g);

    return 0;
}