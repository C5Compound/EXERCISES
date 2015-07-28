#include <vector>
#include <string>
#include <iostream>
using namespace std;
/**
 *  1.全排列
 *  2.去重复全排列
 *  3.mancher实现求最大回文字串
 *  4.求一个0和1组成的矩阵中由1组成的最大的X(十)
 *  5.判断点是否在凸包内，极角二分法
 *  6.求包围点集的最小凸包
 *  7.树的序列和反序列化
 */

// 全排列,深搜实现
class Permutation 
{
public:
    vector<string> result;
    vector<string> getPermutation(string s) 
    {
        if (s.empty()) {
            return result;
        }
        vector<bool> visited(s.size(), false);
        string r;
        DFS(s, r, s.size(), visited);
        return result;
    }
    void DFS(string &s, string &r, size_t count, vector<bool> &visited) 
    {
        if (count == 0) {
            result.push_back(r);
            return;
        }
        for (size_t i = 0; i < s.size(); ++i) {
            if (!visited[i]) {
                r.push_back(s[i]);
                visited[i] = true;
                --count;
                DFS(s, r, count, visited);
                ++count;
                visited[i] = false;
                r.pop_back();
            }
        }
    }
};

// 去重全排列，通过交换元素实现
class Permutation_NO_Dup
{
public:
    vector<string> getPermutation(string s) 
    {
        vector<string> result;
        if (s.empty()) {
            return result;
        }
        SwapChar(s, 0, result);
        return result;
    }
    // 去重，如果两者相等或者中间有和J相等的字符则不交换
    bool isLegal(string &s, size_t i, size_t j)
    {
        for (;i < j; ++i) {
            if (s[i] == s[j]) {
                return false;
            }
        }
        return true;
    }
    void SwapChar(string s, size_t i, vector<string> &result) 
    {
        if (i == s.size() - 1) {
            result.push_back(s);
            return;
        }
        auto swap = [&](size_t i, size_t j){char c = s[j]; s[j] = s[i]; s[i] = c;};
        for (size_t j = i; j < s.size(); ++j) {
            if (isLegal(s, i, j)) {
                swap(i, j);
                SwapChar(s, i + 1, result);
                swap(i, j);
            }
        }
    }
};

// 最大回文字串
string manancher(string s) 
{
    // 合法性判断
    if (s.size() < 2) {
        return s;
    }
    // 插入#号，使回文长度都变成奇数
    string ssharp(2 * s.size() + 1, '#');
    for (int i = 0; i < s.size(); ++i) {
        ssharp[2 * i + 1] = s[i];
    }
    ssharp[0] = '$';
    ssharp[ssharp.size() - 1] = '@';
    vector<int> raid(ssharp.size());
    for (int i = 1, j = 0, k; i < ssharp.size();) {
        while (/*i + j < ss.size() &&　i - j >= 0 && */ssharp[i + j] == ssharp[i - j]) {
            ++j;
        }
        raid[i] = j;
        for (k = 1; k < j && raid[i - k] != raid[i] - k; ++k) {
            raid[i + k] = min(raid[i - k], raid[i] - k);
            i += k;
            j = max(j - k, 0);
        }
    }
    int max_raid = 0, index;
    for (int i = 1; i < ssharp.size(); ++i) {
        if (raid[i] > max_raid) {
            max_raid = raid[i];
            index = i;
        }
    }
    string r;
    for (int i = index - max_raid; i <= index + max_raid; ++i) {
        if (ssharp[i] != '#') {
            r.push_back(ssharp[i]);
        }
    }
    return r;
}

// 扫描以i为中心,j为半径的回文串,方法来自leetcode discuss
int minCut(string s) 
{
    if (s.size() < 2) {
        return 0;
    }
    vector<int> dp(s.size() + 1, s.size());
    // 一个避免进行边界检查的trick
    // 下面的dp索引整体右移了一位
    dp[0] = -1;
    for (int i = 0; i < s.size(); ++i) {
        // 回文字串大小为奇数的情况
        for (int j = 0; i + j < s.size() && i - j >= 0 && s[i + j] == s[i - j]; ++j) {
            dp[i + j + 1] = min(dp[i - j] + 1, dp[i + j + 1]);
        }
        // 回文字串大小为偶数的情况
        for (int j = 0; i + j + 1 < s.size() && i - j >= 0 && s[i + j + 1] == s[i - j]; ++j) {
            dp[i + j + 2] = min(dp[i - j] + 1, dp[i + j + 2]);
        }
    }
    return dp[s.size()];
}

// 最大的X
int maxX(vector<vector<int>> matrix)
{
    // matrix是否为空
    if (matrix.empty()) {
        return 0;
    }
    size_t size  = matrix.size();
    int dp[size][size][4] = {0};
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

        }
    }
}

// 判断点是否在凸包内
bool inPolygon()
{
    return false;
}

// 树的序列和反序列化
string treeSerialize()

int main() 
{
    Permutation_NO_Dup p;
    string s("1233");
    vector<string> vs = p.getPermutation(s);
    for (size_t i = 0; i < vs.size(); ++i) {
        cout << vs[i] << endl;
    }
    return 0;
}