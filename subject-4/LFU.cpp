#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

#define pageNum 10  /*  系统分配给主存的页面数*/
#define memoryNum 3 /*  可用内存页面数*/

int page[pageNum] = {2, 6, 2, 7, 1, 4, 6, 1, 7, 1};
int memory[memoryNum];

void generate_date();
double FIFO(int flag);
double LRU(int flag);
double OPT(int flag);
void SHOW();

int main() {
    // generate_date();
    while (1) {
        int choice;
        cout << endl << "---------------------------" << endl;
        cout << "1) FIFO " << endl;
        cout << "2) LRU" << endl;
        cout << "3) OPT" << endl;
        cout << "4) SHOW" << endl;
        cout << "5) EXIT" << endl;
        cout << "---------------------------" << endl;
        cout << "enter the chocie : ";
        cin >> choice;
        cin.clear();
        switch (choice) {
            case 1:
                FIFO(0);
                break;
            case 2:
                LRU(0);
                break;
            case 3:
                OPT(0);
                break;
            case 4:
                SHOW();
                break;
            case 5:
                exit(0);
                break;
            default:
                cout << "Enter Error!" << endl;
                exit(-1);
        }
    }
    return 0;
}

void generate_date() {       //随机生成页面
    srand((int)time(NULL));  //设置种子

    printf("页面访问序列：\n");

    for (int i = 1; i <= pageNum; i++) {
        int date = rand() % pageNum + 1;
        if (date == page[i - 1]) {
            i--;
            continue;
        }
        page[i - 1] = date;
        printf("%d ", date);
        if (i % 10 == 0) printf("\n");
    }
}

double FIFO(int flag) {
    int j, k = 0, sum = 0;
    for (int i = 0; i < pageNum; i++) {
        if (i < memoryNum) {  //如果是前几个，直接补充
            memory[i] = page[i];
            cout << i + 1 << " : " << page[i] << " -> ";
            for (int h = 0; h < memoryNum; h++)
                if (i < memoryNum && h > i)
                    cout << "_"
                         << " ";
                else
                    cout << memory[h] << " ";
            cout << endl;
            continue;
        }
        for (j = 0; j < memoryNum; j++)
            if (page[i] == memory[j]) {  //找到相同页面，不置换
                cout << i + 1 << " : " << page[i] << " -> ";
                for (int h = 0; h < memoryNum; h++)
                    if (i - memoryNum < 0)
                        cout << "_"
                             << " ";
                    else
                        cout << memory[h] << " ";
                cout << endl;
                break;
            }
        if (j == memoryNum) {       //未找到相同页面，置换
            memory[k++] = page[i];  //直接置换，先到先换
            k %= memoryNum;         // k为memory的标记位，防止越界
            sum++;                  //统计缺页数
            cout << i + 1 << " : " << page[i] << " -> ";
            for (int h = 0; h < memoryNum; h++)
                if (i - memoryNum < 0)
                    cout << "_"
                         << " ";
                else
                    cout << memory[h] << " ";
            cout << endl;
        }
    }
    if (!flag) {
        cout << "Number of page substitutions : " << sum << endl;
        cout << "Page missing rate :" << double(sum) / pageNum * 100 << "%"
             << endl
             << endl;

        cout << endl << "Press any key to continue" << endl;
        getchar();
        getchar();
    }
    system("clear");
    return double(sum) / pageNum;
}
// 当需要淘汰一个页面时，总是选择驻留主存时间最长的页面进行淘汰，即先进入主存的页面先淘汰。
// as最早调入主存的页面不再被使用的可能性最大

