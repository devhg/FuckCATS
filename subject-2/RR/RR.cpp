#include <iostream>
#include <vector>
using namespace std;
struct Node {
    char name;
    int Tarrive;      //到达时间
    int Tservice;     //服务时间
    int Tsurplus;     //剩余时间
    int Tstart;       //开始时间
    int Taccomplish;  //完成时间
    int prio;         //优先级---数字越大优先级越高
    int if_finish;    //进程是否完成
    int num;          //进程个数
} job[10];

vector<int> Safeorder;  //表示安全序列

//按到达时间排序
void Arrive_sort(int num) {
    int temp1, temp2, temp3;
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            if (job[i].Tarrive > job[j].Tarrive) {
                temp1 = job[j].name;
                job[j].name = job[i].name;
                job[i].name = temp1;
                temp2 = job[j].Tarrive;
                job[j].Tarrive = job[i].Tarrive;
                job[i].Tarrive = temp2;
                temp3 = job[j].Tservice;
                job[j].Tservice = job[i].Tservice;
                job[i].Tservice = temp3;
            }
        }
    }
}

void RR(int num)  // RR算法
{
    int q;
    cout << "请输入时间片长度：" << endl;
    cin >> q;
    int flag = 1;        //标志队列中是否还有进程
    int finish_pro = 0;  //完成的进程数
    cout << "进程名称\t"
         << "开始时间\t"
         << "运行时间\t"
         << "剩余服务时间\t"
         << "结束时间\t" << endl;
    int time;  //记录当前时刻时间
    int c = 0;
    while (finish_pro < num) {
        flag = 0;  //就绪队列里没进程
        for (int i = c; i < num; i++) {
            Arrive_sort(num);
            job[i].Tsurplus = job[i].Tservice;
            job[i].Tstart = job[i - 1].Taccomplish;  //上一个作业结束时间
            if (job[i].Tstart < job[i].Tarrive)  //该作业的开始时间小于到达时间
            {
                job[i].Tstart = job[i].Tarrive;
            } else {
                job[i].Tstart = job[i - 1].Taccomplish;
            }
            time = job[i].Tstart;
            if (job[i].if_finish == 1) {
                continue;  //该进程已完成
            } else {
                if (job[i].Tsurplus <= q &&
                    time >= job[i].Tarrive)  //未完成且少于一个时间片
                {
                    flag = 1;
                    time = time + job[i].Tsurplus;
                    job[i].if_finish = 1;  //该进程完成
                    job[i].Taccomplish = time;
                    Safeorder.push_back(i);
                    cout << job[i].name << "\t\t"
                         << job[i].Taccomplish - job[i].Tsurplus << "\t\t"
                         << job[i].Tsurplus << "\t\t" << 0 << "\t\t"
                         << job[i].Taccomplish << endl;
                    job[i].Tsurplus = 0;
                } else if (job[i].Tsurplus > q && time >= job[i].Tarrive) {
                    flag = 1;
                    time = time + q;
                    job[i].Tsurplus -= q;
                    job[i].Taccomplish = time;
                    cout << job[i].name << "\t\t" << time - q << "\t\t" << q
                         << "\t\t" << job[i].Tsurplus << "\t\t"
                         << job[i].Taccomplish << endl;
                    job[num].name = job[i].name;
                    job[num].Tarrive = time;
                    job[num].Tservice = job[i].Tsurplus;
                    num++;
                }
                if (job[i].if_finish == 1) {
                    finish_pro++;
                }  //一个进程完成加一
            }
            c++;
        }
        break;
        if (flag == 0 && finish_pro < num)  //没执行完且没进入就绪队列
        {
            for (int i = 0; i < num; i++) {
                if (job[i].if_finish == 0) {
                    time = job[i].Tarrive;
                    break;
                }
            }
        }
    }
}
//输出
void print(int num) {
    cout << "进程名"
         << "\t"
         << "到达时间"
         << "\t"
         << "服务时间"
         << "\t"
         << "完成时间" << endl;

    for (int i = 0; i < num; i++) {
        cout << job[i].name << "\t" << job[i].Tarrive << "\t\t"
             << job[i].Tservice << "\t\t" << job[i].Taccomplish << endl;
    }
}
void display(int num) { RR(num); }
int main() {
    int num;
    char jname;
    int arrive;
    int service;
    int accomplish;
    cout << "请输入进程个数：" << endl;
    cin >> num;
    for (int i = 0; i < num; i++) {
        cout << "请输入进程名、到达时间、服务时间" << endl;
        cin >> jname;
        job[i].name = jname;
        cin >> arrive;
        job[i].Tarrive = arrive;
        cin >> service;
        job[i].Tservice = service;
    }
    display(num);
    return 0;
}
