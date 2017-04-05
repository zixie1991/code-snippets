// 使用对象管理锁
// @author zixie1991@163.com

#ifndef UTIL_LOCK_GUARD_H_
#define UTIL_LOCK_GUARD_H_


template <typename Lock>
class LockGuard {
  public:
    explicit LockGuard(Lock* lock):
      lock_(lock)
    {
      lock_->Lock();
    }

    ~LockGuard() {
      lock_->Unlock();
    }

  private:
    Lock* lock_;

    // No copying allowed
    LockGuard(const LockGuard&);
    void operator=(const LockGuard&);
}; // class LockGuard

#endif
