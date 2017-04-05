// 线程池
// @author zixie1991@163.com

#ifndef UTIL_THREAD_POOL_H_
#define UTIL_THREAD_POOL_H_

#include <string>
#include <vector>

#include <boost/function.hpp>

#include "thread.h"
#include "blocking_queue.h"
#include "selectable_queue.h"


class ThreadPool {
	public:
    typedef boost::function<void ()> Task;

    class Worker: public Thread {
      public:
        Worker(ThreadPool* thread_pool):
          thread_pool_(thread_pool)
        {}

      protected:
        int Run() {
          while (thread_pool_->running_) {
            Task task(thread_pool_->Take());
            task();
          }

          return 0;
        }

      private:
        ThreadPool* thread_pool_;
    };

    friend Worker;

		ThreadPool(const std::string& name="ThreadPool");
		~ThreadPool();

		void Start(int num_threads);
		void Stop();

    void Run(const Task& task);

    const std::string& name() const {
      return name_;
    }

	private:
    Task Take();

		std::string name_;
    bool running_;
    std::vector<Thread*> threads_;
    BlockingQueue<Task> queue_;
}; // class ThreadPool


class ThreadPoolWithPipe {
  public:
    class Task {
      public:
        virtual ~Task() = 0;
        virtual void PreProcess() {}
        virtual void Process() = 0;
        virtual void PostProcess() {}

        virtual void Callback() {}
    };

    class Worker: public Thread {
      public:
        Worker(ThreadPoolWithPipe* thread_pool):
          thread_pool_(thread_pool)
        {}

      protected:
        int Run() {
          while (thread_pool_->running_) {
            Task* task = thread_pool_->input_queue_.Pop();

            task->PreProcess();
            task->Process();
            task->PostProcess();

            thread_pool_->output_queue_.Push(task);
          }

          return 0;
        }

      private:
        ThreadPoolWithPipe* thread_pool_;
    };

    friend Worker;

		ThreadPoolWithPipe(const std::string& name="ThreadPoolWithPipe");
		~ThreadPoolWithPipe();

		void Start(int num_threads);
		void Stop();

    void Run(Task* task);
    Task* Take();

    int fd() const {
      return output_queue_.fd();
    }

    const std::string& name() const {
      return name_;
    }

  private:
    std::string name_;
    bool running_;
    std::vector<Thread*> threads_;
    BlockingQueue<Task*> input_queue_;
    SelectableQueue<Task*> output_queue_;
}; // class ThreadPoolWithPipe

#endif
