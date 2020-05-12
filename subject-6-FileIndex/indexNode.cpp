/**
 * author: jk1804匿名同学
 * date: 2020/5/12 12:44
 * description: 专题6文件索引算法实现
 * License: MIT
 * other: FuckCATS plan
 **/

#include <cmath>
#include <iostream>
using namespace std;
void pro(double i) {
    if (i < 1024)
        cout << i;
    else if (i >= 1024 && i < 1024 * 1024) {
        i = i / 1024;
        cout << i << "K";
    } else if (i >= 1024 * 1024 && i < 1024 * 1024 * 1024) {
        i = i / 1024;
        i = i / 1024;
        cout << i << "M";
    } else {
        i = i / 1024;
        i = i / 1024;
        i = i / 1024;
        cout << i << "G";
    }
}
int main() {
    int a, b, c, d, e, f;
    cout << "请输入直接索引地址个数" << endl;
    cin >> a;
    cout << "请输入一级间接地址索引个数" << endl;
    cin >> b;
    cout << "请输入二级间接地址索引个数" << endl;
    cin >> c;
    cout << "请输入每个地址项大小" << endl;
    cin >> d;
    cout << "请输入磁盘ID占位数" << endl;
    cin >> e;
    cout << "请输入磁盘索引块（磁盘数据块）大小" << endl;
    cin >> f;
    cout << "结果:" << endl;
    long double i = a * f, j = b * f * (f / d), k = c * f * (f / d) * (f / d),
                q;
    cout << "(1)" << endl;
    cout << "L0 = " << a << "*" << f << " = ";
    pro(i);
    cout << endl;
    cout << "L1 = " << b << "*" << f << "/" << d << "*" << f << " = ";
    pro(j);
    cout << endl;
    cout << "L2 = " << c << "*" << f << "/" << d << "*" << f << "/" << d << "*"
         << f << " = ";
    pro(k);
    cout << endl << endl;
    cout << "MaxL= L0+L1+L2 = ";
    pro(i);
    cout << "+";
    pro(j);
    cout << "+";
    pro(k);
    cout << endl;
    q = pow(2, d * 8 - e) * f;
    cout << endl << "(2)" << endl;
    cout << "MaxP= pow(2," << d << "*"
         << "8"
         << "-" << e << ")*" << f << " = ";
    pro(q);
    cout << endl;
    return 0;
}
