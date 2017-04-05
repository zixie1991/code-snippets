#include "thread.h"

#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>

#include <string.h>
#include <assert.h>


// gettid() returns the caller’s thread ID (TID). In a single-threaded 
// process, the thread ID is equal to the process ID
// In a multithreaded process, all threads have the same PID, but each one 
// has a unique TID
pid_t gettid() {
  //return static_cast<pid_t>(syscall(__NR_gettid));
  return static_cast<pid_t>(syscall(SYS_gettid));
}


Thread::Thread(const std::string& name):
  name_(name),
  pthreadid_(0),
  tid_(0),
  started_(false),
  joined_(false)
{}

Thread::~Thread() {
  if (started_ && !joined_) {
      pthread_detach(pthreadid_);
  }
}

void Thread::Start() {
  assert(!started_);
  started_ = true;
  int ret = pthread_create(&pthreadid_, NULL, ThreadFunc, this);

  if (0 != ret) {
    started_ = false;
    fprintf(stderr, "Failed in pthread_create\n");
    abort();
  }
}

bool Thread::Join() {
  assert(started_);
  assert(!joined_);
  started_ = false;
  joined_ = true;

  int ret = pthread_join(pthreadid_, 0);
  if (0 != ret) {
    return false;
  }

  return true;
}

void* Thread::ThreadFunc(void *arg) {
  Thread *thread= (Thread *)arg;
  // 注意gettid()的调用位置
  thread->tid_ = gettid(); 
  thread->Run();

  return 0;
}
