/**
 *  寻找M满足N × M只包含0和1
 *  采用http://blog.csdn.net/jcwkyl/article/details/3859155的思路
 *  最后的值可能非常大，long long可能容不下
 */
long long findMultiplier(long long N)
{
    if (N <= 0) {
        return 0;
    }
    vector<bool> remains(N, false);
    queue<long long> Q;
    Q.push(1);
    // 层序的方式遍历，广度优先
    while (!Q.empty()) {
        long long root = Q.front();
        Q.pop();
        // 利用同余的性质进行剪枝
        if (remains[root % N]) {
            continue;
        }
        if (root % N == 0) {
            return root;
        }
        remains[root % N] = true;
        Q.push(root * 10);
        Q.push(root * 10 + 1);
    }
}