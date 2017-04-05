#include "daemon.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>


int Daemon(const char* work_dir) {
  switch (fork()) {
    case -1:
      return -1;
    case 0:
      break;
    default:
      exit(0);
  }

  // 回话ID
  if (setsid() < 0) {
    exit(0);
  }

  // 工作目录
  if (work_dir) {
    if (chdir(work_dir) < 0) {
      exit(0);
    }
  }

  // 关闭共享的文件描述符
  if (close(STDIN_FILENO) < 0) {
    exit(0);
  }
  if (close(STDOUT_FILENO) < 0) {
    exit(0);
  }
  if (close(STDERR_FILENO) < 0) {
    exit(0);
  }

  // 将标准输入、输出、出错重定向到/dev/null
  int fd = open("/dev/null", O_RDWR, 0);
  if (fd < 0) {
    exit(0);
  }

  if (dup2(fd, STDIN_FILENO) < 0) {
    exit(0);
  }

  if (dup2(fd, STDOUT_FILENO) < 0) {
    exit(0);
  }

  if (dup2(fd, STDERR_FILENO) < 0) {
    exit(0);
  }

  return 0;
}
