// 文件锁
// @author zixie1991@163.com

#ifndef UTIL_FILE_LOCK_H_
#define UTIL_FILE_LOCK_H_

#include <string>


class FileLock {
  public:
    FileLock();
    ~FileLock();

    void Open(const std::string& filename);
    void Close();

    void Lock();
    bool TryLock();
    void LockShared();
    void Unlock();

    bool ok() const {
      return ok_;
    }

  private:
    int fd_;
    bool ok_;
}; // class FileLock

#endif
