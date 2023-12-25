#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

using neigh = pair<int,int>; //vecino, costo
using graph = vector<vector<neigh>>;
using bridge = tuple<int,int,int>; //costo, v, w

const int none = -1;
const int inf = 9999999;

vector<int> dijkstra(graph& G, int n, int r){
    vector<int> T(n, none), D(n,inf);
    T[r] = r;
    D[r] = 0;
    priority_queue <bridge> S;
    for (auto x: G[r]) S.push({-x.second, r, x.first});
    while (not S.empty()) {
        int c, v, w;
        tie(c, v, w) = S.top();
        S.pop();
        if (T[w] == none) {
            T[w] = v;
            D[w] = -c;
            for (auto x: G[w]) {
                if (T[x.first] == none) {
                    S.push({c - x.second, w, x.first});
                }
            }
        }
    }
    return D;
}

int main() {
    int tests, v, c, box, p, r;
    cin >> tests;
    for (int i = 1 ; i <= tests ; i++){
        cin >> box >> p;
        graph G(p+1);
        vector<neigh> neighIn;
        for (int w = 0 ; w <= p ; w++){
            cin >> r;
            for (int k = 0 ; k < r ; k++){
                (w == 0) ? cin >> v : cin >> c >> v;
                (w == 0) ? G[w].emplace_back(v,0) : G[w].emplace_back(v,c);
                if (v == 0){
                    neighIn.emplace_back(w,c);
                }
            }
        }
        vector<int> D = dijkstra(G,p+1,0);
        int minCycleSize = inf;
        for (auto [w,c] : neighIn){
            minCycleSize = min(minCycleSize,D[w]+c);
        }
//        int result = 0;
//        int original = minCycleSize;
//        while (minCycleSize < box){
//            result++;
//            minCycleSize += original - 1;
//        }
        int result = 1 + (box-minCycleSize) / (minCycleSize-1) - ((box-minCycleSize) % (minCycleSize-1) == 0);
        if (minCycleSize == inf or minCycleSize > box) result = 0;
        cout << result << endl;
    }
    return 0;
}
