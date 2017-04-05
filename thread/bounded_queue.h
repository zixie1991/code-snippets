// 循环队列
// @author zixie1991@163.com

#ifndef UTIL_BOUNDED_QUEUE_H_
#define UTIL_BOUNDED_QUEUE_H_

#include <assert.h>

#include <vector>


template <typename T>
class BoundedQueue {
  public:
    BoundedQueue(size_t capacity):
      head_(0),
      tail_(0),
      size_(0),
      capacity_(capacity)
    {}

    void Push(const T& x) {
      assert(!Full());
      queue_[tail_] = x;
      tail_ = (tail_ + 1) % capacity_;
      size_++;
    }

    T Pop() {
      assert(!Empty());
      size_t ret = head_;
      head_ = (head_ + 1) % capacity_;
      size_--;

      return queue_[ret];
    }

    size_t Size() const {
      return size_;
    }

    bool Empty() const {
      return !size_;
    }

    bool Full() const {
      return size_ == capacity_;
    }

  private:
    size_t head_;
    size_t tail_;
    size_t size_;
    size_t capacity_;
    std::vector<T> queue_;
}; // class BoundedQueue

#endif
