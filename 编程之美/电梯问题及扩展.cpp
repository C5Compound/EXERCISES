/**
 *  每次电梯从一楼往上走时，我们只允许电梯停在其中的某一层。所有的乘客都从一楼上电梯，到达某楼层后，电梯
 *  停下来；所有乘客再从这里爬楼梯到自己的目的层。
 *  问：电梯停在哪一层，能够保证这次乘坐电梯的所有乘客爬楼梯的层数之和最少。
 */
// passenger数组索引对应到达该楼层的情况，0对应0层，闲置
int liftWorker(vector<int> &passengers)
{
    if (passengers.size() < 2) {
        return 1;
    }
    // N1代表该楼层以下的乘客数量，N3代表该楼层以上的乘客数量
    int N1 = 0, N2 = passengers[1], N3 = 0;
    for (int i = 2; i < passengers.size(); ++i) {
        N3 += passengers[i];
    }
    int bestFloor = 1;
    for (int i = 2; i < passengers.size(); ++i) {
        if (N3 > N1 + N2) {
            bestFloor = i;
            N1 += N2;
            N2 = passengers[i];
            N3 -= N2;
        }
        else break;
    }
    return bestFloor;
}

/**
 *  问题扩展1）：电梯可以停在K个楼层，应该停在哪几个楼层？
 *  电梯停在1到j楼层停了K-1次，在j + 1到n层停了1次，动态规划即可
 */
// 从第x层到y层最优停靠法需要走的楼层数
pair<int, int> liftWorker(vector<int> &passengers, int x, int y)
{
    int N1 = 0, N2 = passengers[x], N3 = 0, walkSum = 0;
    for (int i = x + 1; i <= y; ++i) {
        N3 += passengers[i];
        walkSum += passengers[i] * (i - x);
    }
    int bestfloor = x;
    for (int i = x + 1; i <= y; ++i) {
        if (N3 > N1 + N2) {
            bestfloor = i;
            walkSum -= N3 - (N1 + N2);
            N1 += N2;
            N2 = passengers[i];
            N3 -= N2;
        }
        else break;
    }
    return make_pair(walkSum, bestfloor);
}

vector<int> K_lift(vector<int> &passengers, int K)
{
    vector<int> re;
    // 边界情况处理
    if (passengers.size() <= K + 1) {
        for (int i = 1; i < passengers.size(); ++i) {
            re.push_back(i);
        }
    }
    int n = passengers.size(), A[n][n], Lift[n][n];
    pair<int, int> B[n][n];
    // 预处理
    for (int i = 1; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            B[i][j] = liftWorker(passengers, i, j);
        }
    }
    for (int i = 1; i < n; ++j) {
        A[i][1] = B[1][j];
        for (int j = 2; j <= i; ++j) {
            A[i][j] = INT_MAX;
            for (int q = j - 1; q < i; ++q) {
                int tmp = A[q][j - 1] + B[q + 1][i].first;
                if (tmp < A[i][j]) {
                    Lift[i][j] = q;
                    A[i][j] = tmp;
                }
            }
        }
    }
    // 结果输出
    for (int q = K, p = n - 1, tmp; q >= 1; --q) {
        tmp = Lift[p][q];
        re.push_back(B[tmp + 1][p].second);
        p = tmp;
    }
    return re;
}

/**
 *  问题扩展2）：工厂最短距离问题
 *  12个工厂分布在一条东西向高速公路的两侧，工厂距离公路最西端的距离分别是0、4、5、10、12、18、27、30、31、38、39、47.
 *  在这12个工厂中选取3个原料供应厂，使得剩余工厂到最近的原料供应厂距离之和最短，问应该选哪三个厂 ？
 *
 *  动态规划问题
 *  从i到j中选择p个工厂的最短距离等于从i到k选择p - 1个工厂的加上从k到j选择一个工厂的距离最小值
 */
int MinDistanceOfOne(vector<int> &ls, int l, int r)
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

vector<int> MinDistance(vector<int> &ls, int facts)
{
    int n = ls.size(), A[n + 1][n + 1], B[n + 1][n + 1], fac[n + 1][n + 1];
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            B[i][j] = MinDistanceOfOne(ls, i, j);
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
    // 结果输出
    vector<int> re;
    for (int q = facts, p = n, tmp; q >= 1; --q) {
        tmp = fact[p][q];
        re.push_back((tmp + 1 + p) / 2);
        p = tmp;
    }
    return re;
}
