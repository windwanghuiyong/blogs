# elf 文件

1. elf(exective linked file) 格式文件是一种为 Linux 系统所采用的通用文件格式, 支持动态链接和重定位, 有很大的文件头
2. flat 格式文件是扁平格式的文件, 对文件头和一些段信息做了简化, 可执行程序小, 适于嵌入式系统
3. elf2flt 就是将 elf 格式转换为 flt 格式, 在编译器链接的时候可使用 “-elf2flt” 选项直接编译出 flt 格式的可执行文件

## elf 文件的种类

1. 可重定位文件(relocatable file), 包括用户目标文件和其他目标文件(例如 \*.o 或 lib\*.a), 他们一起用于创建可执行文件或者共享目标文件
2. 可执行文件(executable file), 指编译好的可执行文件(例如 a.out), 用于生成程序映像, 载入内存执行
3. 共享目标文件, 指共享库文件(例如 lib\*.so), 用于和其他共享目标文件或者可重定位文件一起生成 elf 目标文件或者和执行文件一起创建程序映像

## elf 文件的作用

elf 文件参与程序的链接和执行, 所以可以从不同的角度来看待 elf 格式文件的作用

1. 如果用于编译和链接(可重定位文件), 则编译器和链接器将把 elf 文件看作是节头表(section-headers)描述的节的集合, 程序头表(program-headers)可选
2. 如果用于加载执行(可执行文件), 则加载器将把 elf 文件看作是程序头表(program-headers)描述的段的集合, 一个段可能包含多个节, 节头表(section-headers)可选
3. 如果是共享目标文件, 则两者都含有, 因为编译时需要共享库中函数的声明, 程序执行函数调用时也需要执行共享库中的代码

## elf 文件的组成

elf 文件头(file-header)描述 elf 文件的总体信息

1. 系统相关: elf 文件标识的魔术数, 以及硬件和平台等相关信息, 增加了 elf 文件的移植性, 使交叉编译成为可能
2. 类型相关: 可重定向文件, 可执行文件, 共享目标文件
3. 加载相关: 程序头表(program-headers)的相关信息
4. 链接相关: 节头表(section-headers)的相关信息

## elf 文件的信息查看

1. 使用 readelf -S 或 objdump -h 查看程序头表(段表)
2. 使用 readelf -s 或 objdump -t 查看符号表
3. 使用 size 命令查看各段大小

| table        | options                         | content                                                         |
| ------------ | ------------------------------- | --------------------------------------------------------------- |
| 程序头表(段表) | -l --program-headers --segments | 显示程序头(段头)信息, 例如记录 bss 段的大小, 即所有未初始化的变量的总大小 |
| 节头表        | -S --section-headers --sections | 显示节头信息, 例如记录 bss 段中每个未初始化的变量的大小                 |
| 符号表        | -s --syms --symbols             | 显示符号表段中的项                                                 |

# C 程序镜像文件

1. 连接器(LD)是将所有编译器和汇编器的输出文件连接成一个二进制映象文件的工具
2. 二进制映象文件有很多种不同格式, 包括: flat, aout, coff, pe, elf 等

无论哪种格式, 链接输出的文件中都会出现三个区域:

1. Text(Code) 代码段, 只读, 存储在磁盘镜像文件中
2. Data 初始化数据段, 可读可写, 存储在磁盘镜像文件中, 举例来说，你在程序定义了一个变量并给它赋值5，那么这个“5”就被存储在 Data 区
3. BSS 未初始化数据段, 可读可写, 它存储着未赋任何值的数组, 是一个虚拟的区域, 只记录大小, 本身不存在于二进制映像中, 当二进制映像被加载后存在于内存中
