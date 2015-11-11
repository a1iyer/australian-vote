// duff.c
// Anoop Iyer, Nov 2015
// http://codeforces.com/problemset/problem/588/B

#include <iostream>
#include <vector>

using namespace std;

void expandprime (int n, vector<unsigned long long>& p)
{
    int count = 0;
    unsigned long long i = 2+p.back(), j=0;
    bool composite = false;
    while (count < n) {
        composite = false;
        for (j = 1; (p[j] * p[j] < i) && (!composite); j++)
            if (i % p[j] == 0)
                composite = true;
        if (!composite) p.push_back (i), ++count;
        i += 2;
    }
}

int main (int argc, char * argv[])
{
    unsigned long long n=0, result=1, i=0;
    vector<unsigned long long> divisor;
    vector<unsigned long long> p {2, 3, 5, 7};

    cin >> n;
    while (n != 1) {
        if (n % p[i] == 0l) {
            divisor.push_back (p[i]);
            do n /= p[i]; while (n % p[i] == 0l);
        }
        i++;
        if (p[i] * p[i] > n) {
            divisor.push_back (n);
            break;
        }
        if (i == p.size()) expandprime (1000, p);
    }
    for (auto x : divisor) result *= x;
    cout << result << endl;
    return 0;
}
