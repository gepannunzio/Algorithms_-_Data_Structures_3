#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

int hayMenor(int index,vector<int> opt, int constraint){
    for (int k = index; k >= 0; k--){
        if (opt[k] <= constraint){
            return k;
        }
    }
    return -1;
}

void fishburn (vector<tuple<int,int,int>> ineq, vector<int> opt, int n){
    vector<int> val(n, opt.back());
    vector<int> index(n, opt.size());
    bool changed = true;
    while(changed){
        changed = false;
        for (auto [a,b,c] : ineq) {
            int dk = hayMenor(index[a-1] - 1,opt, val[b-1] + c);
            if (val[a-1] > val[b-1] + c && dk >= 0){
                val[a-1] = opt[dk];
                index[a-1] = dk + 1;
                changed = true;
            }
        }
    }
    for (auto & [a,b,c] : ineq){
        if (val[a - 1] > val[b - 1] + c){
            cout << "insatisfactible" << endl;
            return;
        }
    }
    for(int i : index){
        cout << i << " " ;
    }
    cout << endl;
}



int main() {
    int t, k, n, m, a, b, c;
    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> k >> n >> m;
        vector<tuple<int,int,int>> ineq;
        for(int j = 0; j < k; j++){
            cin >> a >> b >> c;
            ineq.emplace_back(a,b,c);
        }
        vector<int> d;
        for(int v = 0; v < m; v++){
            int p;
            cin >> p;
            d.push_back(p);
        }
        fishburn(ineq, d, n);
    }
}
