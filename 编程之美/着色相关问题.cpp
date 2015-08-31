/**
 *  最少教室问题，同时在线人数最多问题
 *  时间复杂度为O(NlofN)
 */
int least_classroom(vector<pair<int, int>> &activities) {
    if (activities.empty()) {
        return 0;
    }
    vector<pair<int, int>> ls;
    for (auto i : activities) {
        ls.push_back(make_pair(i.first, 1));
        ls.push_back(make_pair(i.second, -1));
    }
    sort(ls.begin(), ls.end(), 
        [](const pair<int, int> &x, const pair<int, int> &y) {
        // 如果时间点重合，结束点优先
        if (x.first == y.first) 
            return x.second < y.second; 
        return x.first < y.first;});
    int maxs = 0, takes = 0;
    for (auto i : ls) {
        takes += i.second;
        maxs = max(maxs, takes);
    }
    return maxs;
}

/**
 * 贪心法求着色问题较优解
 */


/**
 *  着色问题深搜
 */
