// 阻塞队列
// @author zixie1991@163.com

#ifndef UTIL_BLOCKING_QUEUE_H_
#define UTIL_BLOCKING_QUEUE_H_

#include <queue>

#include "mutex.h"
#include "lock_guard.h"


template <typename T>
class BlockingQueue {
  public:
    BlockingQueue():
      mutex_(),
      not_empty_(&mutex_)
    {}

    void Push(const T& x) {
      LockGuard<Mutex> lock(&mutex_);
      queue_.push(x);
      not_empty_.Signal();
    }

    T Pop() {
      LockGuard<Mutex> lock(&mutex_);
      // always use a while-loop, due to spurious wakeup
      while (queue_.empty()) {
        not_empty_.Wait();
      }

      T front = queue_.front();
      queue_.pop();

      return front;
    }

    size_t Size() const {
      LockGuard<Mutex> lock(&mutex_);
      return queue_.size();
    }

    bool Empty() const {
      return queue_.empty();
    }

  private:
    mutable Mutex mutex_;
    Condition not_empty_;
    std::queue<T> queue_;
}; // class BlockingQueue

#endif
