#ifndef UTIL_DAEMON_H_
#define UTIL_DAEMON_H_

/**
 * @brief 创建守护进程
 * linux系统编程之进程（八）：守护进程详解及创建，daemon()使用: http://www.cnblogs.com/mickole/p/3188321.html
 *
 * @param work_dir 守护进程的工作目录, 默认为当前执行目录
 *
 * @return 成功返回0，失败返回-1
 */
int Daemon(const char* work_dir="");

#endif
