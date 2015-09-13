/**
 *  12个工厂分布在一条东西向高速公路的两侧，工厂距离公路最西端的距离分别是0、4、5、10、12、18、27、30、31、38、39、47.
 *  在这12个工厂中选取3个原料供应厂，使得剩余工厂到最近的原料供应厂距离之和最短，问应该选哪三个厂 ？
 *
 *  动态规划问题
 *  从i到j中选择p个工厂的最短距离等于从i到k选择p - 1个工厂的加上从k到j选择一个工厂的距离最小值
 *  思路来自：http://blog.csdn.net/SunnyYoona/article/details/44016487
 */
vector<int> minDistance(vector<int> &ls, int facts)
{
    int n = ls.size(), A[n + 1][n + 1], B[n + 1][n + 1];
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            B[i][j] = minDisofOne(ls, i, j);
        }
    }
    for (int i = 1; i <= n; ++i) {
        A[i][1] = B[1][i];
        for (int j = 2; j <= i; ++j) {
            A[i][j] = INT_MAX;
            for (int k = j - 1; k < i; ++k) {
                int curmin = A[k][j - 1] + B[k + 1][j];
                if (curmin < A[i][j]) {
                    A[i][j] = curmin;
                    fac[i][j] = k;
                }
            }
        }
    }
    return A[n][count];
}

int minDisofOne(vector<int> &ls, int l, int r)
{
    if (l < r) {
        return -1;
    }
    int m = (l + r) / 2;
    int re = 0;
    for (int i = l; i <= r; ++i) {
        re += abs(ls[m] - ls[i]);
    }
    return re;
}