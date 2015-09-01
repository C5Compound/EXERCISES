/**
 *  瓷砖覆盖问题，用1X2的瓷砖覆盖M X N的地面，有多少种方法
 *  状态压缩动态规划
 */
bool isFirstLintOK(int i, int cols)
{
    for (int k = 0; k < cols;) {
        if ((i >> k & 0x01) == 1) {
            if (k >= cols - 1 || (i >> (k + 1) & 0x01) == 0) {
                return false;
            }
            k += 2;
        } else {
            ++k;
        }
    }
    return true;
}
// j为上一行状态
// isFirstLintOK(i, cols)可以用isCompatible(i, maxState - 1, cols)代替
bool isCompatible(int i, int j, int cols)
{
    for (int k = 0; k < cols;) {
        if ((i >> k & 0x01) == 1) {
            if ((j >> k & 0x01) == 0) {
                ++k;
            } else if (k >= cols - 1 || (j >> (k + 1) & 0x01) == 0 || (i >> (k + 1) & 0x01) == 0) {
                return false;
            } else {
                k += 2;
            }
        } else if ((j >> k & 0x01) == 0) {
            return false;
        } else {
            ++k;
        }
    }
    return true;
}

long long layWays(int rows, int cols)
{
    if (cols <= 0 || rows <= 0) {
        return 0;
    }
    if (rows < cols) {
        swap(cols, rows);
    }
    int maxState = 2 << (cols - 1);
    long long dp[rows][maxState];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < maxState; ++i) {
        // 可被isCompatible替代
        if (isFirstLintOK(i, cols)) {
            dp[0][i] = 1;
        }
    }
    for (int i = 1; i < rows; ++i) {
        for (int j = 0; j < maxState; ++j) {
            for (int k = 0; k < maxState; ++k) {
                if (isCompatible(j, k, cols)) {
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }
    }
    return dp[rows - 1][maxState - 1];
}