double LRU(int flag) {
    //模拟栈的实现
    //栈顶始终是最新被访问页面的编号，而栈底则是最近最久未使用页面的页面号。
    int j, sum = 0;

    for (int i = 0; i < pageNum; i++) {
        if (i < memoryNum) {  //前几个
            memory[i] = page[i];

            cout << i + 1 << " : " << page[i] << " -> ";
            for (int h = 0; h < memoryNum; h++)
                if (i < memoryNum && h > i)
                    cout << "_"
                         << " ";
                else
                    cout << memory[h] << " ";
            cout << endl;

            continue;
        }

        for (j = 0; j < memoryNum; j++)  //匹配到相同页面,将该页面调至栈的顶端
            if (page[i] == memory[j]) {
                for (int k = j; k < memoryNum - 1; k++)
                    memory[k] = memory[k + 1];
                memory[memoryNum - 1] = page[i];

                cout << i + 1 << " : " << page[i] << " -> ";
                for (int h = 0; h < memoryNum; h++)
                    if (i - memoryNum < 0)
                        cout << "_"
                             << " ";
                    else
                        cout << memory[h] << " ";
                cout << endl;
                break;
            }

        if (j == memoryNum) {  //未匹配到相同页面，置换
            for (int k = 0; k < memoryNum - 1; k++)  //提取栈底
                memory[k] = memory[k + 1];
            memory[memoryNum - 1] = page[i];  //从栈头插入新的页面
            sum++;

            cout << i + 1 << " : " << page[i] << " -> ";
            for (int h = 0; h < memoryNum; h++)
                if (i - memoryNum < 0)
                    cout << "_"
                         << " ";
                else
                    cout << memory[h] << " ";
            cout << endl;
        }
    }

    if (!flag) {
        cout << "Number of page substitutions : " << sum << endl;
        cout << "Page missing rate :" << double(sum) / pageNum * 100 << "%"
             << endl
             << endl;

        cout << endl << "Press any key to continue" << endl;
        getchar();
        getchar();
    }
    system("clear");
    return double(sum) / pageNum;
}
// 利用局部性原理，根据一个作业在执行过程中过去的页面访问历史来推测未来的行为。
// 它认为过去一段时间里不曾被访问过的页面，在最近的将来可能也不会再被访问。
// 当需要淘汰一个页面时，总是选择在最近一段时间内最久不用的页面予以淘汰

double OPT(int flag) {  // OPT，向后遍历
    int j, sum = 0;

    for (int i = 0; i < pageNum; i++) {
        if (i < memoryNum) {  //前几个
            memory[i] = page[i];

            cout << i + 1 << " : " << page[i] << " -> ";
            for (int h = 0; h < memoryNum; h++)
                if (i < memoryNum && h > i)
                    cout << "_"
                         << " ";
                else
                    cout << memory[h] << " ";
            cout << endl;

            continue;
        }

        for (j = 0; j < memoryNum; j++)
            if (page[i] == memory[j]) {  //找到相同页面，不置换
                cout << i + 1 << " : " << page[i] << " -> ";
                for (int h = 0; h < memoryNum; h++)
                    if (i - memoryNum < 0)
                        cout << "_"
                             << " ";
                    else
                        cout << memory[h] << " ";
                cout << endl;
                break;
            }

        if (j == memoryNum) {  //未匹配到相同页面，置换
            int find_flag = 0, replace_flag = 0, replace_position, h;
            for (int k = 0; k < memoryNum; k++) {
                for (h = i + 1; h < pageNum; h++) {  //先后遍历
                    if (memory[k] == page[h]) {      //如果是有要被访问
                        find_flag = 1;  //标记存有将被访问的页面
                        if (replace_flag < h) {  //比较，置换较远将被访问的页面
                            replace_flag = h;
                            replace_position = k;
                        }
                        break;  //找到后，跳出当前循环，进入下一层循环
                    }
                }
                if (h == pageNum) {  //如果，当前页面不会被再次访问
                    find_flag = 0;
                    replace_position = k;
                    k = memoryNum;  //跳出双层循环，直接置换
                }
            }

            memory[replace_position] = page[i];  //置换

            sum++;

            cout << i + 1 << " : " << page[i] << " -> ";
            for (int h = 0; h < memoryNum; h++)
                if (i - memoryNum < 0)
                    cout << "_"
                         << " ";
                else
                    cout << memory[h] << " ";
            cout << endl;
        }
    }

    if (!flag) {
        cout << "Number of page substitutions : " << sum << endl;
        cout << "Page missing rate :" << double(sum) / pageNum * 100 << "%"
             << endl
             << endl;

        cout << endl << "Press any key to continue" << endl;
        getchar();
        getchar();
    }
    system("clear");
    return double(sum) / pageNum;
}
// 从主存中移出永远不再需要的页面；如无这样的页面存在，则选择最长时间不需要访问的页面。
// 于所选择的被淘汰页面将是以后永不使用的，或者是在最长时间内不再被访问的页面
// 这样可以保证获得最低的缺页率

void SHOW() {
    double f = FIFO(1), l = LRU(1), o = OPT(1);
    cout << "Page missing rate ：" << endl << endl;
    cout << "1) FIFO ：" << f * 100 << "%" << endl;
    cout << "2) LRU  ：" << l * 100 << "%" << endl;
    cout << "3) OPT  ：" << o * 100 << "%" << endl;

    cout << endl << "Press any key to continue" << endl;
    getchar();
    getchar();

    system("clear");
}