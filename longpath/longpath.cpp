//
// longpath.cpp
// Anoop Iyer, Oct 2015
// Long path problem for SARC OOPL class:
// http://codeforces.com/problemset/problem/407/B/
//

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

int main (int argc, char * argv[])
{
    bool verbose = false;
    if (argc > 1) verbose = true;

    int n = 0;
    cin >> n;
    vector<int> p (n+1);
    vector<int> reachedat (n+2, 0);
    for (int i = 1; i <= n; i++) cin >> p[i];

    for (int i = 2; i < n+2; i++) {
        reachedat[i] = (2 * reachedat[i-1]) + 2 - reachedat[p[i-1]];
        if (reachedat[i] < 0) reachedat[i] += 1000000007;
        reachedat[i] = reachedat[i] % 1000000007;
        if (verbose) cerr << i << ": " << reachedat[i] << "\n";
    }
    for (unsigned int j = 0; j < reachedat.size(); j++)
        if (verbose) cerr << j << ": " << reachedat[j] << '\n';
    cout << reachedat[n+1] << endl;
}
