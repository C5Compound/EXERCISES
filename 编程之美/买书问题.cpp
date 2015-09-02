/*
 *   题目: 
 *   在节假日的时候，书店一般都会做促销活动。由于《哈利波特》系列相当畅销，店长决定通过促销活动来回馈读者。
 *   在销售的《哈利波特》平装本系列中，一共有五卷，用编号0, 1, 2, 3, 4来表示。假设每一卷单独销售均需要
 *   8欧元。如果读者一次购买不同的两卷，就可以扣除5%的费用，三卷则更多。假设具体折扣的情况如下：
 *   
 *   本数          折扣
 *   2             5%
 *   3             10%
 *   4             20%
 *   5             25%
 *   在一份订单中，根据购买的卷数以及本书，就会出现可以应用不同折扣规则的情况。但是，一本书只会应用一个
 *   折扣规则。比如，读者一共买了两本卷一，一本卷二。那么，可以享受到5%的折扣。另外一本卷一则不能享受折扣。
 *   如果有多种折扣，希望能够计算出的总额尽可能的低。要求根据这样的需求，设计出算法，能够计算出读者所购
 *   买一批书的最低价格。
 *
 *  这里给出搜索的方法和贪心算法，动态规划需要一个5维数组，如果问题规模变为K，则需要K维数组
 *  最后一个程序参考了http://xzknet.iteye.com/blog/273763的思路
 *  
 *  ※注意隐含的条件，即每次购买的书种类越多，折扣越高※
 */
const double discount[5] = {1.0, 0.95, 0.9, 0.8, 0.75};

/**
 *  穷搜方法，穷搜方法可以解决普遍问题，但是时间复杂度为指数
 */
double leastCost(vector<int> ls)
{
    sort(ls.begin(), ls.end(), greater<int>());
    double cost = DBL_MAX;
    for (int i = 0; i < ls.size(); ++i) {
        if (ls[i] > 0) {
            --ls[i];
            cost = min(cost, (i + 1) * discount[i] + leastCost(ls));
        } 
        else break;
    }
    // DBL_MAX / 2为充分大数
    return cost > DBL_MAX / 2 ? 0 : cost;
}

/**
 *  改进的贪心方法，适用于K = 5，discount数组如所示的情况，ls大小为5
 *  5 * dis5 + 3 * dis3 < 2 * 4 * dis4
 */
double leastCost(vector<int> ls)
{
    sort(ls.begin(), ls.end(), greater<int>());
    for (int i = 0; i < ls.size() - 1; ++i) {
        ls[i] = ls[i] - ls[i + 1];
    }
    int t = min(ls[4], ls[2]);
    ls[4] -= t;
    ls[2] -= t;
    // 书上这里有错
    ls[3] += 2 * t;
    double cost = 0;
    for (int i = 0; i < ls.size(); ++i) {
        cost += (i + 1) * ls[i] * discount[i];
    }
    return cost;
}

/** 
 *  贪心方法处理一般问题，K种书籍的情况
 *  贪心策略为：1）本次可选的最大种类数不小于下一次可选的最大种类
 *             2）如果1中的选择有两个，选择更好的一个
 *  存疑：如果  5 5 1 和 4 4 3 哪个更好呢？
 */
double leastCost(vector<int> ls, const vector<double> &discount)
{
    sort(ls.begin(), ls.end(), greater<int>());
    double cost = DBL_MAX;
//  TODO
}

/**
 *  N本书，K种书的最佳买法，先缩小问题规模，再剪枝
 *  dfs中剪枝的原则：1）先每次挑出多本，以后挑出的本数不能超过前面的最小值
 *                  2）挑书的次数越少越好，即不能超过最少次数
 */
double dfs(int upper_bound, int remains, const int k)
{
    if (remains <= k) {
        return remains * discount[remains - 1];
    }
    double cost = DBL_MAX;
    for (int i = upper_bound; i > 0; --i) {
        // 剪枝，最后剩余的本数不能超过i
        if (remains > 2 * k && 2 * i <= k) {
            break;
        }
        // 剪枝，次数不能超过最小值
        int times = remains / i + (remains % i ? 1 : 0);
        int times_limit = remains / k + (remains % k ? 1 : 0);
        if (times > times_limit) {
            break;
        }
        cost = min(cost, dfs(i, remains - i, k) + i * discount[i - 1]);
    }
    return cost;
}

double leastCost(int n, const int k)
{
    if (n <= 0) return 0;
    if (n <= k || n % k == 0) return n * discount[k - 1];
    double cost = 0;
    // 缩小问题规模到不超过 K * K - K + 1
    while (n % k + n / k >= k) {
        n -= k;
        cost += k * discount[k - 1];
    }
    cost += dfs(k, n, k);
    return cost;
}