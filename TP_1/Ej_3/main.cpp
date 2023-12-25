#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>
using namespace std;

vector<int> cost = {};

int wateringGrassMemo(vector<pair<double, double>> alcance, int l){
    vector<vector<int>> dp(alcance.size()+1,vector<int>(alcance.size()+1,999999999));
    function<int(int,int)> solver = [&](int i, int j) -> int{
        if (i == alcance.size()){
            return (alcance[j].second > l) ?  0 : 999999999;
        }
        if (dp[i][j] != 999999999){
            return dp[i][j];
        }
        if (alcance[i].first <= alcance[j].second) {
            dp[i][j] = min(solver(i+1,i) + cost[i], solver(i+1,j));
        } else {
            return 999999999;
        }
        return dp[i][j];
    };
    int result = solver(1,0);
    return (result == 999999999) ? -1 : result;
}

int wateringGrassBottomUp(vector<pair<double, double>> alcance, int l){
    vector<vector<int>> dp(alcance.size()+1,vector<int>(alcance.size()+1,999999999));

    for(int i = alcance.size(); i >= 0; i--){
        for(int j = i; j >= 0; j--){
            if (i == alcance.size()){
                dp[i][j] = (alcance[j].second > l) ? 0 : 999999999;
                continue;
            }
            if (alcance[i].first <= alcance[j].second) {
                dp[i][j] = min(dp[i + 1][i] + cost[i], dp[i + 1][j]);
            }
        }
    }
    return (dp[1][0] == 999999999) ? -1 : dp[1][0];
}

vector<pair<double, double>> aux(vector<pair<int, int>> sprayers, double w){
    vector<pair<double, double>> res;
    for(pair<int,int> & sprayer : sprayers){
            double lowerBound = sprayer.first - sqrt((double)sprayer.second*sprayer.second - w/2 * w/2);
            double upperBound = sprayer.first + sqrt((double)sprayer.second*sprayer.second - w/2 * w/2);
            res.emplace_back(lowerBound, upperBound);
    }
    res.emplace_back(INT32_MIN,0);
    cost.push_back(INT32_MAX);
    for (int i = 0 ; i < res.size() ; i++){
        for (int j = 0 ; j < res.size() ; j++){
            if (res[i] < res[j]){
                swap(res[i],res[j]);
                swap(cost[i],cost[j]);
            }
        }
    }
    return res;
}

int main() {
    int n, l, w;
    while(cin >> n >> l >> w){
        vector<pair<int, int>> sprayers = {};
        cost = {};
        for (int i = 0; i < n; i++) {
            int pos, r, c;
            cin >> pos >> r >> c;
            if (w < 2 * r){
                sprayers.emplace_back(pos, r);
                cost.push_back(c);
            }
        }
        vector<pair<double, double>> alcance = aux(sprayers, w);
        cout << wateringGrassMemo(alcance, l) << endl;
        //cout << wateringGrassBottomUp(alcance, l) << endl;
    }
    return 0;
}

