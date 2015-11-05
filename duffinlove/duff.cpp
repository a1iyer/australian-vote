// duff.c
// Anoop Iyer, Nov 2015
// http://codeforces.com/problemset/problem/588/B

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<unsigned long long> prime;

inline unsigned int approxsqrt (int i)
{
    float x = (float) i;
    x = sqrt (i);
    return 1 + (unsigned int) x;
}

void expandprime (int n)
{
    int count = 0;
    unsigned long long i = 2+prime.back();
    bool composite = false;
    while (count < n) {
        unsigned int j = 0;
        composite = false;
        for (j = 0; (j < prime.size()) && (prime[j] < approxsqrt(i)); j++) {
            if (i % prime[j] == 0) {
                composite = true;
                break;
            }
        }
        if (!composite) {
            prime.push_back (i);
            ++count;
        }
        i += 2;
    }
}

int main (int argc, char * argv[])
{
    unsigned long long n;
    vector<unsigned long long> divisor;

    cin >> n;

    prime.push_back (2l);
    prime.push_back (3l);
    expandprime (1000);

    unsigned int i = 0;
    while (n != 1) {
        if (n % prime[i] == 0l) {
            divisor.push_back (prime[i]);
            while (n % prime[i] == 0l) n /= prime[i];
        }
        i++;

        if (prime[i] * prime[i] > n) {
            divisor.push_back (n);
            break;
        }

        if (i == prime.size()) expandprime(1000);
    }

    unsigned long long result = 1;
    for (auto x : divisor) result *= x;
    cout << result << endl;

    return 0;
}
