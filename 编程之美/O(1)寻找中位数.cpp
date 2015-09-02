/**
*  O(1)时间完成中位数查找，O(logN)时间完成插入
*  数据结构为最大堆结合最小堆
*/
class MidHeap
{
private:
    // 中位数
    int mid;
    // 左右堆的大小
    size_t left, right, all;
    // 最大堆
    priority_queue<int, vector<int>, less<int>> left_heap;
    // 最小堆
    priority_queue<int, vector<int>, greater<int>> right_heap;
public:
    // 构造
    MidHeap();
    // 判断是否为空
    bool empty();
    // 取得中位数
    double getMid();
    // 插入
    void insert(int);
};

MidHeap::MidHeap() : left(0), right(0), all(0)
{
}

bool MidHeap::empty()
{
    return all == 0;
}

// 奇数个则返回中位数，偶数个返回最中间两个数的均值
double MidHeap::getMid()
{
    if (all % 2) {
        return mid;
    }
    return left > right ? (mid + left_heap.top()) / 2.0 : (mid + right_heap.top()) / 2.0;
}

/**
 *  插入后对堆进行调整
 */
void MidHeap::insert(int k)
{
    if (all == 0) {
        mid = k;
        ++all;
        return;
    }
    if (k <= mid) {
        if (left - right >= 1) {
            right_heap.push(mid);
            ++right;
            if (k < left_heap.top()) {
                mid = left_heap.top();
                left_heap.pop();
                left_heap.push(k);
            }
        } else {
            left_heap.push(k);
            ++left;
        }
    } else {
        if (right - left >= 1) {
            left_heap.push(mid);
            ++left;
            if (k > right_heap.top()) {
                mid = right_heap.top();
                right_heap.pop();
                right_heap.push(k);
            }
        } else {
            right_heap.push(k);
            ++right;
        }
    }
    ++all;
}