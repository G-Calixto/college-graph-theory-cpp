#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
#include <string>
using namespace std;


vector<pair<int, int>> prim(vector<vector<pair<int, int>>> adj, int vertice, int vertice_inicial, int &sum)
{
    vector <bool> visited(vertice + 1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila_prioridade_min;
    vector<int> caminho_minimo(vertice + 1, INT_MAX);
    vector<int> prev(vertice + 1, -1);
    vector<pair<int, int>> resultado;

    fila_prioridade_min.push({0, vertice_inicial});

    while (!fila_prioridade_min.empty())
    {
        int u = fila_prioridade_min.top().second;
        fila_prioridade_min.pop();
        visited[u] = true;

        for (auto p : adj[u])
        {
            int v = p.first;
            int w = p.second;

            if (!visited[v] && w < caminho_minimo[v])
            {
                prev[v] = u;
                caminho_minimo[v] = w;
                fila_prioridade_min.push({w, v});
            }
        }
    }
    for (int i = 1; i <= vertice; i++)
    {
        if (prev[i] != -1)
        {
            resultado.push_back({i, prev[i]});
            sum += caminho_minimo[i];
        }
    }
    return resultado;
}

int main(int argc, char const *argv[])
{
    int Vertice, Aresta = 0;
    int Vertice_inicial = 1;
    bool solution = false;
    int sum = 0;

    string arquivoEntrada = "";
    string arquivoSaida = "";
    
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Help: -h " << endl;
            cout << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
            cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
            cout << "-s : mostra a solução" << endl;
            cout << "-i : vértice inicial (para o algoritmo de Prim)" << endl;
            return 0;

        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        {
            arquivoSaida = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        {
            arquivoEntrada = argv[i + 1];
            i++;
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            solution = true;
        }
        else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc)
        {
            Vertice_inicial = atoi(argv[i + 1]);
            i++;
        }
    }

    if (arquivoEntrada == "")
    {
        cerr << "Nenhum arquivo de entrada especificado, use -f para especificar o arquivo de entrada" << endl;
        return EXIT_FAILURE;
    }

    ifstream fileEntrada(arquivoEntrada);
    if (!fileEntrada.is_open())
    {
        cerr << "Não foi possível abrir o arquivo de entrada" << endl;
        return EXIT_FAILURE;
    }

    fileEntrada >> Vertice >> Aresta;

    vector<vector<pair<int, int>>> grafo(Vertice + 1);
    for (int i = 0; i < Aresta; i++)
    {
        int u, v, w;
        fileEntrada >> u >> v >> w;
        grafo[u].push_back({v, w});
        grafo[v].push_back({u, w});
    }

    fileEntrada.close();

    vector<pair<int, int>> res = prim(grafo, Vertice, Vertice_inicial, sum);
    if (arquivoSaida != "")
    {
        ofstream fileSaida(arquivoSaida);
        if (!fileSaida)
        {
            cerr << "Could not open arquivoSaida file" << endl;
            return EXIT_FAILURE;
        }
        if (solution)
        {
            for (auto p : res)
            {
                fileSaida << "(" << p.first << "," << p.second << ") " << endl;
            }
        }
        else
        {
            fileSaida << sum << endl;
        }
        fileSaida.close();
    }
    else
    {
        if (solution)
        {
            for (auto p : res)
            {
                cout << "(" << p.first << "," << p.second << ") " << endl;
            }
        }
        else
        {
            cout << sum << endl;
        }
    }
    return 0;
}