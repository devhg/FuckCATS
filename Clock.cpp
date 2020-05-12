#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#define N 200
using namespace std;

int page[N];     //页面引用号
int block[N];    //物理块，内存
int dist[N][N];  //表示第i次访问内存的时候，内存中的页面j 在以后被访问的最小时间

int n;         //页面引用号个数
int m;         //物理块数目
int page_max;  //最大页面号

int pre[N];  // page[i]在page中的索引
int opt() {  //最佳页面置换算法
    int page_lack = 0;
    memset(pre, 0, sizeof(pre));
    memset(dist, 0x3f, sizeof(dist));
    memset(block, -1, sizeof(block));
    for (int i = n; i >= 1; --i) {
        for (int j = 0; j <= page_max; ++j)
            if (pre[j]) dist[i][j] = pre[j] - i;
        pre[page[i]] = i;
    }

    for (int i = 1; i <= n; ++i) {  //开始访问页面，初始是内存中没有分页
        int j;
        int max_dist = 0, p;
        for (j = 1; j <= m; ++j) {
            if (block[j] == -1) {  //改块没有放入页面，则直接放入, 产生缺页
                block[j] = page[i];
                cout << "页面" << page[i] << "不在内存，直接放入物理块" << j
                     << "中!" << endl;
                page_lack++;
                break;
            } else if (block[j] == page[i])  //页面存在内存中
                break;

            if (max_dist < dist[i][block[j]]) {
                max_dist = dist[i][block[j]];  //说明block[j]
                                               //对应的页面以后会长时间不会用到
                p = j;  // block[] 第j个页面会被替换掉
            }
        }
        if (j >
            m) {  //此时内存中不能在放入新的分页，而且没有找到page[i]对应的分页，接下来进行页面替换
            cout << "页面" << page[i] << "不在内存，将物理块" << p << "中的页面"
                 << block[p] << "替换掉!" << endl;
            block[p] = page[i];
            page_lack++;
        }
        cout << endl << "当前内存中页面的情况:" << endl;
        for (int k = 1; k <= m; ++k)  //内存中页面加载情况
            cout << block[k] << " ";
        cout << endl << endl;
    }
    return page_lack;  //返回缺页次数
}

int lru() {  //最近最久未使用算法和opt算法差不多，只不过是lru是向前看，
             //opt是向后看
    int page_lack = 0;
    memset(pre, 0, sizeof(pre));
    memset(dist, 0x3f, sizeof(dist));
    memset(block, -1, sizeof(block));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= page_max; ++j)
            if (pre[j]) dist[i][j] = i - pre[j];
        pre[page[i]] = i;
    }

    for (int i = 1; i <= n; ++i) {  //开始访问页面，初始是内存中没有分页
        int j;
        int max_dist = 0, p;
        for (j = 1; j <= m; ++j) {
            if (block[j] == -1) {  //改块没有放入页面，则直接放入, 产生缺页
                block[j] = page[i];
                cout << "页面" << page[i] << "不在内存，直接放入物理块" << j
                     << "中!" << endl;
                page_lack++;
                break;
            } else if (block[j] == page[i])  //页面存在内存中
                break;

            if (max_dist < dist[i][block[j]]) {
                max_dist = dist[i][block[j]];  //说明block[j]
                                               //对应的页面以后会长时间不会用到
                p = j;  // block[] 第j个页面会被替换掉
            }
        }
        if (j >
            m) {  //此时内存中不能在放入新的分页，而且没有找到page[i]对应的分页，接下来进行页面替换
            cout << "页面" << page[i] << "不在内存，将物理块" << p << "中的页面"
                 << block[p] << "替换掉!" << endl;
            block[p] = page[i];
            page_lack++;
        }
        cout << endl << "当前内存中页面的情况:" << endl;
        for (int k = 1; k <= m; ++k)  //内存中页面加载情况
            cout << block[k] << " ";
        cout << endl << endl;
    }
    return page_lack;  //返回缺页次数
}

set<int> page_set;
int fifo() {  //先进先出页面置换算法
    int page_lack = 0;
    memset(block, -1, sizeof(block));
    int index = 1;
    for (int i = 1; i <= n; ++i) {
        if (index > m) index = 1;
        set<int>::iterator it;
        it = page_set.find(page[i]);
        if (it == page_set.end()) {
            if (block[index] != -1) page_set.erase(block[index]);
            page_set.insert(page[i]);
            block[index++] = page[i];
            ++page_lack;
        }
        for (int k = 1; k <= m; ++k) cout << block[k] << " ";
        cout << endl;
    }
    return page_lack;
}

int nru[N];            //表示 物理块 i 最近时候被访问过
int page_in_block[N];  //页面 i 在 block的下标索引
int clock() {
    int index = 1;
    int page_lack = 0;
    memset(block, -1, sizeof(block));
    for (int i = 1; i <= n; ++i) {
        if (page_in_block[page[i]]) {  //如果page[i]已经在内存中
            nru[page_in_block[page[i]]] =
                1;  //重新标记这个物理块中的页面被访问过了
            cout << endl
                 << "第" << i << "次: 页面" << page[i] << "已经存在物理块"
                 << page_in_block[page[i]] << "中!" << endl;
        } else {
            while (true) {
                if (index > m) index = 1;
                if (block[index] == -1) {
                    nru[index] = 1;
                    page_in_block[page[i]] = index;
                    block[index++] = page[i];
                    ++page_lack;
                    break;
                }
                if (block[index] == page[i]) {
                    nru[index++] = 1;
                    break;
                } else {
                    if (nru[index] == 0) {  //替换该页面
                        nru[index] = 1;
                        page_in_block[block[index]] = 0;
                        cout << endl
                             << "第" << i << "次: 物理块" << index << "中的页面"
                             << block[index] << "最近未被使用，将要被页面"
                             << page[i] << "替换!" << endl;
                        page_in_block[page[i]] = index;
                        block[index++] = page[i];
                        ++page_lack;
                        break;
                    } else
                        nru[index++] = 0;
                }
            }
        }
        for (int k = 1; k <= m; ++k) cout << block[k] << " ";
        cout << endl;
    }
    return page_lack;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> page[i];
        page_max = max(page_max, page[i]);
    }
    cout << "opt缺页中断次数:" << opt() << endl;
    cout << "***********************************" << endl;
    cout << "lru缺页中断次数:" << lru() << endl;
    cout << "***********************************" << endl;
    cout << "fifo缺页中断次数:" << fifo() << endl;
    cout << "***********************************" << endl;
    cout << "clock缺页中断次数:" << clock() << endl;
    return 0;
}
