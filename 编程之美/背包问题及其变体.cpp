#include <iostream>
#include <vector>
using namespace std;

// 0-1背包
int knapsack_of_01(vector<pair<int, int>> &jewels, int cap)
{
    vector<int> dp(cap + 1, 0);
    for (int i = 1; i <= jewels.size(); ++i) {
        for (int j = cap; j >= 1; --j) {
            if (jewels[i - 1].first <= j) {
                dp[j] = max(dp[j], dp[j - jewels[i - 1].first] + jewels[i - 1].second);
            }
        }
    }
    return dp[cap];
}

// 完全背包
int knapscak_complete(vector<pair<int, int>> &jewels, int cap)
{
    vector<int> dp(cap + 1, 0);
    for (int i = 1; i <= jewels.size(); ++i) {
        for (int j = 1; j <= cap; ++j) {
            if (jewels[i - 1].first <= j) {
                dp[j] = max(dp[j], dp[j - jewels[i - 1].first] + jewels[i - 1].second);
            }
        }
    }
    return dp[cap];
}

// 二进制优化的多重背包，可以单独写，也可以先转化为01背包，用上面的函数求解
int knapsack_multi(vector<pair<int, int>> &jewels, vector<int> &nums, int cap)
{
    vector<int> dp(cap + 1, 0);
    for (int i = 1; i <= jewels.size(); ++i) {
        for (int k = 1; k <= nums[i - 1]; k <<= 1) {
            for (int j = cap; j >= 1; --j) {
                if (jewels[i - 1].first * k <= j) {
                    dp[j] = max(dp[j], dp[j - jewels[i - 1].first * k] + jewels[i - 1].second * k);
                }
            }
        }
    }
    return dp[cap];
}
