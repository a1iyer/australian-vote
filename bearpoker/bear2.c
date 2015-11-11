// bear2.c 
// Anoop Iyer, Nov 2015
// http://codeforces.com/problemset/problem/573/A/

#include <stdio.h>
#include <assert.h>

inline unsigned long reduce (unsigned long x)
{
    while ((x & 1) == 0) x = x >> 1;
    while (x % 3 == 0) x /= 3;
    return x;
}

int main (int argc, char * argv[])
{
    int n = 0, i = 0;
    unsigned long m = 0, p = 0;

    assert (scanf ("%d", &n) == 1);
    assert (scanf ("%lu", &m) == 1);
    m = reduce (m);
    for (i = 1; i < n; i++) {
        assert (scanf ("%lu", &p) == 1);
        p = reduce (p);
        if (p != m) break;
    }
    if (i == n) printf ("Yes\n");
    else printf ("No\n");
    return 0;
}
