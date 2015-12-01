#include <iostream>

using namespace std;

class Test {
public:
    const int t = 96007005;
    void print() { cout << t << '\n'; }
    Test() { }
    Test(const Test& rhs) { }
};

int main (int argc, char * argv[])
{
    Test t1;
    Test t2 (t1);
    t1.print();
    t2.print();
    return 0;
}
