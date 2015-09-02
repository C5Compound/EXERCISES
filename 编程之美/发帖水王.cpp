/**
 *  寻找数组中出现频率超过1/2的一个数
 *  可以通过快排partition找中位数的方式实现
 *  每次取一组两个数，不相同则删除
 *  以下程序都假定给定的ls是合法的
 */
void findHighFrequencyNum(vector<int> ls)
{
    int candidate, times = 0;
    for (int i = 0; i < ls.size(); ++i) {
        if (times == 0) {
            candidate = ls[i];
            ++times;
        } else {
            times = candidate == ls[i] ? times + 1 : times - 1;
        }
    }
    cout << candidate << endl;
}

/**
 *  寻找数组中的两个数，其出现频率均超过1/3
 *  每次取一组3个数，不相同则删除
 */
void findHighFrequencyNum(vector<int> ls)
{
    int candidate1, candidate2;
    int times1 = 0, times2 = 0;
    for (int i = 0; i < ls.size(); ++i) {
        if (times1 == 0) {
            candidate1 = ls[i];
            ++times1;
            continue;
        }
        if (times2 == 0) {
            candidate2 = ls[i];
            ++times2;
            continue;
        }
        if (ls[i] == candidate1) {
            ++times1;
        } else if (ls[i] == candidate2) {
            ++times2;
        } else {
            --times1;
            --times2;
        }
    }
    cout << candidate1 << endl;
    cout << candidate2 << endl;
}

/**
 *  寻找数组中的K个数，其出现频率均超过1/(K+1)
 *  每次取一组K+1个数，不同则删除
 */
void findHighFrequencyNum(vector<int> ls, int K)
{
    int candidate[K], times[K];
    fill_n(times, K, 0);
    for (int i = 0; i < ls.size(); ++i) {
        for (int j = 0; j < K; ++j) {
            if (times[j] == 0) {
                candidate[j] = ls[i];
                ++times[j];
                goto next;
            }
        }
        for (int j = 0; j < K; ++j) {
            if (candidate[j] == ls[i]) {
                ++times[j];
                goto next;
            }
        }
        for (int j = 0; j < K; ++j) {
            --times[j];
        }
next: ;
    }
    for (int j = 0; j < K; ++j) {
        cout << candidate[j] << endl;
    }
}
