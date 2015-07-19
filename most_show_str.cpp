/**
*  找出字符转中连续出现最多次数的字串
*/

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

string mostly_show_str(const char *src)
{
    assert(src != NULL && *src != '\0');
    size_t max = 0;
    string result;
    for (size_t i = 1; i <= strlen(src); ++i) {
        for (size_t j = 0; j < strlen(src); ++j) {
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

int main()
{
    char src[] = "abcccccbcbcabc";
    cout << mostly_show_str(src) << endl;
    return 0;
}