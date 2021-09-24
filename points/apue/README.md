# UNIX高级环境编程
<center>inux下一切皆文件</center>

- [UNIX高级环境编程](#unix高级环境编程)
  - [第一章 UNIX基础知识](#第一章-unix基础知识)
      - [1.UNIX体系结构](#1unix体系结构)
      - [2.登陆](#2登陆)
      - [3.shell](#3shell)
      - [4.文件和目录](#4文件和目录)
      - [5.输入与输出](#5输入与输出)
      - [6.程序和进程](#6程序和进程)
## 第一章 UNIX基础知识

#### 1.UNIX体系结构
```
内核：控制计算机硬件资源，提供程序运行环境。
系统调用：内核的接口统称为系统调用。
公用函数库：建立在系统调用接口之上。
shell：特殊的应用程序，为其他的应用程序提供了一个接口。
应用程序：操作系统包含了内核和一些其他软件，这些其他软件能使计算机发挥作用，并使计算机拥有自己的特性。
```

#### 2.登陆
```
口令文件：/etc/passwd 
nick:x:1000:1000:Nick,,,:/home/nick:/bin/bash 
登陆名：加密口令：数字用户ID：数字组ID：注释字段：起始目录：shell程序
```

#### 3.shell
```
Bourne shell    /bin/sh
Bourne-again shell      /bin/bash
C shell     /bin/csh
Korn shell      /bin/ksh
THENEX C shell  /bin/tcsh
```

#### 4.文件和目录
```
root   “/”
绝对路径和相对路径
```
```myls.c
#include "apue.h"  // 自写头文件
#include <dirent>  // /usr/include/dirent.h

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;
    if (argc != 2) {
        err_quit("usage: is directory_name");
    }

    if ((dp = opendir(argv[1])) == NULL)
        err_sys("can't open %s", argv[1]);
    while ((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);
    closedir(dp);
    exit(0);
}

```

#### 5.输入与输出
```
标准输入
标准输出
标准错误

不带缓冲的I/O:函数open、read、write、lseek以及close提供了不带缓冲的I/O
标准I/O:printf，getc，putc
标准I/O常量:stdin和stdout
文件描述符：简称fd，当应用程序请求内核打开/新建一个文件时，内核会返回一个文件描述符用于对应这个打开/新建的文件，其fd本质上就是一个非负整数，读写文件也是需要使用这个文件描述符来指定待读写的文件的
```

#### 6.程序和进程
```
程序:是一个存储在磁盘上某个目录中的可执行文件。
进程:执行的实例。
进程ID:唯一标识符。

进程控制的主要三个函数fork，exec，waitpid。
```
```process.c
#include <apue.h>
#include <sys/wait.h>

int main()
{
    char    buf[MAXLINE];
    pid_t   pid;
    int     status;

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {    /* 标准输入获取 */
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;
    

        if ((pid = fork()) < 0) {   
            err_sys("fork_error");
        } else if (pid == 0) {
            execlp(buf, buf, (char *)0);    /* 执行从标准输入读入的命令 */
            err_ret("could't execute : %s", buf);
            exit(127);
        }
        
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
            
        printf("%% ");

    }    
    exit(0);
}

```







