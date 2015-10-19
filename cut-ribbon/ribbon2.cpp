//
// ribbon2.cpp
// Anoop Iyer, Oct 2015
// Cut Ribbon problem from CodeForces.com for SARC OOPL class
// http://codeforces.com/problemset/problem/189/A/
//

#include <iostream>

#define TEN 0,0,0,0,0,0,0,0,0,0,
#define HUN TEN TEN TEN TEN TEN TEN TEN TEN TEN TEN
#define THOU HUN HUN HUN HUN HUN HUN HUN HUN HUN HUN
#define FOURTHOU THOU THOU THOU THOU

int cache[4000] = { FOURTHOU };
bool case3 = true;
int n = 0, a = 0, b = 0, c = 0;

using namespace std;

inline void swap_to_ascending (int& x, int& y)
{
    if (x > y) {
        int temp = x;
        x = y;
        y = temp;
    }
}

int depth (int x)
{
    int d_a = 0, d_b = 0, d_c = 0;

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

    if (max >= 0) {
        max++;
    } else {
        max = -1;
    }
    cache[x] = max;
    return max;
}

int main (int argc, char * argv[])
{
    cin >> n >> a >> b >> c;

    // Sort and sift
    swap_to_ascending (a, b);
    swap_to_ascending (b, c);
    swap_to_ascending (a, b);
    if (a == b) {
        b = c;
        case3 = false;
    } else if (b == c) {
        case3 = false;
    }

    // Optimization for the trivial case
    int theoretical_max = n / a;
    if ((theoretical_max * a) == n) {
        std::cout << theoretical_max << '\n';
        return 0;
    }

    cout << depth (n) << '\n';
    return 0;
}
