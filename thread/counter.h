// 计数器
// @author zixie1991@163.com

#ifndef UTIL_COUNTER_H_
#define UTIL_COUNTER_H_

#include "atomic.h"


template <typename T>
class AtomicCounter {
  public:
    AtomicCounter():
      count_(0)
    {}

    AtomicCounter(T count):
      count_(count)
    {}

    T operator++() {
      return atomic_inc_ret_old(&count_) + 1U;
    }

    T operator--() {
      return atomic_dec_ret_old(&count_) - 1U;
    }

    operator T() const {
      return count_;
    }

  private:
    volatile T count_;
}; // class AtomicCounter

typedef AtomicCounter<int32_t> AtomicInt32;
typedef AtomicCounter<int64_t> AtomicInt64;

#endif
