//
// coach_rel.cpp
// Anoop Iyer, Nov 2015
// Solution to the coach problem in the SARC OOPL class
// http://codeforces.com/contest/300/problem/B/
//

#include <iostream>
#include <vector>

using namespace std;

struct Team {
    int member[3] = {0, 0, 0};
    bool add (int p) {
        for (int i = 0; i < 3; i++) {
            if (member[i] == 0) {
                member[i] = p;
                return true;
            }
        }
        return false;
    }
    void print (void) {
        cout << member[0] << ' ' << member[1] << ' ' << member[2] << '\n';
    }
};

int main (int argc, char * argv[])
{
    int n = 0, m = 0, t = 1;
    bool failed = false;

    cin >> n >> m;
    int num_teams = n/3;

    vector<Team> team (num_teams+1);
    vector<int> teamof (n+1, 0);

    for (int i = 0; i < m; i++) {
        int p1, p2;
        cin >> p1 >> p2;

        if (teamof[p1] != 0) {
            if (teamof[p2] == teamof[p1]) {
                continue;
            } else if (teamof[p2] == 0) {
                teamof[p2] = teamof[p1];
                if (team[teamof[p1]].add (p2) == false) {
                    failed = true; break;
                }
            } else {
                failed = true; break;
            }
        } else if (teamof[p2] != 0) {
            if (teamof[p1] == teamof[p2]) {
                continue;
            } else if (teamof[p1] == 0) {
                teamof[p1] = teamof[p2];
                if (team[teamof[p2]].add (p1) == false) {
                    failed = true; break;
                }
            } else {
                failed = true; break;
            }
        } else if (t <= num_teams) {
            teamof[p1] = t;
            teamof[p2] = t;
            team[t].add (p1);
            team[t].add (p2);
            t++;
        } else {
            failed = true; break;
        }
    }

    if (failed) {
        cout << "-1\n";
    } else {
        t = 1;
        for (int p = 1; p <= n; p++) {
            if (teamof[p] == 0) {
                while (team[t].add (p) == false) t++;
            }
        }
        for (t = 1; t <= num_teams; t++) team[t].print();
    }
    return 0;
}
