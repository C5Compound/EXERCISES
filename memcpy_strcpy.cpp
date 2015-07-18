/**
 *  memcpy和strcpy的实现
 */

#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

char* strcpy(char *Dest, const char *Src)
{
    assert(Dest != NULL && Src != NULL);
    char *cp = Dest;
    while ((*cp++ = *Src++) != '\0');
    return Dest;
}

void memcpy(void *Dest, void *Src, int length)
{

}

int main()
{
    char c = 255;
    printf("%d\n", c);
    return 0;
}