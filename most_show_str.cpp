/**
*  1.找出字符串中连续出现最多次数的字串
*  2.找出字符串中最长的重复字符
*  3.返回长串中字串开始处以后的串,不使用库函数
*  4.将一句话里的单词倒置，标点符号不倒换
*  比如“i come from tianjin.”倒换后变为“tianjin. come from i”
*  5.求 1 - 4,000,000,000 的所有数字中含有字符‘1’的总数等于其数值的数
*  6.转换字符格式为原来字符串里的字符+该字符连续出现的个数
*  例如“1233422222”转换为“1121324125”
*/

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <stack>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

string mostly_show_str(const char *src)
{
    assert(src != NULL && *src != '\0');
    size_t max = 0;
    string result;
    for (size_t i = 1; i <= strlen(src); ++i) {
        for (size_t j = 0; j < strlen(src) - i; ++j) {
            size_t cnt = 1;
            for (size_t k = j; k + 2 * i <= strlen(src); k += i) {
                if (memcmp(src + k, src + k + i, i) == 0) cnt += 1;
                else break;
            }
            if (cnt >= max) {
                result.assign(src + j, i);
                max = cnt;
            }
        }
    }
    return result;
}

string dup_longest_str(const char *src)
{
    assert(src != NULL && *src != '\0');
    string str;
    for (size_t i = 1; i <= strlen(src); i++) {
        for (size_t j = 0; j < strlen(src) - i; j++) {
            for (size_t k = j + i; k + i <= strlen(src); k++) {
                if (memcmp(src + j, src + k, i) == 0) {
                    str.assign(src + j, i);
                    break;
                }
            }
        }
    }
    return str;
} 

const char* diy_strstr(const char *short_str, const char *long_str)
{
    assert(short_str != NULL && long_str != NULL);
    // 空串 和 短串长于长串 的情况也能产生正确的输出
    for (int i = 0; long_str[i] != '\0'; i++) {
        size_t j = 0;
        while (short_str[j] == long_str[i + j] && short_str[++j] != '\0');
        if (short_str[j] == '\0') {
            return long_str + i;
        }
    }
    return NULL;
}

// C语言做法实现
char* str_reverse(const char *src)
{
    assert(src != NULL);
    char *str = new char[strlen(src) + 1];
    for (int i = 0; i < strlen(src); i++) {
        str[i] = src[strlen(src) - 1 - i];
    }
    str[strlen(src)] = ' ';
    for (int i = 0; i < strlen(src); i++) {
        if (str[i] != ' ') {
            int p, q, j = i;
            while (str[j++] != ' ');
            for (p = i, q = j - 2; p < q; p++, q--) {
                char tmp = str[p];
                str[p] = str[q];
                str[q] = tmp;
            }
            i = j - 1;
        }
    }
    str[strlen(src)] = '\0';
    return str;
}

// 栈实现，思路清晰
string str_reverse(const char *src)
{
    assert(src != NULL);
    string str;
    stack<char> st, tmp;
    for (int i = 0; src[i] != '\0'; i++) {
        if (src[i] == ' ') {
            while (!tmp.empty()) {
                st.push(tmp.top());
                tmp.pop();
            }
            st.push(src[i]);
        } else {
            tmp.push(src[i]);
        }
    }
    while (!tmp.empty()) {
        st.push(tmp.top());
        tmp.pop();
    }
    while (!st.empty()) {
        str += st.top();
        st.pop();
    }
    return str;
}

/***************************************************************
** Kayven <hilyhoo@gmail.com>的高效代码
***************************************************************/
unsigned long f(unsigned long n){
    unsigned long fn = 0, ntemp = n;
    unsigned long step;
    for (step = 1; ntemp > 0; step *= 10, ntemp /= 10){
        fn += (((ntemp - 1) / 10) + 1) * step;
        if ((ntemp % 10) == 1){
            fn -= step - (n % step + 1);
        }
    }
    return fn;
}

unsigned long get_max_fn_equal_n(unsigned long upper_bound){
    unsigned long n = 1, fn = 0;
    unsigned long max = 1;
    while (n <= upper_bound) {
        fn = f(n);
        if (fn == n){
            max = n;
            printf("%10lu\t", n++);
        }
        /**
         *  因为 fn < n，而最大的long为10位数字，因而n增加一，fn增加不超过10
         *  所以增加的步长为（n-fn)/10 + 1
         */
        else if (fn < n)
            n += (n - fn) / 10 + 1;
        /**
         *  因为 fn > n, 在n到fn中间的n的取值，其对应的f(n+x) > f(n) = n + f(n) - n > n + x,
         *  所以可以直接增加到 n = fn
         */
        else
            n = fn;
    }
    return max;
}

// 返回 1-N 的“1”的个数简洁算法
unsigned int count_1s(unsigned int n)
{
    unsigned int step, count, remain = n;
    for (count = 0, step = 1; remain > 0; step *= 10, remain /= 10) {
        count += ((remain - 1) / 10 + 1) * step;
        if (remain % 10 == 1) {
            count -= step - (n % step + 1);
        }
    }
    return count;
}

// 0 - 4000000000 中 1s count = n 的数
void count_ones()
{
    unsigned int count = 0;
    for (unsigned int i = 1; i < 4000000000L; i++) {
        register unsigned int j = i;
        while (j > 0) {
            count = j % 10 == 1 ? count + 1 : count;
            j = j / 10;
        }
        if (i == count) {
            printf("%d\n", i);
        }
    }
}

string char_counts_format(const char *src)
{
    assert(src != NULL && *src != '\0');
    string str;
    char buf[12] = {0};
    for (int i = 0; i < strlen(src); i++) {
        str += src[i];
        int count = 1;
        // 如果碰到了‘\0’，循环也会结束
        while (src[i + count] == src[i]) {
            count += 1;
        }
        i += count - 1;
        sprintf(buf, "%d", count);
        str += buf;
    }
    return str;
}