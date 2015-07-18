/**
 *  memcpy和strcpy的实现
 *  记得判断指针的有效性
 */

#include <cassert>
#include <cstdlib>
#include <cstdio>
using namespace std;

char* strcpy(char *dest, const char *src)
{
    assert(dest != NULL && src != NULL);
    char *cp = dest;
    while ((*cp++ = *src++) != '\0');
    return dest;
}

void* memcpy(void *dest, const void *src, size_t length)
{
    assert(dest != NULL && src != NULL);
    // 不允许对void*指针进行自加和加法运算
    char *_dest = (char*)dest;
    const char *_src = (const char*)src;
    // 从前往后拷贝
    if (_dest <= _src) {
        while (length-- > 0) {
            *_dest++ = *_src++;
        }
    } else {
        // 从后往前拷贝
        while (length-- > 0) {
            *(_dest + length) = *(_src + length);
        }
    }
    return dest;
}

void* memset(void *dest, char c, size_t size)
{
    assert(dest != NULL);
    char *_dest = (char*)dest;
    while (size-- > 0) {
        *_dest = c;
    }
    return dest;
} 

size_t strlen(const char *src)
{
    assert(src != NULL);
    return *src == '\0' ? 0 : 1 + strlen(src + 1);
}

size_t strlen(const char *src)
{
    assert(src != NULL);
    size_t len = 0;
    while (*src++ != '\0') {
        len += 1;
    }
    return len;
}
