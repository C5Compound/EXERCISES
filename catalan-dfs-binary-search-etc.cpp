/**
 *  1.序列通过加，乘和分割得到0
 *  2.n对括号合法状态
 *  3.绳子覆盖端点
 *  4.IP字符串转int
 *  5.各类二分搜索
 */

/**
 * 序列123...N，N介于3和9之间，在其中加入+、-或者空格，使其和为0。
 * 如123456  1-2 3-4 5+6 7 等价于1-23-45+67=0。请问，如何获得所有组合？
 * dfs
 */

void toZeroDfs(vector<string> &seqs, string seq, string &s, int n, int re)
{
    if (n == s.size()) {
        if (re == 0) {
            seqs.push_back(seq);
        }
        return;
    }
    for (int j = n + 1; j <= s.size(); ++j) {
        int i = atoi((s.substr(n, j - n)).c_str());
        toZeroDfs(seqs, seq + '+' + s.substr(n, j - n), s, j, re + i);
        toZeroDfs(seqs, seq + '-' + s.substr(n, j - n), s, j, re - i);
    }
}

/**
 *  n对括号合法放置方法
 *  catalan数, dfs
 */

void bracketDfs(string seq, int brcs, int left_brcs = 0, int right_brcs = 0)
{
    if (left_brcs < right_brcs) {
        return;
    }
    if (left_brcs + right_brcs == 2 * brcs) {
        if (left_brcs == brcs) {
            cout << seq << endl;
        }
        return;
    }
    bracketDfs(seq + '(', brcs, left_brcs + 1, right_brcs);
    bracketDfs(seq + ')', brcs, left_brcs, right_brcs + 1);
}

/**
 *  给定一系列x轴的点坐标，例如 1，3，7，8，9，11这些坐标升序放在数组中，
 *  现在给一根绳子，长度为4，问绳子最多能覆盖的点数有多少，例如绳子放前面只能覆盖两个点，1,3，如果放后面能覆盖4个点。
 *  可用dp，也可用双指针
 */

int coverDots(vector<int> pts, int len)
{
    if (pts.empty()) {
        return 0;
    }
    int maxdots = 0;
    for (int i = 0, j = 0; i < pts.size(); ++i) {
        if (pts[i] - pts[j] <= len) {
            maxdots = max(i - j + 1, maxdots);
        } else {
            ++j;
        }
    }
    return maxdots;
}

/**
 *  字串转32位ip,考虑输入为非法的情况
 */

bool str2IpInt(const char *ip, unsigned int &ipInt)
{
    if (ip == NULL || *ip == '\0') {
        return false;
    }
    int dots = 0;
    for (int i = 0; i < strlen(ip); ++i) {
        // 字串中有不是数字和.的字符
        if (!isdigit(ip[i]) && ip[i] != '.') {
            return false;
        } else {
            dots = ip[i] == '.' ? dots + 1 : dots;
        }
    }
    // 字串中.的个数不为3个
    if (dots != 3) {
        return false;
    }
    int d1 = -1, d2 = -1, d3 = -1, d4 = -1;
    sscanf(ip, "%d.%d.%d.%d", &d1, &d2, &d3, &d4);
    // 大小不对
    if (d1 < 0 || d1 > 255 || d2 < 0 || d2 > 255 || d3 < 0 || d3 > 255 || d4 < 0 || d4 > 255) {
        return false;
    }
    ipInt = (unsigned int)(d1 << 24 | d2 << 16 | d3 << 8 | d4);
    return true;
}

/**
 *  基本二分查找,输出索引,没有则输出-1,迭代
 *  数组按升序排序
 */
int binarySearch1(vector<int> ls, int k)
{
    if (ls.empty()) {
        return -1;
    }
    int left = 0, right = ls.size() - 1, mid;
    while (left <= right) {
        mid = left + ((right - left) >> 2);
        if (ls[mid] > k) {
            right = mid -1;
        } else if (ls[mid] < k) {
            left = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

/**
 *  二分查找k第一次出现的索引,没有则输出-1,迭代
 *  数组按升序排序
 */
int searchFirst(vector<int> ls, int k)
{
    if (ls.empty()) {
        return -1;
    }
    int left = 0, right = ls.size() - 1, mid; 
    while (left < right) {
        mid = left + ((right - left) >> 2);
        if (ls[mid] < k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return ls[left] == k ? left : -1;
}

/**
 *  二分查找k最后出现的索引,没有则输出-1,迭代
 *  数组按升序排序
 */
int searchLast(vector<int> ls, int k)
{
    if (ls.empty()) {
        return -1;
    }
    int left = 0, right = ls.size() - 1, mid;
    while (left < right - 1) {
        mid = left + ((right - left) >> 2);
        if (ls[mid] > k) {
            right = mid - 1;
        } else {
            left = mid;
        }
    }
    if (ls[right] == k) {
        return right;
    }
    if (ls[left] == k) {
        return left;
    }
    return -1;
}

/**
 *  二分查找比K小最接近K的数索引,没有则输出-1,迭代
 *  数组按升序排序
 */
int searchSmaller(vector<int> ls, int k)
{
    if (ls.empty()) {
        return -1;
    }
    int left = 0, right = ls.size() - 1, mid;
    while (left < right - 1) {
        mid = left + ((right - left) >> 2);
        if (ls[mid] >= k) {
            right = mid - 1;
        } else {
            left = mid;
        }
    }
    if (ls[right] < k) {
        return right;
    }
    if (ls[left] < k) {
        return left;
    }
    return -1;
}

/**
 *  二分查找比K大最近接K的索引,没有则输出-1,迭代
 *  数组按升序排序
 */
int searchBigger(vector<int> ls, int k)
{
    if (ls.empty()) {
        return -1;
    }
    int left = 0, right = ls.size() - 1, mid;
    while (left < right) {
        mid = left + ((right - left) >> 2);
        if (ls[mid] <= k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return ls[left] > k ? left : -1;
}

/**
 *  0-1背包
 *  动态规划
 */
int knapsack(vector<pair<int, int>> jewels, int cap)
{
    vector<int> dp(cap + 1, 0), tmp(cap + 1, 0);
    for (int i = 1; i < jewels.size() + 1; ++i) {
        tmp = dp;
        for (int j = 1; j < cap + 1; ++j) {
            if (jewels[i - 1].second <= j) {
                dp[j] = max(tmp[j], jewels[i - 1].first + tmp[j - jewels[i - 1].second]);
            }
        }
    }
    return dp[cap];
}

/**
 *  20个桶，每个桶中有10条鱼，用网从每个桶中抓鱼，每次可以抓住的条数随机，每个桶只能抓一次，问一共抓到180条的排列有多少种
 */


/**
 *  从给定的N个正数中选取若干个数之和最接近M
 */
