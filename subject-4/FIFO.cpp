// FILENAME: FIFO.cpp
#include <iostream>
#define MAX 100
using namespace std;

int main() {
    int memory[3] = {-1, -1, -1};  //-1 means no page in this memory page
    int page[MAX];                 // the test pages
    int pm = 0;                    // pointer of memory
    int count = 0;                 // missing page count
    int replace[12];
    int pr = 0;

    int n, cnt = 0;
    while (cin >> n && n != -1) {
        page[cnt++] = n;
    }

    cout << "######FIFO#######" << endl;
    // search begin
    for (int i = 0; i < cnt; i++) {
        // check if there is page[i] in memory
        bool exist = false;
        for (int j = 0; j < 3; j++) {
            if (page[i] == memory[j]) {
                exist = true;
                break;
            }
        }
        // not exist , replace this memory page
        if (exist == false) {
            if (memory[pm] != -1) {
                replace[pr] = memory[pm];
                pr++;
            }

            count++;
            memory[pm] = page[i];
            pm++;
            if (pm == 3) pm = 0;
        }
        // output
        cout << page[i] << ":  [ ";
        for (int j = 0; j < 3; j++) {
            if (memory[j] == -1)
                cout << "*  ";
            else
                cout << memory[j] << "  ";
        }
        cout << "]" << endl;
    }
    // output
    cout << "######################" << endl;
    cout << "the lack page count = " << count << endl;

    cout << "repalce pages are  : ";
    for (int i = 0; i < pr; i++) {
        cout << replace[i] << " ";
    }
    cout << endl;

    cout << "the rate of page lack is " << count / 12.0 * 100 << "%" << endl;

    return 0;
}
