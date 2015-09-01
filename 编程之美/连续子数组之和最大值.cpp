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
 *  一维数组首尾相连的情况，可以求出连续数组的最小值和最大值
 *  用数组所有元素的和减去最小值的结果和连续的最大值中较大者即为所求
 */
int maxSum(vector<int> ls)
{
    if (ls.empty()) return 0;
    int maxsum = ls[0], sum4max = ls[0], minsum = ls[0], sum4min = ls[0], sum = ls[0];
    for (int i = 1; i < ls.size(); ++i) {
        sum4max = max(ls[i], ls[i] + sum4max);
        maxsum = max(maxsum, sum4max);
        sum4min = min(ls[i], ls[i] + sum4min);
        minsum = min(minsum, sum4min);
        sum += ls[i];
    }
    return max(maxsum, sum - minsum);
}

/**
 *  连续子数组和的绝对值最大值,即取和最大值和最小值中绝对值较大的
 */
int maxSumAbs(vector<int> ls)
{
    if (ls.empty()) return 0;
    int maxsum = ls[0], sum4max = ls[0], minsum = ls[0], sum4min = ls[0], sum = ls[0];
    for (int i = 1; i < ls.size(); ++i) {
        sum4max = max(ls[i], ls[i] + sum4max);
        maxsum = max(maxsum, sum4max);
        sum4min = min(ls[i], ls[i] + sum4min);
        minsum = min(minsum, sum4min);
        sum += ls[i];
    }
    return max(abs(maxsum), abs(sum - minsum));
}

/**
 *  连续子数组和的绝对值最小值
 *  先求出数组的前缀数组，然后排序求出前缀数组之差的最小值
 *  复杂度为O(NlogN)
 */
int minSumAbs(vector<int> ls)
{
    if (ls.empty()) return 0;
    vector<int> prefix(ls.size() + 1, 0);
    for (int i = 0; i < ls.size(); ++i) {
        prefix[i + 1] = prefix[i] + ls[i];
    }
    sort(prefix.begin(), prefix.end(), less<int>());
    int minabs = INT_MAX;
    for (int i = 1; i < prefix.size(); ++i) {
        minabs = min(minabs, prefix[i] - prefix[i - 1]);
    }
    return minabs;
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
 *  二维数组首尾相连的情况，模仿一维数组首尾相接的情况
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
            }
            else {
                sums[i][j] = sums[i - 1][j] + ls[i][j];
            }
        }
    }
    int max_sub_sum = INT_MIN;
    // 计算最大值
    // 不妨设ls为一个长大于宽的矩形
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = i; j < ls.size(); ++j) {
            auto f = [i, j, &sums](int k)-> int {return i > 0 ? sums[j][k] - sums[i - 1][k] : sums[j][k]; };
            int maxsum = f(0), sum4max = f(0), minsum = f(0), sum4min = f(0), sum = f(0);
            for (int k = 1; k < ls[0].size(); ++k) {
                sum4max = max(f(k), f(k) + sum4max);
                maxsum = max(maxsum, sum4max);
                sum4min = min(f(k), f(k) + sum4min);
                minsum = min(minsum, sum4min);
                sum += f(k);
            }
            max_sub_sum = max(max_sub_sum, max(sum - minsum, maxsum));
        }
    }
    return max_sub_sum;
}

/**
 *  二维数组连成游泳圈的情况,考虑找出二维数组中的最小矩形，用和减去其即可
 */
int maxSum(vector<vector<int>> ls)
{
    if (ls.empty()) return 0;
    vector<vector<int>> sums(ls.size(), vector<int>(ls[0].size()));
    // 不同于书上的预处理方式，处理和计算比较方便
    int sum = 0, min_sub_sum = INT_MAX, max_sub_sum = INT_MIN;
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = 0; j < ls[0].size(); ++j) {
            sum += ls[i][j];
            if (i == 0) {
                sums[i][j] = ls[i][j];
            }
            else {
                sums[i][j] = sums[i - 1][j] + ls[i][j];
            }
        }
    }
    // 计算最大值
    // 不妨设ls为一个长大于宽的矩形
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = i; j < ls.size(); ++j) {
            auto f = [i, j, &sums](int k)-> int {return i > 0 ? sums[j][k] - sums[i - 1][k] : sums[j][k]; };
            int maxsum = f(0), sum4max = f(0), minsum = f(0), sum4min = f(0), tmpsum = f(0);
            for (int k = 1; k < ls[0].size(); ++k) {
                sum4max = max(f(k), f(k) + sum4max);
                maxsum = max(maxsum, sum4max);
                sum4min = min(f(k), f(k) + sum4min);
                minsum = min(minsum, sum4min);
                tmpsum += f(k);
            }
            min_sub_sum = min(min_sub_sum, min(tmpsum - maxsum, minsum));
            max_sub_sum = max(max_sub_sum, max(tmpsum - minsum, maxsum));
        }
    }
    return max(sum - min_sub_sum, max_sub_sum);
}

/**
 *  求三维长方体中和最大的长方体与求二维的方法类似，先确定其中两维，对于剩下的一维可以用一维的方法求
 */