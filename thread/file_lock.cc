#include "file_lock.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <assert.h>
#include <string.h>


FileLock::FileLock():
  fd_(-1),
  ok_(false)
{}

FileLock::~FileLock() {
  Close();
}

void FileLock::Open(const std::string& filename) {
  fd_ = open(filename.c_str(), O_RDWR | O_CREAT, 0644);
  if (fd_ > 0) {
    ok_ = true;
  }
}

void FileLock::Close() {
  close(fd_);
}

void FileLock::Lock() {
  struct flock f;
  memset(&f, 0, sizeof(f));
  f.l_type = F_WRLCK;
  f.l_whence = SEEK_SET;
  f.l_start = 0;
  f.l_len = 0;

  fcntl(fd_, F_SETLKW, &f);
}

bool FileLock::TryLock() {
  struct flock f;
  memset(&f, 0, sizeof(f));
  f.l_type = F_WRLCK;
  f.l_whence = SEEK_SET;
  f.l_start = 0;
  f.l_len = 0;

  // 非阻塞, 当文件已加锁, 则返回-1
  return fcntl(fd_, F_SETLK, &f) != -1;
}

void FileLock::LockShared() {
  struct flock f;
  memset(&f, 0, sizeof(f));
  f.l_type = F_RDLCK;
  f.l_whence = SEEK_SET;
  f.l_start = 0;
  f.l_len = 0;

  fcntl(fd_, F_SETLKW, &f);
}

void FileLock::Unlock() {
  struct flock f;
  memset(&f, 0, sizeof(f));
  f.l_type = F_UNLCK;
  f.l_whence = SEEK_SET;
  f.l_start = 0;
  f.l_len = 0;

  fcntl(fd_, F_SETLKW, &f);
}
