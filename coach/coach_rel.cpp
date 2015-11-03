//
// coach.cpp
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
        if (member[0] == 0)
            member[0] = p;
        else if (member[1] == 0)
            member[1] = p;
        else if (member[2] == 0)
            member[2] = p;
        else
            return false;
        return true;
    }
    void print (void) {
        cout << member[0] << ' ' << member[1] << ' ' << member[2] << '\n';
    }
};

int main (int argc, char * argv[])
{
    int n = 0;
    int m = 0;

    cin >> n >> m;
    int num_teams = n/3;

    vector<Team> team (num_teams+1);
    vector<int> player (n+1, 0);

    int t = 1;
    bool failed = false;
    for (int i = 0; i < m; i++) {
        int p1, p2;
        cin >> p1 >> p2;

        if (player[p1] != 0) {
            if (player[p2] == player[p1]) {
                continue;
            } else if (player[p2] == 0) {
                player[p2] = player[p1];
                if (team[player[p1]].add (p2) == false) {
                    failed = true; break;
                }
            } else {
                failed = true; break;
            }
        } else if (player[p2] != 0) {
            if (player[p1] == player[p2]) {
                continue;
            } else if (player[p1] == 0) {
                player[p1] = player[p2];
                if (team[player[p2]].add (p1) == false) {
                    failed = true; break;
                }
            } else {
                failed = true; break;
            }
        } else if (t <= num_teams) {
            player[p1] = t;
            player[p2] = t;
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
        for (int i = 1; i <= n; i++) {
            if (player[i] == 0) {
                while (team[t].add (i) == false) t++;
            }
        }
        for (int i = 1; i <= num_teams; i++) {
           team[i].print();
        }
    }
    return 0;
}
