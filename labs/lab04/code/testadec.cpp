//               testadec.cpp
#include <iostream>
#include <iomanip>
#include "fsm.h"

using namespace std;

int main() {
    tFSM Adec;
///////////////////////
//  Постоить автомат
    addrange(Adec, 0, '1', '9', 6);
    addstr(Adec, 0, "+", 7);
    addstr(Adec, 0, "-", 7);
    addrange(Adec, 7, '1', '9', 6);
    addstr(Adec, 0, "0", 1);
    addstr(Adec, 1, ".", 2);
    addrange(Adec, 6, '0', '9', 6);
    addstr(Adec, 6, ".", 2);
    addrange(Adec, 2, '0', '9', 2);

    addstr(Adec, 6, "e", 3);
    addstr(Adec, 6, "E", 3);
    addstr(Adec, 2, "e", 3);
    addstr(Adec, 2, "E", 3);
    addstr(Adec, 3, "+", 4);
    addstr(Adec, 3, "-", 4);
    addrange(Adec, 4, '0', '9', 5);
    addrange(Adec, 5, '0', '9', 5);

//......................
    Adec.final(1);
    Adec.final(2);
    Adec.final(5);
    Adec.final(6);
//......................
///////////////////////
    cout << "*** dao Adec "
         << "size=" << Adec.size()
         << " ***\n";
    cout << endl;

    while (true) {
        char input[81];
        cout << ">";
        cin.getline(input, 81);
        if (!*input) break;
        int res = Adec.apply(input);
        cout << setw(res ? res + 1 : 0) << "^"
             << endl;
    }
    return 0;
}
