/**
 * author: QXQZX
 * date: 2020/5/13 12:34
 * description: 银行家算法实现 修改自网络
 * License: MIT
 * other: FuckCATS plan
 **/
#include <iostream>
#include <vector>
using namespace std;

#define MAX 20

int n_process;             //表示进程的个数
int n_resource;            //表示资源的个数
int Resource[MAX];         //表示资源的总数
int Max[MAX][MAX];         //表示进程对每类资源的最大需求量
int Allocation[MAX][MAX];  //表示系统给进程已分配每类资源的数目
int Need[MAX][MAX];        //表示进程还需各类资源数目
int Available[MAX];        //表示系统当前剩下的资源
int Work[MAX];             //表示安全性检查的中间变量
bool Finish[MAX];          //表示资源是否被安全性检查过
vector<int> Safeorder;     //表示安全序列

void Menu() {
    cout << "------------------Banker----------------------" << endl;
    cout << "*              1.初始化数据                  *" << endl;
    cout << "*              2.显示资源分配情况            *" << endl;
    cout << "*              3.申请资源并生成安全序列       *" << endl;
    cout << "*              4.退出                        *" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "请选择：";
}

void checkInit() {
    if (n_resource)
        for (int i = 0; i < n_process; i++) {
            for (int j = 0; j < n_resource; j++) {
                if (Max[i][j] < 0)
                    cout << "Max[" << i << "][" << j << "]输入值小于0！"
                         << endl;
                if (Allocation[i][j] < 0)
                    cout << "Allocation[" << i << "][" << j << "]输入值小于0！"
                         << endl;
                if (Allocation[i][j] > Max[i][j])
                    cout << "Allocation[" << i << "][" << j << "]的值大于Max["
                         << i << "][" << j << "]输入值" << endl;
            }
        }
    for (int i = 0; i < n_resource; i++) {
        if (Available[i] < 0)
            cout << "Available[" << i << "]的值小于0！" << endl;
    }
    cout << "输入检查完毕！" << endl;
}

