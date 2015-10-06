#include <iostream>
#include <vector>
using namespace std;

// 0-1背包
int knapsack_of_01(vector<pair<int, int>> &jewels, int cap) {
    int dp[cap + 1];
    for (int i = 1; i <= cap; ++i) {
        for (int j = 0; j < jewels.size(); ++j) {
            if (jewels[j].first < i) {
                dp[i] = max(dp[i], dp[i - jewels[j].first] + jewels.second);
            }
        }
    }
    return dp[cap];
}

// 多重背包
int knapsack_multi(vector<pair<int, int>> &jewels, int cap) {
    
    return 0;
}

// 完全背包
int knapsack_complete(vector<pair<int, int>> &jewels, int cap) {

    return 0;
}

int main() {
    
    return 0;
}
