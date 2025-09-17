# 简介

嵌入式项目中，有各种硬件平台和os平台，在写应用时，需要用到不少库函数接口，当项目需要迁移时，就会比较麻烦，很多应用行为需要调整。

一个简单的办法就是用一个嵌入式os来处理，但是os有时候太大了，很多时候还是希望裸机上运行，这样code size不会太大，代码也相对清晰一些。

为满足上述需求，本项目将一些常用到的功能整合在一起，以便用户写一些跨平台应用。本项目地址：[bobwenstudy/easy_tools: 一个跨平台裸机工具库，包含任务/堆栈/消息/定时器/日志等实现。](https://github.com/bobwenstudy/easy_tools)

- TASK/MSG/HEAP功能，在嵌入式裸机开发中，经常有任务(Task)和消息队列(Message)的管理需求，直接加入OS又太过复杂了，所以本项目提供适用于嵌入式裸机环境需要进行Task和Message功能需求的人群。项目地址：[bobwenstudy/bare_task_msg (github.com)](https://github.com/bobwenstudy/bare_task_msg)
- 定时器功能，嵌入式需求通常伴随低功耗和定时需求，本项目实现了一整套定时器管理功能。
- Log管理功能，包含日志级别管理等日志管理功能。
- RingBuffer/Pool，常用的Buffer管理，项目地址：[bobwenstudy/simple_ringbuffer: 一种基于镜像指示位办法的RingBuffer实现，解决Mirror和2的幂个数限制 (github.com)](https://github.com/bobwenstudy/simple_ringbuffer)
- 单/双链表，参考zepher实现的单双链表。

有以上功能，基本大多数应用都可以开发了。




# 代码结构

代码结构如下所示：

- **easy_tools**：驱动库，主要包含heap管理，list管理，msg管理和task管理几个部分。
- **main.c**：测试例程。
- **build.mk**和**Makefile**：Makefile编译环境。
- **port_xx.c**：不同平台的easy_tools接口实现。
- **README.md**：说明文档

```shell
easy_tools
 ├── build.mk
 ├── easy_tools
 │   ├── easy_api.c
 │   ├── easy_api.h
 │   ├── easy_data_ringbuffer.c
 │   ├── easy_data_ringbuffer.h
 │   ├── easy_dlist.h
 │   ├── easy_heap.c
 │   ├── easy_heap.h
 │   ├── easy_log.c
 │   ├── easy_log.h
 │   ├── easy_msg.c
 │   ├── easy_msg.h
 │   ├── easy_pool.h
 │   ├── easy_ringbuffer.c
 │   ├── easy_ringbuffer.h
 │   ├── easy_slist.h
 │   ├── easy_task.c
 │   ├── easy_task.h
 │   ├── easy_timer.c
 │   ├── easy_timer.h
 │   ├── easy_tools.c
 │   ├── easy_tools.h
 │   ├── easy_tools_common.h
 │   ├── easy_tools_config.h
 │   └── easy_tools_config_default.h
 ├── LICENSE
 ├── main.c
 ├── Makefile
 ├── port_pc
 │   ├── api_easy_tools.c
 │   └── app_easy_tools_config.h
 ├── port_rtthread
 │   ├── api_easy_tools.c
 │   └── app_easy_tools_config.h
 ├── port_stm32
 │   ├── api_easy_tools.c
 │   └── app_easy_tools_config.h
 └── README.md
```





# 移植说明

在不同平台移植时，需要实现`easy_api.h`中的函数。可以参考`port_pc`、`port_stm32`、`port_rtthread`中的实现，没什么东西。

- 临界区管理，因为涉及到队列管理/timer管理等，项目中也会有前台和后台（中断）等同时使用场景，所以需要进入临界区保护。定义了进出临界区的接口，`__easy_disable_isr()`和`__easy_enable_isr()`。如果应用不在中断中调用，这两个宏可以为空，不然需要根据具体平台情况适配。
- Timer管理，如果项目没低功耗要求，无需实现`easy_tools_api_timer_start()`和`easy_tools_api_timer_stop()`。如果有低功耗要求，意味着有时候polling会不调度，所以需要通过上面2个接口告知平台在什么时刻需要调度`easy_tools`。当然考虑到有task业务，所以需要用`easy_tools_check_need_polling_work()`判断是否允许进低功耗业务。基本的`easy_tools_api_timer_get_current()`和`easy_tools_api_delay()`按需实现。
- 日志管理，实现`easy_tools_api_log()`和`easy_tools_api_assert()`接口。
- Heap管理，实现`easy_tools_api_heap_init()`接口。







# 使用说明

具体如何使用直接看例程就行，非常简单，看函数名和变量名即可。

## TASK/MSG/HEAP功能

直接看[bobwenstudy/bare_task_msg (github.com)](https://github.com/bobwenstudy/bare_task_msg)说明就行。



## 定时器功能

代码在`easy_timer.c/.h`中，一个简单的单链表定时器，看看代码就能看懂了。



## Log管理功能

代码在`easy_log.c/.h`中，就是一些日志级别管理之类的东西，记得配置`EASY_CONFIG_DEBUG_LOG_LEVEL`。

`EASY_CONFIG_DEBUG_LOG_SIMPLE`决定是否打印文件所在行和列。

`EASY_CONFIG_DEBUG_LOG_WITH_NEWLINE`决定是否增加新行。



## RingBuffer/Pool功能

直接看[bobwenstudy/simple_ringbuffer: 一种基于镜像指示位办法的RingBuffer实现，解决Mirror和2的幂个数限制 (github.com)](https://github.com/bobwenstudy/simple_ringbuffer)说明。



## 单/双链表功能

直接看代码和使用示例即可，常规的链表管理操作。





# 测试说明

## 环境搭建

目前测试暂时只支持Windows编译，最终生成exe，可以直接在PC上跑。

目前需要安装如下环境：
- GCC环境，笔者用的msys64+mingw，用于编译生成exe，参考这个文章安装即可。[Win7下msys64安装mingw工具链 - Milton - 博客园 (cnblogs.com)](https://www.cnblogs.com/milton/p/11808091.html)。


## 编译说明

本项目都是由makefile组织编译的，编译整个项目只需要执行`make all`即可。


也就是可以通过如下指令来编译工程：

```shell
make all
```

而后运行执行`make run`即可运行例程，例程中先完成buffer的自测试；然后实现了2个Task的消息管理，并实现了Task Save的相关逻辑；最后实现了一个定时器周期工作。

```shell
PS D:\workspace\github\easy_tools> make run
Building   : "output/main.exe"
Start Build Image.
objcopy -v -O binary output/main.exe output/main.bin
copy from `output/main.exe' [pei-x86-64] to `output/main.bin' [binary]
objdump --source --all-headers --demangle --line-numbers --wide output/main.exe > output/main.lst
Print Size
   text    data     bss     dec     hex filename
 128880  807288    2880  939048   e5428 output/main.exe
./output/main.exe
Application running
Test work
Testing test_work .......................................................... pass
Testing test_work_insuff ................................................... pass
Testing test_work_invalid .................................................. pass
Testing test_work_full ..................................................... pass
Testing test_work_full_define .............................................. pass
Testing test_work_read_index_big_to_write_index ............................ pass
Testing test_work_read_index_big_to_write_index ............................ pass
Testing test_work_odd ...................................................... pass
Testing test_work_insuff_odd ............................................... pass
Testing test_work_invalid_odd .............................................. pass
Testing test_work_full_odd ................................................. pass
Testing test_work_read_index_big_to_write_index_odd ........................ pass
Testing test_data_work ..................................................... pass
Testing test_data_work_full ................................................ pass
Testing test_data_work_full_define ......................................... pass
Testing test_data_work_full_define_enqueue ................................. pass
Testing test_data_work_odd ................................................. pass
Testing test_data_work_full_odd ............................................ pass
Testing test_pool_work ..................................................... pass
Testing test_pool_work_full ................................................ pass
Testing test_pool_work_odd ................................................. pass
Testing test_pool_work_full_odd ............................................ pass
Heap Remain Size: 0xff0
Task Start Work!
Timer Start Work!
Timer callback called: 1
user_task1(), id: 0x1, len: 0
EASY_TASK_HDL_SAVED
user_task2(), id: 0x8, len: 0
user_task2(), id: 0x9, len: 0
user_task2(), id: 0x50, len: 20
0x0:0x1:0x2:0x3:0x4:0x5:0x6:0x7:0x8:0x9:0xa:0xb:0xc:0xd:0xe:0xf:0x10:0x11:0x12:0x13:
EASY_TASK_HDL_SAVED
user_task1(), id: 0x1, len: 0
user_task1(), id: 0x2, len: 0
user_task1(), id: 0x10, len: 10
0x0:0x1:0x2:0x3:0x4:0x5:0x6:0x7:0x8:0x9:
user_task1(), id: 0x11, len: 10
0x10:0x11:0x12:0x13:0x14:0x15:0x16:0x17:0x18:0x19:
user_task2(), id: 0x50, len: 20
0x0:0x1:0x2:0x3:0x4:0x5:0x6:0x7:0x8:0x9:0xa:0xb:0xc:0xd:0xe:0xf:0x10:0x11:0x12:0x13:
user_task2(), id: 0x51, len: 20
0x10:0x11:0x12:0x13:0x14:0x15:0x16:0x17:0x18:0x19:0x1a:0x1b:0x1c:0x1d:0x1e:0x1f:0x20:0x21:0x22:0x23:
user_task2(), id: 0x51, len: 100
0x50:0x51:0x52:0x53:0x54:0x55:0x56:0x57:0x58:0x59:0x5a:0x5b:0x5c:0x5d:0x5e:0x5f:0x60:0x61:0x62:0x63:0x64:0x65:0x66:0x67:0x68:0x69:0x6a:0x6b:0x6c:0x6d:0x6e:0x6f:0x70:0x71:0x72:0x73:0x74:0x75:0x76:0x77:0x78:0x79:0x7a:0x7b:0x7c:0x7d:0x7e:0x7f:0x80:0x81:0x82:0x83:0x84:0x85:0x86:0x87:0x88:0x89:0x8a:0x8b:0x8c:0x8d:0x8e:0x8f:0x90:0x91:0x92:0x93:0x94:0x95:0x96:0x97:0x98:0x99:0x9a:0x9b:0x9c:0x9d:0x9e:0x9f:0xa0:0xa1:0xa2:0xa3:0xa4:0xa5:0xa6:0xa7:0xa8:0xa9:0xaa:0xab:0xac:0xad:0xae:0xaf:0xb0:0xb1:0xb2:0xb3:
Task End Work!
Heap Remain Size: 0xff0
Timer callback called: 2
Timer callback called: 3
```



