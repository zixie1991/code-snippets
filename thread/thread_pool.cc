#include "thread_pool.h"

ThreadPool::ThreadPool(const std::string& name):
  name_(name),
  running_(false)
{
}

ThreadPool::~ThreadPool(){
	if(running_){
		Stop();
	}
}

void ThreadPool::Start(int num_threads) {
  assert(!running_);
  running_ = true;

  for (int i = 0; i < num_threads; i++) {
    threads_.push_back(new Worker(this));
    threads_[i]->Start();
  }
}

void ThreadPool::Stop() {
  running_ = false;
  for (size_t i = 0; i < threads_.size(); i++) {
    threads_[i]->Join();
  }
}

void ThreadPool::Run(const Task& task) {
  if (threads_.empty()) {
    task();
  } else {
    queue_.Push(task);
  }
}

ThreadPool::Task ThreadPool::Take() {
  return queue_.Pop();
}


ThreadPoolWithPipe::ThreadPoolWithPipe(const std::string& name):
  name_(name),
  running_(false)
{
}

ThreadPoolWithPipe::~ThreadPoolWithPipe() {
}

void ThreadPoolWithPipe::Start(int num_threads) {
  assert(!running_);
  running_ = true;

  for (int i = 0; i < num_threads; i++) {
    threads_.push_back(new Worker(this));
    threads_[i]->Start();
  }
}

void ThreadPoolWithPipe::Stop() {
  running_ = false;
  for (size_t i = 0; i < threads_.size(); i++) {
    threads_[i]->Join();
  }
}

void ThreadPoolWithPipe::Run(Task* task) {
  input_queue_.Push(task);
}

ThreadPoolWithPipe::Task* ThreadPoolWithPipe::Take() {
  Task* task = NULL;
  bool status = output_queue_.Pop(&task);
  if (!status) {
    return NULL;
  }

  return task;
}
