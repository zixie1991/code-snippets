// 管道队列
// @author zixie1991@163.com

#ifndef UTIL_SELECTABLE_QUEUE_H_
#define UTIL_SELECTABLE_QUEUE_H_

#include <errno.h>
#include <string.h>

#include <vector>


template <typename T>
class SelectableQueue {
  public:
    SelectableQueue() {
      if (pipe(fds_) < 0) {
        fprintf(stderr, "create pipe error: %s\n", strerror(errno));
        exit(0);
      }
    }

    ~SelectableQueue() {
      close(fds_[0]);
      close(fds_[1]);
    }

    void Push(const T& x) {
      if (write(fds_[1], (char *)&x, sizeof(T)) == -1) {
        exit(0);
      }
    }

    bool Pop(T* x) {
      bool ret = false;
      while (1) {
        int status = read(fds_[0], (char*)x, sizeof(T));
        if (status < 0) {
          if (errno != EINTR) {
            continue;
          }
        } else if (status == 0) {
          break;
        } else {
          ret = true;
          break;
        }
      }

      return ret;
    }

    int fd() const {
      return fds_[0];
    }

  private:
		int fds_[2];
};

#endif
