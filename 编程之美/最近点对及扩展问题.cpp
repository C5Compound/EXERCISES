/**
 *  分治法求二维平面最近点对距离
 *  没有实现算法导论提及的备份方法
 */
struct Point
{
    double x, y;
    Point(double ix, double iy) : x(ix), y(iy) {};
    friend double D(const Point &p, const Point &q){ return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y)); };
};

double closest_pair(vector<Point> &pts, int l, int r)
{
    if (r - l <= 1) {
        return r != l ? D(pts[l], pts[r]) : DBL_MAX;
    }
    int mid = l + ((r - l) >> 1);
    double dmin = min(closest_pair(pts, l, mid), closest_pair(pts, mid + 1, r));
    // 可以二分查找 pts[x] ± dmin的界
    int ll = mid, rr = mid + 1;
    while (ll >= l && pts[ll].x >= pts[mid].x - dmin) --ll;
    ll = ll < l ? l : ll;
    while (rr <= r && pts[rr].x <= pts[mid].x + dmin) ++rr;
    rr = rr > r ? r : rr;
    // 只计算矩形内的点
    for (int i = ll; i <= mid; ++i) {
        for (int j = mid + 1; j <= rr; ++j) {
            if (fabs(pts[i].y - pts[j].y) <= dmin) {
                dmin = min(D(pts[i], pts[j]), dmin);
            }
        }
    }
    return dmin;
}

double find_closest(vector<Point> &pts)
{
    if (pts.empty()) {
        return -1.0;
    }
    sort(pts.begin(), pts.end(), [](const Point &p, const Point &q){return p.x < q.x; });
    return closest_pair(pts, 0, pts.size() - 1);
}

/**
 *  求数组中大小相邻数字的最大差值
 *  由于小数的原因，可能出现结果有偏差
 */
double max_diff(vector<double> nums)
{
    if (nums.size() < 2) {
        return -1;
    }
    double maxnum = *max_element(nums.begin(), nums.end());
    double minnum = *min_element(nums.begin(), nums.end());
    // 分成N - 1个桶，第N个桶用来处理最大值，初始化
    vector<pair<double, double>> buckets(nums.size(), pair<double, double>(DBL_MAX, -DBL_MAX));
    double space = (maxnum - minnum) / (nums.size() - 1);
    for (auto i : nums) {
        int buc = floor((i - minnum) / space);
        buckets[buc].first = min(i, buckets[buc].first);
        buckets[buc].second = max(i, buckets[buc].second);
    }
    // 遍历寻找最大差值
    double maxspace = 0;
    for (int i = 1, j = 0; i < buckets.size(); ++i) {
        // 空桶
        if (fabs(buckets[i].first - DBL_MAX) < DBL_EPSILON) continue;
        double tmp = buckets[i].first - buckets[j].second;
        maxspace = max(tmp, maxspace);
        j = i;
    }
    return maxspace;
}

/**
*  凸包加旋转卡壳算法求最远点对距离
*  不适用于不能构成凸包的情况
*  可以进行检测，如果返回的hull大小为2，则所有的点共线
*  可以用Graham扫描法也可以用步进法建立凸包
*/
double crossX(const Point &p0, const Point &p1, const Point &p2)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

// 点在三个及以上
vector<Point> GrahamScan(vector<Point> &pts)
{
    // 找出最下角的点
    int i = 0;
    for (int j = 1; j < pts.size(); ++j) {
        if (pts[j].y < pts[i].y || (pts[j].y == pts[i].y && pts[j].x < pts[i].x)) {
            i = j;
        }
    }
    swap(pts[i], pts[0]);
    // 按极角排序
    sort(pts.begin() + 1, pts.end(), [&pts](const Point &p1, const Point &p2) -> bool {return crossX(pts[0], p1, p2) > 0; });
    // 扫描过程
    vector<Point> hull;
    hull.push_back(pts[0]);
    hull.push_back(pts[1]);
    pts.push_back(pts[0]);
    for (int i = 2; i < pts.size(); ++i) {
        int j = hull.size() - 1;
        while (j > 0 && crossX(pts[j], pts[i], pts[j - 1]) <= 0) {
            hull.pop_back();
            --j;
        }
        hull.push_back(pts[i]);
    }
    // 返回的hull中的第一个和最后一个点相同
    return hull;
}

// 旋转卡壳算法求凸包直径
double rotateConvex(vector<Point> hull)
{
    double diameter = 0, tmp;
    for (int i = 0, scan_pos = 1; i < hull.size() - 1; ++i) {
        while ((tmp = crossX(hull[i], hull[i + 1], hull[scan_pos + 1])) > crossX(hull[i], hull[i + 1], hull[scan_pos])) {
            // hull中包含了重复的点，所以取余的时候减一
            scan_pos = (scan_pos + 1) % (hull.size() - 1);
        }
        diameter = max(max(D(hull[i], hull[scan_pos]), D(hull[i + 1], hull[scan_pos])), diameter);
    }
    // 最大直径可以通过面积/底来求出
    return diameter;
}
