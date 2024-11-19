#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
using namespace std;

typedef pair<int, int> Edge;
typedef pair<int, Edge> WeightedEdge;

int find(int vertex, vector<int>& parent) {
    if (parent[vertex] != vertex) {
        parent[vertex] = find(parent[vertex], parent);
    }
    return parent[vertex];
}

void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = find(u, parent);
    int rootV = find(v, parent);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

int kruskal(int vertices, vector<WeightedEdge>& edges, vector<Edge>& result) {
    vector<int> parent(vertices + 1);
    vector<int> rank(vertices + 1, 0);
    for (int i = 1; i <= vertices; ++i) parent[i] = i;

    sort(edges.begin(), edges.end());

    int res = 0;
    for (auto& edge : edges) {
        int weight = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if (find(u, parent) != find(v, parent)) {
            unionSets(u, v, parent, rank);
            result.push_back({u, v});
            res += weight;
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    int vertices, edgesCount;
    string arquivoEntrada = "";
    string arquivoSaida = "";
    bool solution = false;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Help: -h : mostra o help" << endl;
            cout << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
            cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
            cout << "-s : mostra a solução" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            arquivoSaida = argv[i + 1];
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            arquivoEntrada = argv[i + 1];
        } else if (strcmp(argv[i], "-s") == 0) {
            solution = true;
        }
    }

    if (arquivoEntrada.empty()) {
        cerr << "Arquivo de entrada não especificado" << endl;
        return EXIT_FAILURE;
    }

    ifstream fileEntrada(arquivoEntrada);
    if (!fileEntrada) {
        cerr << "Não foi possível abrir o arquivo" << endl;
        return EXIT_FAILURE;
    }

    fileEntrada >> vertices >> edgesCount;

    vector<WeightedEdge> edges(edgesCount);

    for (int i = 0; i < edgesCount; ++i) {
        int u, v, weight;
        fileEntrada >> u >> v >> weight;
        edges[i] = {weight, {u, v}};
    }

    fileEntrada.close();

    vector<Edge> result;
    int res = kruskal(vertices, edges, result);

    if (!arquivoSaida.empty()) {
        ofstream fileSaida(arquivoSaida);
        if (!fileSaida) {
            cerr << "Não foi possível abrir o arquivo" << endl;
            return EXIT_FAILURE;
        }
        if (solution) {
            for (auto& p : result) {
                fileSaida << "(" << p.first << "," << p.second << ") " << endl;
            }
        } else {
            fileSaida << res << endl;
        }
        fileSaida.close();
    } else {
        if (solution) {
            for (auto& p : result) {
                cout << "(" << p.first << "," << p.second << ") " << endl;
            }
        } else {
            cout << res << endl;
        }
    }

    return 0;
}