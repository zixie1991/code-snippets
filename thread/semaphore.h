// 信号量
// @author zixie1991@163.com

#ifndef UTIL_SEMAPHORE_H_
#define UTIL_SEMAPHORE_H_

#include <semaphore.h>


class Semaphore {
  public:
    Semaphore(int value) {
      sem_init(&sem_, 0, value);
    }

    ~Semaphore() {
      sem_destroy(&sem_);
    }

    void Signal() {
      sem_post(&sem_);
    }

    void Wait() {
      sem_wait(&sem_);
    }

    bool TimedWait(int timeout_in_ms) {
      if (timeout_in_ms < 0) {
        return false;
      }

      // 计算过期时间
      timespec ts;
      timeval tv;
      gettimeofday(&tv, NULL);
      int64 usec = tv.tv_usec + timeout_in_ms * 1000LL;
      ts->tv_sec = tv.tv_sec + usec / 1000000;
      ts->tv_nsec = (usec % 1000000) * 1000;

			int status = pthread_cond_timedwait(&cond_, mutex_->pthread_mutex(), &ts);
      if (0 == status) {
        return true; 
      } else if (status == ETIMEDOUT) {
        return false;
      } else {
        fprintf(stderr, "pthread_cond_timedwait error: %s", strerror(errno));
        return false;
      }
    }

  private:
    sem_t sem_;
};

#endif
