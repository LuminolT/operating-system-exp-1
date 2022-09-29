# 实验3 - 进程管理和进程通信

1、4、7：Gu

2、5、8：Lian

3、6、9：Chen

> 完成对应题目和思考（思考贴相关资料或者简要说明）

### 注意

Fork Repository后自行完成

commit格式：`<operations>: <content>`

例：`Update: subexp-1`，`Finish: 1,4,7`

完成后Pull Request到`master`分支

### New Quests

1. subexp10 多缓存 多进程
2. lockf对锁定管道的效果
3. 多进程

### 思考题

## 1

## 2

- 子进程由父进程通过fork()函数创建产生，通过exit()函数或者主函数的return()自我结束。子进程被创建后，核心为其分配一个进程表项和进程标识符pid，检查同时运行的进程数目，并拷贝父进程的进程表项的数据，由子进程继承父进程的所有文件。

## 3

- subexp-3-1.c
- subexp-3-2.c

## 4

## 5

- 子进程被创建后，对父进程的运行环境无影响。因为子进程被创建后，他拥有独立的代码段和数据段，并可以对其单独修改。而父进程的代码段和数据段不会随着子进程代码段和数据段的改变而受到影响。

## 6

- subexp-6.c

## 7

## 8

- 还可以通过管道操作或者用信号量机制来实现。信号量是一个整形计数器，用来控制多个进程对共享资源的访问。或者通过消息队列信号机制，通过向消息队列发送信息、接收信息来实现进程间的通信。

## 9

- subexp-9.c

## 10
