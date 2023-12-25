#include <iostream>
#include <vector>
using namespace std;

using Matriz = vector<vector<int>>;
Matriz M;
vector<pair<int, int>> vPosCheck(4);
vector<int> vValCheck(4);

vector<pair<int, int>> posicionesDisponibles(Matriz& m, int i, int j){
    vector<pair<int, int>> dispo;
    if (i + 1 < m.size() && m[i+1][j] == -1){
        dispo.emplace_back(i+1, j);
    }
    if (i - 1 >= 0 && m[i-1][j] == -1){
        dispo.emplace_back(i-1, j);
    }
    if (j + 1 < m[0].size() && m[i][j+1] == -1){
        dispo.emplace_back(i, j+1);
    }
    if (j - 1 >= 0 && m[i][j-1] == -1){
        dispo.emplace_back(i, j-1);
    }
    return dispo;
}

int distManhattan(int i, int j, pair<int, int> p){
    return abs(i - p.first) + abs(j - p.second);
}

int robotsOnIce(int i, int j, int celda) {
    for (int k = 0 ; k < vValCheck.size() ; k++){   /// Por cada valor de los checkpoints
        if (celda == vValCheck[k] and make_pair(i, j) != vPosCheck[k]) { /// Disconcordancia entre val y pos
            return 0;
        }
        if (make_pair(i,j) == vPosCheck[k] and celda != vValCheck[k]){ /// Disconcordancia entre pos y val
            return 0;
        }
        /// Distancia Manhattan entre los prox checkpoints y (i,j) suficientes min casilleros disponibles
        if (celda < vValCheck[k] and distManhattan(i, j, vPosCheck[k]) > abs(vValCheck[k] - celda)){
            return 0;
        }
    }
    if (celda == M.size() * M[0].size() and make_pair(i,j) == vPosCheck.back()){ /// Meta
        return 1;
    }
    vector<pair<int,int>> dispo = posicionesDisponibles(M, i, j);
    if (dispo.empty()){
        return 0;
    }
    if (dispo.size() == 2){ /// Caso de una encrucijada con dos opciones opuestas
        pair<int,int> x = dispo[0];
        pair<int,int> y = dispo[1];
        if (abs(x.first - y.first) == 2 and x.second == y.second){
            return 0;
        }
        if (x.first == y.first and abs(x.second - y.second) == 2) {
            return 0;
        }
    }
    int sum = 0;
    for(auto& k : dispo){
        M[k.first][k.second] = celda+1;
        sum += robotsOnIce(k.first, k.second, celda+1);
        M[k.first][k.second] = -1;
    }
    return sum;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 1, m = 1, i = 1;
    while (n != 0 && m != 0) {
        cin >> n >> m;
        if (n == 0 && m == 0){
            break;
        }
        M = Matriz(n, vector<int>(m, -1));
        M[0][0] = 1;
        for (int t = 0; t < vPosCheck.size()-1; t++) {
            int x, y;
            cin >> x >> y;
            vPosCheck[t] = make_pair(x, y);
            vValCheck[t] = ((t + 1) * n * m) / 4;
        }
        vPosCheck[3] = {0,1};
        vValCheck[3] = n*m;
        int res = robotsOnIce(0, 0, 1);
        cout << "Case "<< i << ": " << res << endl;
        i++;
    }
    return 0;
}
