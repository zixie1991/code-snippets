// 当前线程操作
// @author zixie1991@163.com

#ifndef UTIL_CURRENT_THREAD_H_
#define UTIL_CURRENT_THREAD_H_

#include <time.h>
#include <sched.h>


namespace CurrentThread {

// Thread sleep msec
void SleepMsec(int time_in_ms) {
  if (time_in_ms > 0) {
    timespec ts = {time_in_ms / 1000, (time_in_ms % 1000) * 1000000 };
    nanosleep(&ts, &ts);
  }
}

// Thread sleep usec
void SleepUsec(int time_in_us) {
  if (time_in_us > 0) {
    timespec ts = {time_in_us / 1000000, (time_in_us % 1000000) * 1000 };
    nanosleep(&ts, &ts);
  }
}

// Get thread id
int GetTid() {
  static __thread int thread_id = 0;
  if (thread_id == 0) {
      thread_id = syscall(__NR_gettid);
  }

  return thread_id;
}

// 线程放弃CPU, 让其他线程运行
void Yield() {
  sched_yield();
}

}

#endif
