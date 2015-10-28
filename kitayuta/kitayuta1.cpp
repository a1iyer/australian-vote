//
// kitayuta1.cpp
// Anoop Iyer, Oct 2015
// http://codeforces.com/problemset/problem/505/A/
//

#include <iostream>
#include <string>

using namespace std;

bool ispal2 (string& s1)
{
    int n = s1.size(), u = -1;
    for (int i = 0; i <= n/2; i++)
        if (s1[i] == '_') u = i;
        else if (s1[n-1-i] == '_') u = n-1-i;
        else if (s1[i] != s1[n-1-i]) return false;
    if (u != -1) s1[u] = s1[n-u-1];
    return true;
}

int main ()
{
    string s, s1;
    cin >> s;
    bool b = false;

    for (int i = 0; i <= (int) s.size(); i++) {
        s1 = s;
        s1.insert (i, 1, '_');
        b = ispal2 (s1);
        if (b) {
            cout << s1 << '\n';
            break;
        }
    }
    if (!b) cout << "NA\n";
    return 0;
}
