// Domokos Ábel
// 411

#include "damm0338_L7_1a.h"

int main()
{
    Stack<int> verem(3);
    verem.push(5);
    verem.push(6);
    verem.push(6);
    verem.print();

    verem.pop();
    verem.print();

    verem(fg);
    verem.print();
    cout << verem[0] << endl;
    try {
        verem.pop();
        verem.pop();
        verem.pop();
    } catch (const char* uzenet) {
        cout << uzenet << endl;
    }

    return 0;
}