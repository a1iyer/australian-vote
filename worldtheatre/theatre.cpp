// theatre.cpp
// Anoop Iyer, Nov 2015
// http://codeforces.com/problemset/problem/131/C/

#include <iostream>

using namespace std;
using num_t = long long;

num_t C (num_t n, num_t k)
{
    num_t r=1;
    if (k > (n+1) / 2) k = n-k;
    for (num_t i = 0; i != k; i++) {
        r *= n-i;
        r /= (i+1);
    }
    return r;
}

int main (int argc, char * argv[])
{
    num_t n=0, m=0, t=0, result=0;

    cin >> n >> m >> t;
    for (num_t b = max<num_t> (4, t-m); b <= t - max<num_t> (1, t-n); b++) 
        result += C (n, b) * C (m, t - b);
    cout << result << '\n';
    return 0;
}