int Init() {
    if (n_resource != 0 && n_process != 0) {
        cout << "你已经初始化过了！" << endl;
        return 1;
    }
    cout << "请分别输入资源个数和进程个数，中间用空格隔开：" << endl;
    cin >> n_resource >> n_process;
    cout << "请输入各个资源的总拥有量(Resource)：" << endl;
    for (int i = 0; i < n_resource; i++) cin >> Resource[i];
    for (int i = 0; i < n_process; i++) {
        cout << "P" << i << "对各个资源的最大需求量(Max)：" << endl;
        for (int j = 0; j < n_resource; j++) cin >> Max[i][j];
        cout << "P" << i << "各个资源已分配量(Allocation)：" << endl;
        for (int j = 0; j < n_resource; j++) cin >> Allocation[i][j];
        for (int j = 0; j < n_resource; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
    }
    for (int i = 0; i < n_resource; i++) {
        int sum[MAX] = {0};
        for (int j = 0; j < n_process; j++) {
            if (i == 0) sum[i] += Allocation[j][i];
            if (i == 1) sum[i] += Allocation[j][i];
            if (i == 2) sum[i] += Allocation[j][i];
        }
        Available[i] = Resource[i] - sum[i];
    }
    checkInit();
    return 1;
}

bool Safecheck() {
    Safeorder.clear();
    for (int i = 0; i < n_resource; i++) Work[i] = Available[i];
    for (int i = 0; i < n_process; i++) Finish[i] = false;

    //开始安全性检查
    int count = 0;

    for (int k = 0; k < n_process; k++) {
        for (int i = 0; i < n_process; i++) {
            if (Finish[i] == false) {
                count = 0;
                for (int j = 0; j < n_resource; j++) {
                    if (Need[i][j] <= Work[j]) count++;
                }
                if (count == n_resource) {
                    for (int j = 0; j < n_resource; j++) {
                        Work[j] = Work[j] + Allocation[i][j];
                    }
                    Finish[i] = true;
                    Safeorder.push_back(i);
                }
            }
        }
    }
    count = 0;
    for (int i = 0; i < n_process; i++) {
        if (Finish[i] == true) count++;
    }
    if (count == n_process)
        return true;
    else
        return false;
}

int Order() {
    int n = -1;                          //请求资源的进程号
    int *Request = new int[n_resource];  //表示请求的各个资源数量
    cout << "请输入第一个满足条件的进程Need(各资源均小于Available)的进程号：";
    cin >> n;
    cout << "请输入满足条件进程Need各资源的数量 空格隔开：" << endl;
    for (int i = 0; i < n_resource; i++) cin >> Request[i];

    //开始判断
    for (int i = 0; i < n_resource; i++) {
        if (Need[n][i] < Request[i]) {
            cout << "好啊你敢骗我，需求量比你的最大需求量还大！玩泥巴去吧！"
                 << endl;
            return 1;
        }
    }
    for (int i = 0; i < n_resource; i++) {
        if (Available[i] < Request[i]) {
            cout << "系统已经满足不了你了，你走吧！" << endl;
            return 1;
        }
    }
    //试分配资源给请求进程，并做安全性检查
    for (int i = 0; i < n_resource; i++) {
        Available[i] -= Request[i];
        Allocation[n][i] += Request[i];
        Need[n][i] -= Request[i];
    }
    bool Is_safe = Safecheck();
    if (Is_safe == true) {
        cout << "系统已经分配资源给P" << n << "进程了！" << endl;
        cout << "其中一个安全序列为：" << endl;
        for (int i = 0; i < Safeorder.size(); i++) {
            cout << "P" << Safeorder.at(i) << "->";
        }
        cout << "End" << endl;
    }
    //恢复试分配之前的现场
    for (int i = 0; i < n_resource; i++) {
        Available[i] += Request[i];
        Allocation[n][i] -= Request[i];
        Need[n][i] += Request[i];
    }

    return 1;
}

void Display() {
    cout << endl;
    cout << "进程 \t Max \t Allocation\tNeed\tAvailable" << endl;
    for (int i = 0; i < n_process; i++) {
        cout << " P" << i << " \t";
        for (int j = 0; j < n_resource; j++) {
            cout << Max[i][j] << " ";
        }
        cout << "\t   ";
        for (int j = 0; j < n_resource; j++) {
            cout << Allocation[i][j] << " ";
        }
        cout << "\t   ";
        for (int j = 0; j < n_resource; j++) {
            cout << Need[i][j] << " ";
        }
        cout << "\t  ";
        for (int j = 0; i == 0 && j < n_resource; j++) {
            cout << Available[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void ShowTable() {
    cout << "Prog*\t\t"
         << "Work\t\t"
         << "Need\t\t"
         << "Allo*\t\t"
         << "W + A\t\t"
         << "Finish" << endl;
    for (int k = 0; k < Safeorder.size(); k++) {
        cout << "P" << Safeorder.at(k) << "\t";
        int i = Safeorder.at(k);
        for (int j = 0; j < n_resource; j++) {
            cout << Available[j] << " ";
        }
        cout << "\t\t";
        for (int j = 0; j < n_resource; j++) {
            cout << Need[i][j] << " ";
        }
        cout << "\t\t";
        for (int j = 0; j < n_resource; j++) {
            cout << Allocation[i][j] << " ";
            Available[j] += Allocation[i][j];
        }
        cout << "\t\t";
        for (int j = 0; j < n_resource; j++) {
            cout << Available[j] << " ";
        }
        cout << "\t\t"
             << "true" << endl;
    }
    cout << "End" << endl;
}
int main() {
    int choose = 0;
    while (1) {
        Menu();
        cin >> choose;
        switch (choose) {
            case 1:
                Init();
                break;
            case 2:
                Display();
                break;
            case 3:
                Order();
                ShowTable();
                break;
            case 4:
                cout << "系统已退出！";
                return 1;
            default:
                cout << "就1-4这你都能输错？？？" << endl;
                break;
        }
    }
}