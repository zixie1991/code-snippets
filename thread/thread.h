#ifndef UTIL_THREAD_H_
#define UTIL_THREAD_H_

#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

#include <queue>
#include <string>


pid_t gettid();

class Thread {
  public:
    Thread(const std::string& name=std::string());
    virtual ~Thread();

    // abort if thread start error
    void Start();
    // return pthread_join()
    bool Join();

    std::string name() const {
      return name_;
		}

    pthread_t pthreadid() const {
			return pthreadid_;
		}

    pid_t tid() const {
			return tid_;
		}

    bool started() const {
			return started_;
		}

  protected:
    virtual int Run() = 0;

  private:
    static void* ThreadFunc(void *arg);

    std::string name_;
    pthread_t pthreadid_;
    pid_t tid_;
    bool started_;
    bool joined_;
}; // class Thread

#endif // UTIL_THREAD_H_
