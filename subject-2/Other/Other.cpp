/**
 * author: QXQZX
 * date: 2020/5/22 13:57
 * description: FCFS SJF HRRN算法实现
 * License: MIT
 * other: FuckCATS plan
 **/
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
#define MAX 100

typedef struct JCB {
    char job_id[10];   //作业ID
    float Arr_time;    //到达时刻
    float Fun_time;    //估计运行时间
    float Wait_time;   //等待时间
    float Start_time;  //开始时刻
    float Fin_time;    //完成时刻
    float Tur_time;    //周转时间
    float WTur_time;   //带权周转时间
    int Order;         //优先标记
} list;
bool cmp(list a, list b) { return a.Order < b.Order; }

//先来先服务算法
void fcfs(list *p, int count) {
    list temp;  //临时结构体变量
    int i;
    int j;

    for (i = 1; i < count; i++)  //按到达时刻直接插入排序
    {
        temp = p[i];
        j = i - 1;

        while (temp.Arr_time < p[j].Arr_time && j >= 0) {
            p[j + 1] = p[j];
            --j;
        }
        p[j + 1] = temp;
    }

    for (i = 0; i < count; i++)  //循环计算各个作业的时间值
    {
        if (i == 0) {
            p[i].Start_time = p[i].Arr_time;
        } else {
            p[i].Start_time =
                p[i - 1].Fin_time;  //开始时刻==前一个作业的完成时刻
        }
        p[i].Wait_time = p[i].Start_time - p[i].Arr_time;  //等待==开始-到达
        p[i].Fin_time = p[i].Start_time + p[i].Fun_time;  //完成==开始+运行
        p[i].Tur_time = p[i].Fin_time - p[i].Arr_time;    //周转=完成-到达
        p[i].WTur_time = p[i].Tur_time / p[i].Fun_time;  //带权周转=周转/运行
    }

    return;
}
//最短作业优先算法（sjf）
void sjf(list *p, int count) {
    list item;      //结构体变量
    int k = 0;      //最短运行时间作业的下标
    int flag = 0;   //优先级设置
    float min = 0;  //最短运行时间
    float temp;     //开始的时刻

    temp = p[0].Arr_time;

    //先求出最先到达作业的时刻
    for (int i = 0; i < count; i++) {
        if (temp > p[i].Arr_time) {
            temp = p[i].Arr_time;  //保存最先到达的作业的时刻
            k = i;  //最先到达的作业的下标，默认为p[0]
        }
    }

    for (int i = 0; i < count; i++) {
        p[k].Order = ++flag;  //设置优先级为1，最高优先级

        p[k].Start_time = temp;
        p[k].Wait_time = temp - p[k].Arr_time;  //计算各个时间
        p[k].Fin_time = temp + p[k].Fun_time;
        p[k].Tur_time = p[k].Fin_time - p[k].Arr_time;
        p[k].WTur_time = p[k].Tur_time / p[k].Fun_time;

        min = 100;

        temp = p[k].Fin_time;  //后一个作业的开始时刻是前一个作业的完成时刻

        for (int j = 0; j < count; j++) {
            if (p[j].Order != 0 ||
                temp - p[j].Arr_time <=
                    0)  //跳过不满足条件的（已设置优先级的 和
                        //到达时刻要晚于前一个作业的完成时刻的）
                continue;
            if (min > p[j].Fun_time) {
                min = p[j].Fun_time;
                k = j;  //求出满足条件最短运行时间的作业的下标
            }
        }
    }
    //按优先级排序
    sort(p, p + count, cmp);
    return;
}

//最高响应比优先算法
void hrn(list *p, int count) {
    list item;      //结构体变量
    int k = 0;      //最高响应比作业的下标
    int flag = 0;   //优先级设置
    float max = 0;  //最大响应比的值
    float temp;     //开始的时刻

    temp = p[0].Arr_time;

    //先求出最先到达作业的时刻
    for (int i = 0; i < count; i++) {
        if (temp > p[i].Arr_time) {
            temp = p[i].Arr_time;
            k = i;  //最先到达的作业的下标，默认为p[0]
        }
    }

    for (int i = 0; i < count; i++) {
        p[k].Order = ++flag;  //设置优先级

        p[k].Start_time = temp;  //计算各个作业的时间
        p[k].Wait_time = temp - p[k].Arr_time;
        p[k].Fin_time = temp + p[k].Fun_time;
        p[k].Tur_time = p[k].Fin_time - p[k].Arr_time;
        p[k].WTur_time = p[k].Tur_time / p[k].Fun_time;

        max = 0;

        temp = p[k].Fin_time;

        for (int j = 0; j < count; j++) {
            //排除优先级已设置 和 晚于作业完成时刻到达的
            if (p[j].Order != 0 || temp - p[j].Arr_time <= 0) continue;
            if (max < (temp - p[j].Arr_time) / p[j].Fun_time) {
                max = (temp - p[j].Arr_time) / p[j].Fun_time;
                k = j;  //求出剩下响应比最高的作业的下标
            }
        }
    }
    //按调度顺序排序
    sort(p, p + count, cmp);
    return;
}
//输出各个作业的详细信息
void print(list *p, int count) {
    printf(
        "*****************************************************************\n");
    printf("ID\t到达\t服务\t等待\t开始\t完成\t周转\t带权周转\n");

    for (int i = 0; i < count; i++) {
        printf("%s\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\n", p[i].job_id,
               p[i].Arr_time, p[i].Fun_time, p[i].Wait_time, p[i].Start_time,
               p[i].Fin_time, p[i].Tur_time, p[i].WTur_time);
    }
    return;
}

void avg(list *p, int count) {
    float AvgTur1;  //平均周转
    float AvgTur2;  //平均带权周转
    float t1 = 0;
    float t2 = 0;

    for (int i = 0; i < count; i++) {
        t1 += p[i].Tur_time;   //周转时间和
        t2 += p[i].WTur_time;  //带权周转和
    }

    AvgTur1 = t1 / count;
    AvgTur2 = t2 / count;

    printf("\n平均周转时间为：%f\t平均带权周转时间为：%f\n", AvgTur1, AvgTur2);
    printf(
        "\n*****************************************************************"
        "\n");

    return;
}

int main() {
    list st[MAX];       //最多可以一百个作业
    int job_count = 0;  //作业数量
    int flag = 1;       //算法标记
    int i = 0;

    printf("请输入作业数量：");
    scanf("%d", &job_count);

    printf("请输入作业ID，到达时刻，估计运行时间(用空格隔开)：\n");

    do {
        scanf("%s %f %f", st[i].job_id, &st[i].Arr_time, &st[i].Fun_time);
        st[i].Order = 0;  //优先级初始化

    } while (++i < job_count);

    printf(
        "请选择算法：\n1.先来先服务算法FCFS\n2.最短作业优先算法SJF\n3."
        "最高响应比优先算法HRRN\n");
    scanf("%d", &flag);

    switch (flag) {
        case 1: {
            fcfs(st, job_count);
            printf("\n*******************************************\n\n");
            printf("先来先服务算法FCFS\n");
        } break;

        case 2: {
            sjf(st, job_count);
            printf("\n*******************************************\n\n");
            printf("最短作业优先算法SJF\n");
        } break;
        case 3: {
            hrn(st, job_count);
            printf("\n*******************************************\n\n");
            printf("最高响应比优先算法HRRN\n");
        } break;
    }
    print(st, job_count);
    avg(st, job_count);
    return 0;
}