## 时间片轮转调度算法RR q=x

* 建议使用 [RRN.cpp](RRN.cpp)
* [RR.cpp](RR.cpp)为半成品，只完成了gantt chart



#### 过程展示

```shell
请输入进程个数：5
请输入时间片q：4
请输入进程 1 到达时间、服务时间(空格隔开)：0 19
请输入进程 2 到达时间、服务时间(空格隔开)：2 18
请输入进程 3 到达时间、服务时间(空格隔开)：7 16
请输入进程 4 到达时间、服务时间(空格隔开)：12 12
请输入进程 5 到达时间、服务时间(空格隔开)：13 8
Total time: 73   
Gantt chart如下：
0 (P1) 4
 (P2) 8
 (P1) 12
 (P3) 16
 (P2) 20
 (P4) 24
 (P1) 28
 (P5) 32
 (P3) 36
 (P2) 40
 (P4) 44
 (P1) 48
 (P5) 52
 (P3) 56
 (P2) 60
 (P4) 64
 (P1) 67
 (P3) 71
 (P2) 73

Process    Finish Time     Arrival Time    Turnaround Time         Service Time    Wr
P5              52                13              39                     8          4.8750000000
P4              64                12              52                     12         4.3333333333
P1              67                0               67                     19         3.5263157895
P3              71                7               64                     16         4.0000000000
P2              73                2               71                     18         3.9444444444
T=58.6000000000
W=4.1358187135
```



来源自：某群