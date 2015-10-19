//
// ribbon.cpp
// Anoop Iyer, Oct 2015
// Cut Ribbon problem from CodeForces.com for SARC OOPL class
// http://codeforces.com/problemset/problem/189/A/
//

#include <iostream>

namespace Ribbon {

int n = 0;
int a = 0;
int b = 0;
int c = 0;
int maxdepth = 0;
int theoretical_max = 0;
bool case3 = true;

bool verbose = false;

class Node {
private:
    Node* child[3] = { NULL, NULL, NULL };
    int _sum = 0;   // sum of all numbers from the beginning
    int _depth = 0; // depth of this node (number of elements required)
    int _type = 0;
public:
    Node() { }
    Node (Node * parent, int weight, int type) {
        _sum = parent->_sum + weight;
        _depth = parent->_depth + 1;
        _type = type;
    }
    bool traverse (void);
};

bool Node::traverse (void)
{
    if (verbose) {
        std::cerr << "traverse: depth=" << _depth << ";sum=" << _sum << '\n';
    }

    if (_sum == n) {
        if (verbose) {
            std::cerr << "Matched sum " << _sum << '\n';
        }
        if (_depth > maxdepth) maxdepth = _depth;
        return true;
    } else if (_sum > n) {
        return false;
    }

    bool retval_a = false;
    bool retval_b = false;
    bool retval_c = false;

    if (_type <= 1) {
        child[0] = new Node (this, a, 1);
        retval_a = child[0]->traverse();
        delete child[0];
        if (maxdepth == theoretical_max) {
            return true;
        }
    }

    if (_type <= 2) {
        child[1] = new Node (this, b, 2);
        retval_b = child[1]->traverse();
        delete child[1];
        if (maxdepth == theoretical_max) {
            return true;
        }
    }

    if (_type <= 3 && case3) {
        child[2] = new Node (this, c, 3);
        retval_c = child[2]->traverse();
        delete child[2];
        if (maxdepth == theoretical_max) {
            return true;
        }
    }

    return (retval_a || retval_b || retval_c);
}

};

inline void swap_to_ascending (int& x, int& y)
{
    if (x > y) {
        int temp = x;
        x = y;
        y = temp;
    }
}

using namespace Ribbon;
using namespace std;

int main (int argc, char * argv[])
{
    if (argc > 1) verbose = true;

    std::cin >> n >> a >> b >> c;

    // Sort in ascending order
    swap_to_ascending (a, b);
    swap_to_ascending (b, c);
    swap_to_ascending (a, b);

    // Optimization: if we are given inputs like (2,5,5) we can collapse this
    // problem to (2,5) and ignore the 3rd element altogether.
    if (a == b) {
        b = c;
        case3 = false;
    }

    // Optimization: our theoretical max solution is n / a.
    theoretical_max = n / a;

    Node node;
    node.traverse();
    std::cout << maxdepth << '\n';

    return 0;
}
