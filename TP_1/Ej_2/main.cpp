#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int wateringGrass( vector<pair<double, double>> alcance, int l){
    int counter = 0;
    int i = 0;
    double j = 0;
    while(j < l){
        pair<double, double> optimo = make_pair(j,INT32_MIN);
        bool found = false;
        while (i < alcance.size() && alcance[i].first <= j){
            if (optimo.second < alcance[i].second){
                optimo = alcance[i];
                found = true;
            }
            i++;
        }
        if (found) {
            counter++;
            j = optimo.second;
        } else {
            return -1;
        }
    }
    return counter;
}

vector<pair<double, double>> aux(vector<pair<int, int>>& sprayers, double w){
    vector<pair<double, double>> res;
    for(pair<int, int>& sprayer : sprayers){
        if (w < 2 * sprayer.second){
            double lowerBound = sprayer.first - sqrt((double)sprayer.second*sprayer.second - w/2 * w/2);
            double upperBound = sprayer.first + sqrt((double)sprayer.second*sprayer.second - w/2 * w/2);
            res.emplace_back(lowerBound, upperBound);
        }
    }
    sort(res.begin(), res.end());
    return res;
}



int main() {
    int n, l, w;
    while(cin >> n >> l >> w){
        vector<pair<int, int>> sprayers = {};
        for (int i = 0; i < n; i++) {
            int pos, r;
            cin >> pos >> r;
            sprayers.emplace_back(pos, r);
        }
        vector<pair<double, double>> alcance = aux(sprayers, w);
        cout << wateringGrass(alcance, l) << endl;
    }
    return 0;
}
