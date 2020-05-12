/**
 * author: jk1804匿名同学
 * date: 2020/5/12 12:44
 * description: 磁盘调度算法实现 N-Step-SCAN N-Step-CSCAN
 * License: MIT
 * other: FuckCATS plan
 **/

#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int n, a[50], y[50], m, p, i, j, b, c, d, u, o, h, k, v;
    double g, w;
    cout << "请输入依次输入题目中已访问的进程和正在访问的进程" << endl;
    cin >> u >> o;
    if (o > u)
        c = 1;
    else
        c = 0;
    cout << "scan算法请输入0,cscan算法请输入1" << endl;
    cin >> p;
    cout << "请输入N(n-scan, n-cscan)的N" << endl;
    cin >> n;
    cout << "请输入磁道号队列个数" << endl;
    cin >> m;
    cout << "请输入磁道号队列(空格间隔)" << endl;
    for (i = 0; i < m; i++) cin >> a[i];
    v = o;
    b = m / n;
    for (i = 1; i <= b; i++) {
        sort(a + (i - 1) * n, a + i * n);
    }
    sort(a + b * n, a + m);
    if (p == 0) {
        h = 0;
        k = 0;
        while (b != 0) {
            if (c == 1) {
                for (i = n * h; i < n * (h + 1); i++) {
                    d = 0;
                    if (a[i] > o) {
                        d = 1;
                        break;
                    }
                }
                if (d == 1) {
                    if (i != n * h) {
                        for (j = i; j < n * (h + 1); j++) {
                            y[k] = a[j];
                            k++;
                        }
                        for (j = i - 1; j >= n * h; j--) {
                            y[k] = a[j];
                            k++;
                        }
                        c = 0;
                        o = a[n * h];
                    } else {
                        for (j = i; j < n * (h + 1); j++) {
                            y[k] = a[j];
                            k++;
                        }
                        o = a[n * (h + 1) - 1];
                    }
                } else {
                    for (j = n * (h + 1) - 1; j >= n * h; j--) {
                        y[k] = a[j];
                        k++;
                    }
                    c = 0;
                    o = a[n * h];
                }
            } else {
                for (i = n * (h + 1) - 1; i >= n * h; i--) {
                    d = 0;
                    if (a[i] < o) {
                        d = 1;
                        break;
                    }
                }
                if (d == 1) {
                    if (i != n * (h + 1) - 1) {
                        for (j = i; j >= n * h; j--) {
                            y[k] = a[j];
                            k++;
                        }
                        for (j = i + 1; j < n * (h + 1); j++) {
                            y[k] = a[j];
                            k++;
                        }
                        c = 1;
                        o = a[n * (h + 1) - 1];
                    } else {
                        for (j = i; j >= n * h; j--) {
                            y[k] = a[j];
                            k++;
                        }
                        o = a[n * h];
                    }
                } else {
                    for (j = n * h; j < n * (h + 1); j++) {
                        y[k] = a[j];
                        k++;
                    }
                    c = 1;
                    o = a[n * (h + 1) - 1];
                }
            }
            b--;
            h++;
        }
        if (c == 1) {
            for (i = n * h; i < m; i++) {
                d = 0;
                if (a[i] > o) {
                    d = 1;
                    break;
                }
            }
            if (d == 1) {
                if (i != n * h) {
                    for (j = i; j < m; j++) {
                        y[k] = a[j];
                        k++;
                    }
                    for (j = i - 1; j >= n * h; j--) {
                        y[k] = a[j];
                        k++;
                    }
                } else
                    for (j = i; j < m; j++) {
                        y[k] = a[j];
                        k++;
                    }
            } else
                for (j = m - 1; j >= n * h; j--) {
                    y[k] = a[j];
                    k++;
                }
        } else {
            for (i = m - 1; i >= n * h; i--) {
                d = 0;
                if (a[i] < o) {
                    d = 1;
                    break;
                }
            }
            if (d == 1) {
                if (i != m - 1) {
                    for (j = i; j >= n * h; j--) {
                        y[k] = a[j];
                        k++;
                    }
                    for (j = i + 1; j < m; j++) {
                        y[k] = a[j];
                        k++;
                    }
                } else
                    for (j = i; j >= n * h; j--) {
                        y[k] = a[j];
                        k++;
                    }
            } else
                for (j = n * h; j < m; j++) {
                    y[k] = a[j];
                    k++;
                }
        }
        for (i = 0; i < m; i++) cout << y[i] << " ";
        cout << endl;

        w = y[0] - v;
        if (w < 0) w = -w;
        for (i = 1; i < m; i++) {
            if (y[i - 1] > y[i])
                w = w + y[i - 1] - y[i];
            else
                w = w + y[i] - y[i - 1];
        }
        g = w / m;
        cout << " ASL= " << w << "/" << m << " = " << g;
    } else {
        h = 0;
        k = 0;
        while (b != 0) {
            if (c == 1) {
                for (i = n * h; i < n * (h + 1); i++) {
                    d = 0;
                    if (a[i] > o) {
                        d = 1;
                        break;
                    }
                }
                if (d == 1 && i != n * h) {
                    for (j = i; j < n * (h + 1); j++) {
                        y[k] = a[j];
                        k++;
                    }
                    for (j = n * h; j < i; j++) {
                        y[k] = a[j];
                        k++;
                    }
                    o = a[i - 1];
                } else {
                    for (j = n * h; j < n * (h + 1); j++) {
                        y[k] = a[j];
                        k++;
                    }
                    o = a[n * (h + 1) - 1];
                }
            } else {
                for (i = n * (h + 1) - 1; i >= n * h; i--) {
                    d = 0;
                    if (a[i] < o) {
                        d = 1;
                        break;
                    }
                }
                if (d == 1 && i != n * (h + 1) - 1) {
                    for (j = i; j >= n * h; j--) {
                        y[k] = a[j];
                        k++;
                    }
                    for (j = n * (h + 1) - 1; j > i; j--) {
                        y[k] = a[j];
                        k++;
                    }
                    o = a[i + 1];
                } else {
                    for (j = n * (h + 1) - 1; j >= n * h; j--) {
                        y[k] = a[j];
                        k++;
                    }
                    o = a[n * h];
                }
            }
            b--;
            h++;
        }
        if (c == 1) {
            for (i = n * h; i < m; i++) {
                d = 0;
                if (a[i] > o) {
                    d = 1;
                    break;
                }
            }
            if (d == 1 && i != n * h) {
                for (j = i; j < m; j++) {
                    y[k] = a[j];
                    k++;
                }
                for (j = n * h; j < i; j++) {
                    y[k] = a[j];
                    k++;
                }
            } else
                for (j = n * h; j <= m - 1; j++) {
                    y[k] = a[j];
                    k++;
                }
        } else {
            for (i = m - 1; i >= n * h; i--) {
                d = 0;
                if (a[i] < o) {
                    d = 1;
                    break;
                }
            }
            if (d == 1 && i != m - 1) {
                for (j = i; j >= n * h; j--) {
                    y[k] = a[j];
                    k++;
                }
                for (j = m - 1; j > i; j--) {
                    y[k] = a[j];
                    k++;
                }
            } else {
                for (j = m - 1; j >= n * h; j--) {
                    y[k] = a[j];
                    k++;
                }
            }
        }
        for (i = 0; i < m; i++) cout << y[i] << " ";
        cout << endl;

        w = y[0] - v;
        if (w < 0) w = -w;
        for (i = 1; i < m; i++) {
            if (y[i - 1] > y[i])
                w = w + y[i - 1] - y[i];
            else
                w = w + y[i] - y[i - 1];
        }
        g = w / m;
        cout << " ASL= " << w << "/" << m << " = " << g;
    }
    return 0;
}
