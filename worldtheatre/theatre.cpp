// theatre.cpp | Anoop Iyer, Nov 2015 | http://codeforces.com/problemset/problem/131/C/

#include <iostream>

inline long long C (long long n, long long k)
{
    long long r=1, i=0;
    if (k > (n+1) / 2) k = n-k;
    for (i = 0; i != k; i++) r = (r * (n-i)) / (i+1);
    return r;
}

int main ()
{
    long long n=0, m=0, t=0, result=0, b=0;
    std::cin >> n >> m >> t;
    for (b = std::max (4ll, t-m); b <= t - std::max (1ll, t-n); b++) 
        result += C (n, b) * C (m, t-b);
    std::cout << result << '\n';
}
