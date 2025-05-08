## 进程调度PV操作



#### PV操作

PV操作是典型的同步机制之一， PV操作与信号量的处理相关，P表示通过的意思，V表示释放的意思。PV操作即可实现同步，也可以实现互斥。

* P操作意味着请求分配一个资源 : 也称为down()/wait()操作,P(S) 使S=S-1,若S<0,**进程暂停执行,放入信号量的等待队列**.

* V操作意味着释放一个资源 : 也称为up()/signal()操作,V(S) 使S=S+1,若S<=0,**唤醒等待队列中的一个进程**.

#### 关于抢占式和非抢占式

* 抢占式：  v释放资源 资源数<=0  唤醒对队列中的进程，转到唤醒的进程
* 非抢占式： v释放资源 资源数<=0   唤醒对队列中的进程，继续执行当前进程





#### 对两个例题进行展示

**抢占式**
在H5体现抢占式，此时N=0，唤醒Y进程，Y进程抢占式，因此先执行Y进程Y6 后 H6

![抢占式.png](https://i.loli.net/2020/05/13/UzbDwkaJ9dpMo3m.png)

<hr>

**抢占式**
在E3体现非抢占式，此时Q=0，唤醒X进程，X进程是非抢占式，因此继续执行E进程 E4

![非抢占式.png](https://i.loli.net/2020/05/13/prNMa8mDC5IWoi9.png)



<hr>

不准备添加c/c++代码实现，python版本规划中


# coding=gbk
# 优先级设置（Y优先级高于X）
priority_order = "Y"

# 进程X的指令序列（带变量操作）
process_x = [
    ("X1", "S=35"),
    ("X2", "C=S-C"),
    ("X3", "V(R)"),  # V操作
    ("X4", "S=C-E"),
    ("X5", "P(H)"),  # P操作
    ("X6", "E=C-S")
]

# 进程Y的指令序列
process_y = [
    ("Y1", "E=22"),
    ("Y2", "S=E-S"),
    ("Y3", "P(R)"),
    ("Y4", "E=S+C"),
    ("Y5", "V(H)"),
    ("Y6", "C=E-S")
]

# 初始变量值
initial_vars = {'E': 46, 'C': 28, 'S': 47, 'R': 0, 'H': 0}


class Process:
    def __init__(self, name, priority, instructions):
        self.name = name
        self.priority = priority  # 数值越大优先级越高
        self.instructions = instructions  # 指令列表
        self.pc = 0  # 程序计数器
        self.state = 'ready'


class Scheduler:
    def __init__(self):
        self.vars = {'E': 0, 'C': 0, 'S': 0, 'R': 0, 'H': 0}
        self.ready_queue = []  # 按优先级排序的就绪队列
        self.blocked_queue = []  # 阻塞队列
        self.execution_log = []  # 执行记录
        self.variable_log = []  # 变量变化记录

    def parse_operation(self, instr):
        """解析指令操作（支持算术运算和信号量操作）"""
        if instr.startswith(('V(', 'P(')):
            semaphore = instr[2]
            value = 1 if instr.startswith('V') else -1
            self.vars[semaphore] += value
            # V操作时触发唤醒（参考网页8）
            if instr.startswith('V'):
                self.wake_blocked_processes(semaphore)
            return f"{'↑' if value > 0 else '↓'}信号量{semaphore}={self.vars[semaphore]}"
        else:
            var, expr = instr.split('=')
            try:
                self.vars[var] = eval(expr, {}, self.vars)
            except:
                self.vars[var] = int(expr)
            return ""

    def wake_blocked_processes(self, semaphore):
        """唤醒因指定信号量阻塞的进程（参考网页4、8）"""
        wake_list = []
        for p in self.blocked_queue:
            if p.instructions[p.pc - 1][1].startswith(f'P({semaphore})'):
                if self.vars[semaphore] >= 0:
                    wake_list.append(p)

        for p in wake_list:
            self.blocked_queue.remove(p)
            p.state = 'ready'
            self.ready_queue.insert(0, p)  # 按优先级插入队列头部

    def execute_step(self, process):
        """执行单条指令"""
        instr_name, operation = process.instructions[process.pc]

        # 记录执行前状态
        prev_vars = self.vars.copy()

        # 执行操作
        desc = self.parse_operation(operation)

        # 处理信号量阻塞（参考网页6、7）
        if operation.startswith('P('):
            semaphore = operation[2]
            if self.vars[semaphore] < 0:
                process.state = 'blocked'
                desc = f"{process.name}等待{semaphore}（{semaphore}={self.vars[semaphore]}）"

        # 记录执行日志
        self.execution_log.append(instr_name)
        self.variable_log.append({
            'step': instr_name,
            **self.vars.copy(),
            'desc': desc,
            'process': process.name
        })

        process.pc += 1
        return process.state != 'blocked'

    def schedule(self, processes):
        """调度主循环（参考网页5、8）"""
        # 初始化就绪队列
        self.ready_queue = sorted(processes, key=lambda p: -p.priority)

        while self.ready_queue or self.blocked_queue:
            # 处理信号量唤醒（参考网页4）
            if not self.ready_queue and self.blocked_queue:
                for sem in ['R', 'H']:
                    self.wake_blocked_processes(sem)

            if not self.ready_queue:
                continue  # 等待信号量唤醒

            # 选择优先级最高的进程
            current = self.ready_queue.pop(0)
            current.state = 'running'

            # 执行当前指令
            can_continue = self.execute_step(current)

            # 更新进程状态
            if can_continue and current.pc < len(current.instructions):
                current.state = 'ready'
                self.ready_queue.insert(0, current)  # 保持优先级抢占
            elif current.state == 'blocked':
                self.blocked_queue.append(current)

            # 维护就绪队列优先级（参考网页5）
            self.ready_queue.sort(key=lambda p: -p.priority)

    def print_report(self):
        """输出执行报告"""
        print("【执行顺序】")
        print(" -> ".join(self.execution_log))

        print("\n【变量变化过程】")
        print(f"{'步骤':<6} | {'进程':<4} | {'E':<6} | {'C':<6} | {'S':<6} | {'R':<6} | {'H':<6} | 操作说明")
        print("-" * 90)
        for log in self.variable_log:
            print(
                f"{log['step']:<6} | {log['process']:<4} | {log['E']:<6} | {log['C']:<6} | {log['S']:<6} | {log['R']:<6} | {log['H']:<6} | {log['desc']}")


# 使用示例
if __name__ == "__main__":
    # 初始化进程
    processes = [
        Process('X', 1, process_x),  # 优先级1
        Process('Y', 2, process_y)  # 优先级2
    ]

    # 初始化调度器
    scheduler = Scheduler()
    scheduler.vars = initial_vars.copy()
    scheduler.schedule(processes)

    # 输出结果
    scheduler.print_report()
