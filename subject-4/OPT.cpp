// FILENAME: OPT.cpp
#include <iostream>
using namespace std;

int main() {
    int memory[4] = {-1, -1, -1, -1};
    int page[12] = {0, 6, 1, 5, 3, 7, 6, 7, 4, 3, 6, 1};  // the test pages
    int count = 0;                                        // missing page count
    int replace[12];                                      // replace page record
    int pr = 0;                                           // pointer of replace

    cout << "######OPT#######" << endl;
    // search begin
    for (int i = 0; i < 12; i++) {
        // there are 3 memory pages in memory ,so if i<3,just put it in memory
        if (i < 4) {
            memory[i] = page[i];
            count++;
        } else {
            // check if this page is in memory already
            bool exist = false;
            for (int j = 0; j < 4; j++) {
                if (page[i] == memory[j]) {
                    exist = true;
                    break;
                }
            }

            if (exist == false) {
                //###############################
                // begin to choose a memory page to replace
                int later = 0;
                bool ok[4];
                for (int j = 0; j < 4; j++) ok[j] = false;

                // check from i step -1 till 0
                for (int j = i + 1; j < 12; j++) {
                    for (int k = 0; k < 4; k++) {
                        if (page[j] == memory[k]) {
                            ok[k] = true;
                            later++;
                            break;
                        }
                    }
                    if (later == 2) break;
                }
                // check which ok ==false
                for (int j = 0; j < 4; j++) {
                    if (ok[j] == false) {
                        // replace this memory[j]
                        count++;
                        replace[pr] = memory[j];
                        pr++;
                        memory[j] = page[i];
                        break;
                    }
                }
                //#############################
            }
        }

        // output
        cout << page[i] << ":  [ ";
        for (int j = 0; j < 4; j++) {
            if (memory[j] == -1)
                cout << "*  ";
            else
                cout << memory[j] << "  ";
        }
        cout << "]" << endl;
    }
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
