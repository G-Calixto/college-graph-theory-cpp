#include <bits/stdc++.h>
#define maximum INT_MAX
using namespace std;

void mostrarAjuda() {
    cout << "Uso: ./dijkstra [opções]\n";
    cout << "Opções:\n";
    cout << "  -h                : Mostra ajuda\n";
    cout << "  -o <arquivo>      : Redireciona a saída para o 'arquivo'\n";
    cout << "  -f <arquivo>      : Indica o 'arquivo' que contém o grafo de entrada\n";
    cout << "  -i <vértice>      : Vértice inicial para calcular os caminhos mínimos\n";
}


void dfs(int v, const vector<vector<int>>& adj, vector<bool>& visitado, stack<int>& pilha){
    visitado[v] = true;
    for (int u : adj[v]){
        if (!visitado[u]){
            dfs(u, adj, visitado, pilha);
        }
    }
    pilha.push(v);
}

void dfsT(int v, const vector<vector<int>>& adjT, vector<bool>& visitado, vector<int>& comp){
    visitado[v] = true;
    comp.push_back(v);
    for (int u : adjT[v]){
        if (!visitado[u]){
            dfsT(u, adjT, visitado, comp);
        }
    }
}


void kosaraju(const vector<vector<int>>& adj, const vector<vector<int>>& adjT, ofstream& output) {
    int n = adj.size();
    stack<int> pilha;
    vector<bool> visitado(n, false);

    for(int i = 0; i<n; i++){
        if(!visitado[i]){
            dfs(i, adj, visitado, pilha);
        }
    }

    fill(visitado.begin(), visitado.end(), false);
    vector<vector<int>> allComponents;

    while(!pilha.empty()) {
        int v = pilha.top();
        pilha.pop();

        if(!visitado[v]) {
            vector<int> componente;
            dfsT(v, adjT, visitado, componente);

        sort(componente.begin(), componente.end());
        allComponents.push_back(componente);
        }
    }
    // PARTE QUE ORDENA TUDO. TIRAR SE AUMENTAR MT COMPLEXIDADE
    sort(allComponents.begin(), allComponents.end(), [](const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
    });

    for (const auto& componente : allComponents) {
        for (int node : componente) {
            if (output.is_open()) {
                output << (node + 1) << " ";
            } else {
                cout << (node + 1) << " ";  
            }
        }
        if (output.is_open()) {
            output << endl; 
        } else {
            cout << endl;
        }


    }
}

int main(int argc, char *argv[]){
    string arquivoSaida, arquivoEntrada;
    int n, m, v1, v2;

    for(int i = 1; i< argc; i++){
        if(strcmp(argv[i], "-h") == 0){
            mostrarAjuda();
            return 0;
        }
        if(strcmp(argv[i], "-o") == 0){
            arquivoSaida = argv[++i];
        }
        if(strcmp(argv[i], "-f") == 0){
            arquivoEntrada = argv[++i];
        }
    }

    if (arquivoEntrada ==""){
        cout << "Arquivo não encontrado ou inexistente.\n";
        mostrarAjuda();
        return 0;
    }
    ifstream file(arquivoEntrada);
    if (!file){
        cout << "Arquivo de entrada ilegível ou inexistente.\n";
        mostrarAjuda();
        return 0;
    }

    file >> n >> m;
    vector<vector<int>> adj(n);
    vector<vector<int>> adjT(n);

    while(file >> v1 >> v2){
        adj[v1-1].push_back(v2-1);
        adjT[v2-1].push_back(v1-1);

    }

    file.close();

    ofstream output;
    if (!arquivoSaida.empty()) {
        output.open(arquivoSaida);
        if (!output.is_open()){
            cout << "Erro ao abrir o arquivo de saída: " << arquivoSaida << endl;
            return 0;
        }
    }


    kosaraju(adj, adjT, output);

    if (output.is_open()) {
        output.close();
    }

return 0;
}