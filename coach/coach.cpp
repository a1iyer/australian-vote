//
// coach.cpp
// Anoop Iyer, Nov 2015
// Solution to the coach problem in the SARC OOPL class
// http://codeforces.com/contest/300/problem/B/
//
// This is the debug version!
//

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

bool verbose = false;
#define derr if (verbose) cerr

struct Team {
    Team() { member[0] = 0; member[1] = 0; member[2] = 0; }
    int member[3] = {0, 0, 0};
    // int team_id = 0; // TODO: eliminate if not needed
    bool add (int p) {
        derr << "Adding " << p << '\n';
        if (member[0] == 0) {
            member[0] = p;
        } else if (member[1] == 0) {
            member[1] = p;
        } else if (member[2] == 0) {
            member[2] = p;
        } else {
            derr << "Failed! Members are " << member[0] << ',' << member[1] << ',' << member[2] << '\n';
            return false;
        }
        return true;
    }
    void print (void) {
        cout << member[0] << ' ' << member[1] << ' ' << member[2] << '\n';
    }
};

int main (int argc, char * argv[])
{
    if (argc > 1) verbose = true;
    
    int n = 0;
    int m = 0;

    cin >> n >> m;
    assert (n % 3 == 0);
    int num_teams = n/3;

    vector<Team> team (num_teams+1);
    vector<int> player (n+1, 0);

    int t = 1;
    bool failed = false;
    for (int i = 0; i < m; i++) {
        int p1, p2;
        cin >> p1 >> p2;
        derr << "Pair " << i << ": " << p1 << " and " << p2 << "\n";

        if (player[p1] != 0) {
            derr << "Player " << p1 << " found in team " << player[p1] << "\n";
            if (player[p2] == player[p1]) {
                derr << "Both " << p1 << " and " << p2 << " are in team " << player[p1] << "\n";
                continue;
            } else if (player[p2] == 0) {
                player[p2] = player[p1];
                if (team[player[p1]].add (p2) == false) {
                    derr << "Failed to add " << p2 << " to team " << player[p1] << "\n";
                    failed = true;
                    break;
                }
            } else {
                failed = true; break;
            }
        } else if (player[p2] != 0) {
            derr << "Player " << p2 << " found in team " << player[p2] << "\n";
            if (player[p1] == player[p2]) {
                derr << "Both " << p1 << " and " << p2 << " are in team " << player[p1] << "\n";
                continue;
            } else if (player[p1] == 0) {
                player[p1] = player[p2];
                if (team[player[p2]].add (p1) == false) {
                    derr << "Failed to add " << p1 << " to team " << player[p2] << "\n";
                    failed = true;
                    break;
                }
            } else {
                failed = true; break;
            }
        } else if (t <= num_teams) {
            derr << "Creating team " << t << " with " << p1 << " and " << p2 << "\n";
            player[p1] = t;
            player[p2] = t;
            assert (team[t].add (p1));
            assert (team[t].add (p2));
            t++;
        } else {
            derr << "Team request exceeded team capacity: t=" << t << "\n";
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
        derr << num_teams << " teams\n";
        derr << "Printing now!\n";
        for (int i = 1; i <= num_teams; i++) {
           team[i].print();
        }
    }

    return 0;
}
