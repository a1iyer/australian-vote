// coach_rel.cpp
// Anoop Iyer, Nov 2015
// Solution to the coach problem in the SARC OOPL class
// http://codeforces.com/contest/300/problem/B/

#include <iostream>
#include <vector>

using namespace std;

struct Team {
    int _m[3] = {-1, -1, -1};
    inline bool add (int p) {
        for (int i = 0; i < 3; i++)
            if (_m[i] == -1) {
                _m[i] = p;
                return true;
            }
        return false;
    }
    inline void add (int p1, int p2) { add (p1); add (p2); }
    inline void print (void) { cout << _m[0] << ' ' << _m[1] << ' ' << _m[2] << '\n'; }
};

int main (int argc, char * argv[])
{
    int n = 0, m = 0, t = 0, p1 = 0, p2 = 0, i = 0, num_teams = 0;

    cin >> n >> m;
    num_teams = n/3;
    Team team [num_teams];
    vector<int> teamof (n+1, -1);

    for (i = 0; i < m; i++) {
        cin >> p1 >> p2;

#define EXECUTE(x,y) {                                          \
            if (teamof[x] == teamof[y]) continue;               \
            else if (teamof[x] == -1) {                         \
                if (!team[teamof[x] = teamof[y]].add (x)) break;\
            } else break;                                       \
        }

        if (teamof[p1] != -1) EXECUTE (p2, p1)
        else if (teamof[p2] != -1) EXECUTE (p1, p2)
        else if (t < num_teams) team[teamof[p1] = teamof[p2] = t++].add (p1, p2);
        else break;
    }

    if (i != m)
        cout << "-1\n";
    else {
        t = 0;
        for (i = 1; i <= n; i++) if (teamof[i] == -1) while (!team[t].add (i)) t++;
        for (t = 0; t < num_teams; t++) team[t].print();
    }
    return 0;
}
