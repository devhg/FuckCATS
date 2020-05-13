/**
 * author: QXQZX
 * date: 2020/5/13 12:35
 * description: 时间片轮转调度算法RR q=x 修改自群友
 * License: MIT
 * other: FuckCATS plan
 **/
// #include <bits/stdc++.h>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define io ios::sync_with_stdio(0)
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define pii pair<int, int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
vector<int> ans;
queue<pii> q;
int at[200], st[200];
int finit[200], tt[200];
double wr[200];
int rr;
vector<int> G[200];
int n;

int cmp(int a, int b) { return finit[a] < finit[b]; }
int main() {
    // io;
    cout << "RR算法代码实现" << endl;
    cout << "请输入进程个数：";
    cin >> n;
    cout << "请输入时间片q：";
    cin >> rr;
    rep(i, 1, n) {
        cout << "请输入进程 " << i << " 到达时间、服务时间(空格隔开)：";
        cin >> at[i] >> st[i];
        G[at[i]].pb(i);
    }
    for (auto &i : G[0]) q.push(mp(i, 0));
    int ti = 0;
    while (!q.empty()) {
        pii t = q.front();
        q.pop();
        rep(i, 1, rr) {
            ans.pb(t.fi);
            ti++;
            for (auto &i : G[ti]) q.push(mp(i, 0));
            t.se++;
            if (t.se == st[t.fi]) {
                finit[t.fi] = ti;
                break;
            }
        }
        if (t.se != st[t.fi]) q.push(t);
    }
    cout << "Total time: " << ti << endl;
    cout << "Gantt chart如下：" << endl;
    ti = 0;
    cout << 0 << "";
    for (int i = 0; i < ans.size(); i++) {
        int p = i;
        while (p + 1 < ans.size() && ans[p] == ans[p + 1] && (p - i + 1) < rr)
            p++, ti++;
        ti++;
        cout << " (P" << ans[i] << ") " << ti << endl;
        ;
        i = p;
    }
    cout << endl;

    string s[200];
    s[1] = "Process";
    s[2] = "Finish Time";
    s[3] = "Arrival Time";
    s[4] = "Turnaround Time";
    s[5] = "Service Time";
    s[6] = "Wr";
    rep(i, 1, 6) { cout << s[i] << "\t   "; }
    cout << endl;
    double avtt = 0;
    double avwr = 0;
    rep(i, 1, n) {
        tt[i] = finit[i] - at[i];
        wr[i] = tt[i] * 1.0 / st[i];
        avtt += 1.0 * tt[i] / n;
        avwr += 1.0 * wr[i] / n;
    }
    int tmp[200];
    rep(i, 1, n) tmp[i] = i;
    sort(tmp + 1, tmp + 1 + n, cmp);
    rep(j, 1, n) {
        int i = tmp[j];
        cout << "P" << i << "\t\t" << finit[i] << "\t          " << at[i]
             << "\t          " << tt[i] << "\t                 " << st[i]
             << "\t    ";
        printf("%.10f\n", wr[i]);
    }

    printf("T=%.10f\nW=%.10f\n", avtt, avwr);
    return 0;
}
