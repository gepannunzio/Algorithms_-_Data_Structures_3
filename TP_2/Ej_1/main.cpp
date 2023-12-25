#include <iostream>
#include <vector>
#include <stack>
using namespace std;


//DETECCIÓN DE PUENTES made by Pablo Terlisky
int bridges(const vector<vector<int>>& ady, int source, const vector<int>& time_in, const vector<int>& parents, vector<bool>& puente_con_parent) {
    int cantidad = 0;
    for (int u : ady[source]) {
        if (parents[u] == source) {
            cantidad += bridges(ady, u, time_in, parents, puente_con_parent);
        } else {
            if (time_in[source] > time_in[u] and parents[source] != u) { //(source,u) es backedge que sube
                cantidad++;
            }
            if (time_in[source] < time_in[u]) { //(source,u) es backedge que viene de abajo
                cantidad--;
            }
        }
    }
    if (cantidad == 0 and parents[source] != source) {
        puente_con_parent[source] = true;
    }
    return cantidad;
}

void dfs(vector<vector<int>>& adj, vector<int>& parent, vector<int>& time_in, int source, int &current_time){
    stack<int> pila; pila.push(source);
    while (!pila.empty()) {
        int u = pila.top();
        pila.pop();
        time_in[u] = current_time;
        for (int w : adj[u]) {
            if (parent[w] == -1) {
                pila.push(w);
                parent[w] = u;
            }
        }
        current_time++;
    }
}

void dfs_simple(vector<vector<int>>& adj, vector<int>& componente,int source,int label){
    stack<int> pila; pila.push(source);
    while (!pila.empty()) {
        int u = pila.top();
        pila.pop();
        componente[u] = label;
        for (int w : adj[u]) {
            if (componente[w] == -1) {
                pila.push(w);
            }
        }
    }
}

int main() {
    int n, C, Q, v, w;
    while (cin >> n >> C >> Q){
        if (n == 0 and C == 0 and Q == 0) {
            break;
        }
        vector<vector<int>> adj(n+1);
        vector<vector<int>> bridgeGraph(n+1);
        vector<int> parent(n+1,-1), time_in(n+1);
        vector<bool> puente_con_parent(n+1,false);
        for (int i = 1 ; i <= C ; i++){
            cin >> v >> w;
            adj[v].push_back(w);
            adj[w].push_back(v);
        }
        int current_time = 0;
        for (int v = 1 ; v <= n ; v++){
            if (parent[v] == -1){
                parent[v] = v; // raiz de un arbol
                dfs(adj,parent,time_in,v,current_time);
                bridges(adj,v,time_in,parent,puente_con_parent);
            }
        }
        for (int v = 1 ; v <= n ; v++){
            if (puente_con_parent[v]){
                w = parent[v];
                bridgeGraph[v].push_back(w);
                bridgeGraph[w].push_back(v);
            }
        }
        vector<int> componente(n+1,-1);
        int label = 1;
        for (int v = 1 ; v <= n ; v++){
            if (componente[v] == -1){
                dfs_simple(bridgeGraph,componente,v,label);
                label++;
            }
        }
        for (int i = 1 ; i <= Q ; i++){
            cin >> v >> w;
            cout << ((componente[v] == componente[w]) ? "Y" : "N") << endl;
        }
        cout << "-" << endl;
    }
    return 0;
}
