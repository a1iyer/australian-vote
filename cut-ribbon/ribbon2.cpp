//
// ribbon2.cpp
// Anoop Iyer, Oct 2015
// Cut Ribbon problem from CodeForces.com for SARC OOPL class
// http://codeforces.com/problemset/problem/189/A/
//

#include <iostream>
#include <utility>

int cache[4000];
bool case3 = true;
int n, a, b, c;

using namespace std;

int depth (int x)
{
    int d_a, d_b, d_c;

    if (x == 0) return 0;
    if (x < 0) return -2;
    if (cache[x] != 0) return cache[x];
    
    d_a = depth (x - a);
    d_b = depth (x - b);
    if (case3) d_c = depth (x - c);

    int max = -1;
    if (d_a > max) max = d_a;
    if (d_b > max) max = d_b;
    if (case3) if (d_c > max) max = d_c;

    if (max >= 0) max++;
    cache[x] = max;
    return max;
}

int main (int argc, char * argv[])
{
    cin >> n >> a >> b >> c;

    // Sort and sift
    if (a > b) swap (a, b);
    if (b > c) swap (b, c);
    if (a > b) swap (a, b);
    if (a == b) {
        b = c;
        case3 = false;
    }
    if ((c > n) || (b == c))
        case3 = false;

    // Trivial case
    int theoretical_max = n / a;
    if ((theoretical_max * a) == n) {
        std::cout << theoretical_max << '\n';
        return 0;
    }

    cout << depth (n) << '\n';
    return 0;
}
