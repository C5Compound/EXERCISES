/**
 *  题目：一个数组中有三个数字a、b、c只出现一次，其他数字都出现了两次。请找出三个只出现一次的数字。
 */
// 保留最后一位为1的位
int last1Bit(int x)
{
    return x & ~(x - 1);
}

void findTripleMiss(vector<int> &ls)
{
    if (ls.size() < 3) {
        return;
    }
    int Xor = 0;
    for (auto i : ls) {
        Xor ^= i;
    }
    int fXor = 0;
    for (auto i : ls) {
        fXor ^= last1Bit(i ^ Xor);
    }
    fXor = last1Bit(fXor);
    int first = 0;
    for (auto i : ls) {
        // 特别注意此处
        if ((last1Bit(Xor ^ i) & fXor) > 0) {
            first ^= i;
        }
    }
    cout << "first of miss three is : " << first << endl;
    Xor ^= first;
    int second = 0, sXor = last1Bit(Xor);
    for (auto i : ls) {
        if ((sXor & i) > 0) {
            second ^= i;
        }
    }
    cout << "second of miss three is : " << second << endl;
    cout << "third of miss three is : " << (Xor ^ second) << endl;
}