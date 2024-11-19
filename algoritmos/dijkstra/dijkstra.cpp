#include <bits/stdc++.h>
using namespace std;

#define maximum INT_MAX

void mostrarAjuda() {
    cout << "Uso: ./dijkstra.bin [opções]\n";
    cout << "Opções:\n";
    cout << "  -h                : Mostra ajuda\n";
    cout << "  -o <arquivo>      : Redireciona a saída para o 'arquivo'\n";
    cout << "  -f <arquivo>      : Indica o 'arquivo' que contém o grafo de entrada\n";
    cout << "  -i <vértice>      : Vértice inicial para calcular os caminhos mínimos\n";
}

vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int origem)
{
    vector<int> dist(adj.size(), maximum);
    dist[origem] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    fila.push(make_pair(0, origem));
    while (!fila.empty())
    {
        int v = fila.top().second;
        fila.pop();
        for (unsigned i = 0; i < adj[v].size(); i++)
        {
            int u = adj[v][i].first;
            int p = adj[v][i].second;
            if (dist[u] > dist[v] + p)
            {
                dist[u] = dist[v] + p;
                fila.push(make_pair(dist[u], u));
            }
        }
    }
      for (auto& d : dist) {
        if (d == maximum) d = -1;
    }
    
    return dist;
}

int main(int argc, char* argv[]){
    string arquivoEntrada, arquivoSaida;
    int n, m, w, v1, v2;
    int verticeInicial = 1;

    for (int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-h") == 0){
            mostrarAjuda();
            return 0;
        }
        if(strcmp(argv[i], "-o") == 0 && i+1 <argc){
            arquivoSaida = argv[++i];
        }
        if(strcmp(argv[i], "-f") == 0 && i+1 < argc){
            arquivoEntrada = argv[++i];
        }
        if(strcmp(argv[i], "-i") == 0 && i+1 <argc){
            verticeInicial = stoi(argv[++i]);
        }
    }
    
    if (arquivoEntrada.empty()){
        cout << "Nenhum arquivo de entrada selecionado.\n";
        mostrarAjuda();
        return 0;
    }
    ifstream file(arquivoEntrada);
    if(!file){
        cout << "Arquivo inexistente ou inacessível.\n";
        mostrarAjuda();
        return 0;
    }
    file >> n >> m;
    n++;
    vector<vector<pair<int,int>>> adj(n);
    for(int i = 0; i<m; i++){
        file >> v1 >> v2 >> w;
        adj[v1].push_back({v2,w});
        adj[v2].push_back({v1,w});
    }
    file.close();

    vector<int> dist = dijkstra(adj, verticeInicial);

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

    for (size_t i = 1; i < dist.size(); i++) {
        *out << i << ":" << dist[i] << " ";
    }
    *out << endl;

    if (arquivoOut.is_open()) {
        arquivoOut.close();
    }

    return 0;
}