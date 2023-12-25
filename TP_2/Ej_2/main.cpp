#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using Costo = long int;
using Arista = pair<int,int>;

//Estructura Union-Find. Made by Francisco Soulignac
//Proporciona dos funciones: Unite y Find
struct UF {
    //vectores internos
    //  p: Vector con los parents
    //  s: Vector con tamaños
    vector<int> p;
    vector<int> s;

    //Constructor
    UF(int n): p(n, -1), s(n, 1) {}

    //unite: Hace la unión y devuelve el tamaño del resultante
    int unite(int v, int w) {
        v = find(v); w = find(w);
        if(v == w) return s[v];
        if(s[v] < s[w]) swap(v, w);
        p[w] = v; //El árbol de mayor tamaño queda como padre
        return s[v] += s[w];
    }
    //find: Devuelve el parent
    int find(int v) {
        return p[v] == -1 ? v : p[v] = find(p[v]); //Recursión para path compression
    }
    int size(int v){
        return s[v];
    }
};

int main() {
    int  test, n, m, u, v, c;
    cin >> test;
    for (; test >= 1 ; test--){
        cin >> n >> m;
        vector<pair<Costo,Arista>> E;
        vector<vector<int>> adyacenciasMin(n+1, vector<int> (n+1, 100000000));
        vector<vector<int>> adyacenciasMax(n+1, vector<int> (n+1, -100000000));
        vector<int> pesoMinComp(n+1, 10000000);
        for (int w = 1 ; w <= m ; w++){
            cin >> u >> v >> c;
            E.push_back({-c,{u,v}});
            adyacenciasMin[u][v] = c;
            adyacenciasMax[u][v] = c;
            adyacenciasMin[v][u] = c;
            adyacenciasMax[v][u] = c;
        }

        sort(E.begin(),E.end());
        UF componentes(n+1);
        int result = 0;
        for (int k = 0 ; k < E.size() ; k++) {
            auto [c,e] = E[k];
            auto [i,j] = e;
            if (componentes.find(i) != componentes.find(j)) {
                int x = componentes.find(i);
                int y = componentes.find(j);
                if (componentes.size(x) < componentes.size(y)) {
                    swap(x,y);
                }
                for(int l = 1; l < adyacenciasMax.size(); l++){
                    int p = componentes.find(l);
                    adyacenciasMax[x][p] = max(adyacenciasMax[x][p], adyacenciasMax[y][p]);
                    adyacenciasMax[p][x] = adyacenciasMax[x][p];
                    adyacenciasMin[x][p] = min(adyacenciasMin[x][p], adyacenciasMin[y][p]);
                    adyacenciasMin[p][x] = adyacenciasMin[x][p];
                }
                pesoMinComp[x] = min(pesoMinComp[x],min(pesoMinComp[y],adyacenciasMin[x][y]));
                componentes.unite(i,j);
                bool add = true;
                for(int t = 1; t < adyacenciasMax.size(); t++) {
                    int p = componentes.find(t);
                    if((p != x) && (adyacenciasMax[x][p] >= pesoMinComp[x])){
                        add = false;
                    }
                }
                result += componentes.size(x) * add;
            }
        }
        cout << result << endl;
    }
    return 0;
}
