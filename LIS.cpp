/**
 *  最长递增子序列的三种实现
 */

// O(N^2)算法
int LIS1(vector<int> &nums)
{
    // 数组保存以i位置为终点的最长递增子序列
    vector<int> dp(nums.size(), 1);
    // 找出最大值
    int maxlen = 0;
    for (int i = 1; i < nums.size(); ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxlen = max(maxlen, i);
    }
    return maxlen;
}


// O(N^2)算法
int LST2(vector<int> &nums)
{
    // lenMinVal数组保存的是长度为len的序列最小终点
    vector<int> lenMinVal(nums.size() + 1, 1), dp(nums.size(), 1);
    int maxlen = 1;
    for (int i = 1; i < nums.size(); ++i) {
        for (int j = maxlen; j >= 1; --j) {
            if (nums[i] > lenMinVal[j]) {
                dp[i] = j + 1;
                break;
            }
        }
        if (dp[i] > maxlen) {
            lenMinVal[dp[i]] = nums[i];
            maxlen = dp[i];
        } else {
            lenMinVal[dp[i]] = min(nums[i], lenMinVal[dp[i]]);
        }
    }
    return maxlen;
}

// 二分过程，数组按升序排列
int lowerbound(vector<int> arr, int k)
{
    int left = 0, right = arr.size() - 1, mid;
    while (left < right) {
        mid = left + ((right - left + 1) >> 1);
        if (arr[mid] >= k) {
            right = mid - 1;
        } else {
            left = mid;
        }
    }
    return arr[left] < k ? left : -1;
}

// O(NlgN)算法
int LST3(vector<int> &nums)
{
    // lenMinVal数组保存的是长度为len的序列最小终点
    vector<int> lenMinVal(nums.size() + 1, 1), dp(nums.size(), 1);
    int maxlen = 1;
    for (int i = 1; i < nums.size(); ++i) {
        // 二分查找len长度的最小终点刚好小于nums[i]
        lowerbound(vector<int>(lenMinVal[1], lenMinVal[maxlen]), nums[i]);
        if (dp[i] > maxlen) {
            lenMinVal[dp[i]] = nums[i];
            maxlen = dp[i];
        } else {
            lenMinVal[dp[i]] = min(nums[i], lenMinVal[dp[i]]);
        }
    }
    return maxlen;
}