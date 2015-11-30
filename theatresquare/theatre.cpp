// Nov 2015, Anoop Iyer | http://codeforces.com/problemset/problem/1/A

#include <iostream>

int main ()
{
    unsigned long long n=0, m=0, a=0;
    std::cin >> n >> m >> a;
    std::cout << (n % a ? n / a + 1 : n / a) * (m % a ? m / a + 1 : m / a) << '\n';
}
