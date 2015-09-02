/**
 *  问题：
 *  有一个没有排序、元素为2n的正整数组，要求：如何把这个数组分割为元素
 *  个数为n的连个数组，并使连个子数组的和最接近假定输入的数组是合法的，
 *  不包含负数，如果包含负数，可以通过整体加上一个数成为不含负数的数组
 */

 /**
  * 动态规划方法
  */
int arraySplit(vector<int> ls)
{
    if (ls.empty() || ls.size() % 2) {
        return -1;
    }
    int sum = 0;
    for (auto i : ls) sum += i;
    int cols = sum >> 1, rows = ls.size() >> 1;
    vector<vector<bool>> dp(rows + 1, vector<bool>(cols + 1, false));
    dp[0][0] = true;
    for (int k = 1; k <= ls.size(); ++k) {
        for (int i = 1; i <= k && i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                if (j >= ls[k - 1] && dp[i - 1][j - ls[k - 1]]) {
                    dp[i][j] = true;
                }
            }
        }
    }
    int re = cols;
    while (re >= 0 && !dp[rows][re]) --re;
    return re;
}

/**
 *  暴力穷举方法
 */
void dfs(vector<int> &ls, int k, int sum, int &answer, int total)
{
    if (k == ls.size() >> 1) {
        if (abs(sum - total) < abs(answer - total)) {
            answer = sum;
        }
        return;
    }
    for (int i = k; i < ls.size(); ++i) {
        swap(ls[i], ls[k]);
        dfs(ls, k + 1, sum + ls[k], answer, total);
        swap(ls[i], ls[k]);
    }
}

int arraySplit(vector<int> ls) 
{
    if (ls.empty() || ls.size() % 2) {
        return -1;
    }
    int total = 0;
    for (auto i : ls) total += i;
    total >>= 1;
    int answer = 0;
    dfs(ls, 0, 0, answer, total);
    return answer;
}