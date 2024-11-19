#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
#include <string>
using namespace std;

vector<vector<int>> floyd_warshall(int vertices, int verticeInicial, vector<vector<int>> &grafo)
{
    vector<vector<int>> dist = grafo;

    for (int i = 0; i < vertices; i++)
    {
        dist[i][i] = 0;
    }
    if (verticeInicial != 0)
    {
        dist[verticeInicial][verticeInicial] = 0;
    }

    for (int j = 0; j < vertices; j++)
    {
        for (int k = 0; k < vertices; k++)
        {
            if (dist[k][j] == INT_MAX)
            {
                continue;
            }
            for (int l = 0; l < vertices; l++)
            {
                if (dist[j][l] != INT_MAX && k != l)
                {
                    dist[k][l] = min(dist[k][l], dist[k][j] + dist[j][l]);
                }
            }
        }
    }

    return dist;
}

int main(int argc, char *argv[])
{
    string arquivoEntrada = "";
    string arquivoSaida = "";

    int verticeInicial = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Uso: ./floyd-warshall.bin [opções]" << endl;
            cout << "Opções:" << endl;
            cout << "  -h                : Mostra ajuda" << endl;
            cout << "  -o <arquivo>      : Redireciona a saída para o 'arquivo'" << endl;
            cout << "  -f <arquivo>      : Indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "  -i <vértice>      : Vértice inicial para calcular os caminhos mínimos" << endl;
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
        else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc)
        {
            verticeInicial = atoi(argv[i + 1]) - 1;
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

    int Vertice, Aresta;

    fileEntrada >> Vertice >> Aresta;

    vector<vector<int>> grafo(Vertice, vector<int>(Vertice, INT_MAX));
    {
        for (int i = 0; i < Vertice; i++)
            grafo[i][i] = 0;
    }
    for (int i = 0; i < Aresta; i++)
    {
        int u, v, peso;
        fileEntrada >> u >> v >> peso;
        grafo[u - 1][v - 1] = peso;
        grafo[v - 1][u - 1] = peso;
    }

    fileEntrada.close();

    vector<vector<int>> dist = floyd_warshall(Vertice, verticeInicial, grafo);

       ostream* out;
    ofstream arquivoOut;
    if (!arquivoSaida.empty()) {
        arquivoOut.open(arquivoSaida);
        if (!arquivoOut) {
            cout << "Erro ao abrir o arquivo de saída.\n";
            return 1;
        }
        out = &arquivoOut;
    } else {
        out = &cout;
    }

    // Saída dos resultados
    if (verticeInicial < 0 || verticeInicial >= Vertice) {
        cout << "Vértice inicial inválido.\n";
        return 1;
    }

    for (int i = 0; i < Vertice; i++) {
        *out << i + 1 << ":" << dist[verticeInicial][i] << " ";
    }
    *out << endl;

    if (arquivoOut.is_open()) {
        arquivoOut.close();
    }

    return 0;
}