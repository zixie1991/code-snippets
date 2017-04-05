// 阻塞循环队列
// @author zixie1991@163.com

#ifndef UTIL_BOUNDED_BLOCKING_QUEUE_H_
#define UTIL_BOUNDED_BLOCKING_QUEUE_H_

#include <assert.h>

#include "mutex.h"
#include "condition.h"
#include "bounded_queue.h"


template <typename T>
class BoundedBlockingQueue {
  public:
    BoundedBlockingQueue(size_t capacity):
      mutex_(),
      not_empty_(&mutex_),
      not_full_(&mutex_),
      queue_(capacity)
    {}

    void Push(const T& x) {
      LockGuard lock(&mutex_);
      while (queue_.Full()) {
        not_full_.Wait();
      }
      queue_.Push(x);
      not_empty_.Signal();
    }

    T Pop() {
      LockGuard lock(&mutex_);
      while (!queue_.Empty()) {
        not_empty_.Wait();
      }

      T ret = queue_.Pop();
      not_full_.Signal();

      return ret;
    }

    size_t Size() const {
      LockGuard lock(&mutex_);
      return queue_.Size();
    }

    bool Empty() const {
      LockGuard lock(&mutex_);
      return queue_.Empty();
    }

    bool Full() const {
      LockGuard lock(&mutex_);
      return queue_.Full();
    }

  private:
    Mutex mutex_;
    Condition not_empty_;
    Condition not_full_;
    BoundedQueue queue_;
}; // class BoundedBlockingQueue

#endif
