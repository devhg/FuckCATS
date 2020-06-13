/**
 * author: QXQZX
 * date: 2020/5/12 12:44
 * description: Clock算法实现
 * License: MIT
 * other: FuckCATS plan
 **/
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#define N 200
#define rep(i, a, b) for (int i = a; i <= b; i++)
using namespace std;

struct node {
    int index;
    int page;
    int status;
};
int PR[N];
int RS[N];
node ram[10];
node _ram[10][N];
node *p = NULL;
int frame;   // 物理块个数
int _page;   // 已装入内存的页面个数
int rs_num;  // 页面序列个数
int PF_NUM, PR_NUM;

void clock() {
    rep(i, 0, rs_num - 1) {
        int flag = 0;
        rep(j, 1, frame) {
            if (ram[j].page == RS[i]) {
                ram[j].status = 1;
                flag = 1;
                break;
            }
        }
        if (flag == 1) continue;
        int k = p->index;
        while (1) {
            if (ram[k].status == -1) {
                ram[k].page = RS[i];
                ram[k].status = 1;
                flag = 1;
                PF_NUM++;  // 页面中断次数++
            } else {
                if (ram[k].status == 1) {
                    ram[k].status = 0;
                } else if (ram[k].status == 0) {
                    PR[i] = ram[k].page;
                    ram[k].page = RS[i];
                    // cout << RS[i] << "***" << PR[i] << endl;
                    ram[k].status = 1;
                    flag = 1;
                    PF_NUM++;  // 页面中断次数++
                    PR_NUM++;  // 页面置换次数++
                }
            }
            if (k == frame) {
                p = &ram[1];
            } else {
                p = &ram[k + 1];
            }
            k = p->index;
            // cout << "p " << p->index << endl;
            if (flag == 1) break;
        }
        rep(j, 1, frame) {
            if (ram[j].page == -1) {
                // cout << ram[j].index << " "
                //      << " "
                //      << "-"
                //      << " " << endl;
            } else {
                _ram[j][i].page = ram[j].page;
                _ram[j][i].status = ram[j].status;
                _ram[j][i].index = ram[j].index;
                // cout << ram[j].index << " " << ram[j].page << "-"
                //      << ram[j].status << endl;
            }
        }
    }
}
void init_data() {
    PR_NUM = PF_NUM = 0;
    // cout << "test" << PF_NUM << PR_NUM << endl;
    rep(i, 0, N - 1) {
        PR[i] = -1;
        RS[i] = -1;
    }
    rep(i, 1, 9) {
        ram[i].index = i;
        ram[i].page = ram[i].status = -1;
        rep(j, 0, N - 1) {
            _ram[i][j].page = _ram[i][j].status = _ram[i][j].index = -1;
        }
    }
}
void init() {
    cout << "Clock 页面置换算法实现" << endl;
    init_data();
    cout << "请输入进程物理块个数：";
    cin >> frame;
    cout << "请输入已装入内存的界面个数：";
    cin >> _page;
    rep(i, 1, _page) {
        cout << "请输入已装入内存的界面 P A状态(空格隔开)：";
        cin >> ram[i].page >> ram[i].status;
    }
    int pp;
    cout << "指向高地址 (输入1) 指向低地址 (输入0)：";
    cin >> pp;
    p = (pp == 1) ? &ram[frame - 1] : &ram[1];
    cout << "请输入RS序列 -1结束：";
    int temp;
    rs_num = 0;
    while (cin >> temp && temp != -1) {
        RS[rs_num++] = temp;
    }
}
void show() {
    cout << "################### chart show #################" << endl;

    rep(i, 0, rs_num - 1) {
        if (PR[i] != -1) {
            cout << PR[i] << " ";
        } else
            cout << "  ";
    }
    cout << endl;
    rep(i, 0, rs_num - 1) { cout << RS[i] << " "; }
    cout << endl;
    rep(j, 1, frame) {
        rep(i, 0, rs_num - 1) {
            if (_ram[j][i].index == -1) {
                cout << "  ";
            } else {
                cout << _ram[j][i].page << " ";
            }
        }
        cout << endl;
    }
    cout << "################################################" << endl;
    cout << "PF: " << PF_NUM << endl;
    cout << "PR: " << PR_NUM << endl;
    rep(j, 1, frame) { cout << ram[j].page << "-" << ram[j].status << ","; }
    cout << endl;
}
int main() {
    init();
    clock();
    show();
    return 0;
}
