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

    // Read input
    int n = 0;
    cin >> n;
    vector<int> p (n+1);
    vector<bool> cross (n+1);
    vector<int> reachedat (n+1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    // Traverse
    int i = 1;
    int steps = 0;
    while (i != (n+1)) {
        if (verbose) cerr << i << ' ' << cross[i] << '\n';
        cross[i] = ! cross[i];
        i = cross[i] ? p[i] : i+1;
        steps++;
        if (reachedat[i] == 0) reachedat[i] = steps;
        if (steps == 1000000007) steps = 0;
    }
    for (unsigned int j = 0; j < reachedat.size(); j++) {
        if (verbose) cerr << j << ": " << reachedat[j] << '\n';
    }
    cout << steps << '\n';
}
