/**
 * 最简单的情况，求一位数组的子数组和最大值
 */
int maxSum(vector<int> ls)
{
    if (ls.empty()) {
        // 出错提示
        return 0;
    }
    int maxsum = ls[0], sum = ls[0];
    for (int i = 1; i < ls.size(); ++i) {
        sum = max(ls[i], ls[i] + sum);
        maxsum = max(maxsum, sum);
    }
    return maxsum;
}

/**
 *  一维数组首尾相连的情况，可以设定两个条件
 *  1）总长度不能超过数组长度；
 *  2）循环次数不超过两倍数组长度。
 */
int maxSum(vector<int> ls)
{
    if (ls.empty()) return 0;
    int maxsum = ls[0], sum = ls[0], maxlen = 1;
    for (int i = 1; maxlen <= ls.size() && i < ls.size() * 2; ++i) {
        if (sum > 0) {
            sum += ls[i % ls.size()];
            ++maxlen;
        } else {
            sum = ls[i % ls.size()];
            maxlen = 1;
        }
        maxsum = max(maxsum, sum);
    }
    return maxsum;
}

/**
 *  二维数组子数组和最大值
 *  二维数组需要先进行预处理再计算
 */
int maxSum(vector<vector<int>> ls)
{
    if (ls.empty()) return 0;
    vector<vector<int>> sums(ls.size(), vector<int>(ls[0].size()));
    // 不同于书上的预处理方式，处理和计算比较方便
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = 0; j < ls[0].size(); ++j) {
            if (i == 0) {
                sums[i][j] = ls[i][j];
            } else {
                sums[i][j] = sums[i - 1][j] + ls[i][j];
            }
        }
    }
    int maxsum = INT_MIN;
    // 计算最大值
    // 不妨设ls为一个长大于宽的矩形
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = i; j < ls.size(); ++j) {
            auto f = [i, j, &sums](int k)-> int {return i > 0 ? sums[j][k] - sums[i - 1][k] : sums[j][k]; };
            int sum = f(0);
            for (int k = 1; k < ls[0].size(); ++k) {
                sum = max(sum + f(k), f(k));
                maxsum = max(maxsum, sum);
            }
        }
    }
    return maxsum;
}

/**
 *  二维数组首尾相连的情况
 */
int maxSum(vector<vector<int>> ls)
{
    if (ls.empty()) return 0;
    vector<vector<int>> sums(ls.size(), vector<int>(ls[0].size()));
    // 不同于书上的预处理方式，处理和计算比较方便
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = 0; j < ls[0].size(); ++j) {
            if (i == 0) {
                sums[i][j] = ls[i][j];
            } else {
                sums[i][j] = sums[i - 1][j] + ls[i][j];
            }
        }
    }
    int maxsum = INT_MIN;
    // 计算最大值
    // 不妨设ls为一个长大于宽的矩形
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = i; j < ls.size(); ++j) {
            auto f = [i, j, &sums](int k)-> int {return i > 0 ? sums[j][k] - sums[i - 1][k] : sums[j][k]; };
            int sum = f(0), maxlen = 1;
            for (int k = 1; maxlen <= ls[0].size() && k < ls[0].size() * 2; ++k) {
                if (sum >= 0) {
                    sum += f(k % ls[0].size());
                    ++maxlen;
                } else {
                    sum = f(k % ls[0].size());
                    maxlen = 1;
                }
                maxsum = max(maxsum, sum);
            }
        }
    }
    return maxsum;
}


/**
 *  二维数组连成游泳圈的情况
 */
int maxSum(vector<vector<int>> ls)
{
    if (ls.empty()) return 0;
    vector<vector<int>> sums(ls.size(), vector<int>(ls[0].size()));
    // 不同于书上的预处理方式，处理和计算比较方便
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = 0; j < ls[0].size(); ++j) {
            if (i == 0) {
                sums[i][j] = ls[i][j];
            } else {
                sums[i][j] = sums[i - 1][j] + ls[i][j];
            }
        }
    }
    int maxsum = INT_MIN;
    // 计算最大值
    // 不妨设ls为一个长大于宽的矩形
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = i; j < ls.size(); ++j) {
            auto f = [i, j, &sums](int k)-> int {return i > 0 ? sums[j][k] - sums[i - 1][k] : sums[j][k]; };
            int sum = f(0), maxlen = 1;
            for (int k = 1; maxlen <= ls[0].size() && k < ls[0].size() * 2; ++k) {
                if (sum >= 0) {
                    sum += f(k);
                    ++maxlen;
                } else {
                    sum = f(k);
                    maxlen = 1;
                }
                maxsum = max(maxsum, sum);
            }
        }
    }
    return maxsum;
}