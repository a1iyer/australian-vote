// bear.cpp 
// Anoop Iyer, Nov 2015
// http://codeforces.com/problemset/problem/573/A/

#include <iostream>

using namespace std;

inline void reduce (unsigned long long& x)
{
    while ((x & 1) == 0) x = x >> 1;
    while (x % 3 == 0) x /= 3;
}

int main (int argc, char * argv[])
{
    int n = 0, i = 0;
    unsigned long long m = 0, p = 0;

    cin >> n;
    cin >> m;
    reduce (m);
    for (i = 1; i < n; i++) {
        cin >> p;
        reduce (p);
        if (p != m) break;
    }
    if (i == n) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}
