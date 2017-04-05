#ifndef UTIL_SPIN_LOCK_H_
#define UTIL_SPIN_LOCK_H_

// 自旋锁
// @author zixie1991@163.com

#include <pthread.h>


class SpinLock {
  public:
    SpinLock() {
      pthread_spin_init(&lock_, PTHREAD_PROCESS_PRIVATE);
    }

    ~SpinLock() {
      pthread_spin_destroy(&lock_);
    }

    void Lock() {
      pthread_spin_lock(&lock_);
    }

    bool TryLock() {
      return pthread_spin_trylock(&lock_) == 0;
    }

    void Unlock() {
      pthread_spin_unlock(&lock_);
    }

  private:
    pthread_spinlock_t lock_;
}; // class SpinLock

#endif
