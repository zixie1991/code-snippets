// 互斥量
// 条件变量
// @author zixie1991@163.com

#ifndef UTIL_MUTEX_H_
#define UTIL_MUTEX_H_

#include <pthread.h>
#include <sys/time.h>
#include <errno.h>


class Mutex {
	public:
		Mutex() {
			pthread_mutex_init(&mutex_, NULL);
		}

		~Mutex() {
			pthread_mutex_destroy(&mutex_);
		}

		void Lock() {
			pthread_mutex_lock(&mutex_);
		}

		void Unlock() {
			pthread_mutex_unlock(&mutex_);
		}

		pthread_mutex_t* pthread_mutex() {
			return &mutex_;
		}

	private:
		pthread_mutex_t mutex_;
}; // class Mutex


class Condition {
	public:
		Condition(Mutex* mutex):
			mutex_(mutex)
		{
			pthread_cond_init(&cond_, NULL);
		}

		~Condition(){
			pthread_cond_destroy(&cond_);
		}

		void Wait() {
			pthread_cond_wait(&cond_, mutex_->pthread_mutex());
		}

		bool TimedWait(int timeout_in_ms) {
      if (timeout_in_ms < 0) {
        return false;
      }

      // 计算过期时间
      timespec ts;
      timeval tv;
      gettimeofday(&tv, NULL);
      uint64_t usec = tv.tv_usec + timeout_in_ms * 1000LL;
      ts.tv_sec = tv.tv_sec + usec / 1000000;
      ts.tv_nsec = (usec % 1000000) * 1000;

			int status = pthread_cond_timedwait(&cond_, mutex_->pthread_mutex(), &ts);
      if (0 == status) {
        return true; 
      } else if (status == ETIMEDOUT) {
        return false;
      } else {
        fprintf(stderr, "pthread_cond_timedwait error: %s", strerror(errno));
        return false;
      }
		}

		void Signal() {
			pthread_cond_broadcast(&cond_);
		}

		void Broadcast() {
			pthread_cond_broadcast(&cond_);
		}

	private:
		Mutex* mutex_;
		pthread_cond_t cond_;
}; // class Condition

#endif
