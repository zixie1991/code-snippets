// 读写锁
// @author zixie1991@163.com

#ifndef UTIL_RW_LOCK_H_
#define UTIL_RW_LOCK_H_


class RWLock {
  public:
    RWLock() {
      pthread_rwlock_init(&lock_, NULL);
    }

    ~RWLock() {
      pthread_rwlock_destroy(&lock_);
    }

    void Lock() {
      pthread_rwlock_wrlock(&lock_);
    }

    void LockShared() {
      pthread_rwlock_rdlock(&lock_);
    }

    void Unlock() {
      pthread_rwlock_unlock(&lock_);
    }

  private:
    pthread_rwlock_t lock_;
}; // class RWLock

#endif
