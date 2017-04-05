#ifndef UTIL_PTIME_H_
#define UTIL_PTIME_H_

#include <stdint.h>

#include <string>

class Timestamp {
  public:
    const static int kMicrosecondsPerSecond = 1000000;
    const static int kMillisecondsPerSecond = 1000;

    explicit Timestamp(long microseconds=0);
    ~Timestamp();

    void Now();

    long seconds() const {
      return microseconds_ / kMicrosecondsPerSecond;
    }

    long milliseconds() const {
      return microseconds_ / kMillisecondsPerSecond;
    }

    long microseconds() const {
      return microseconds_;
    }

    void set_microseconds(long microseconds) {
      microseconds_ = microseconds;
    }

    std::string ToString() const;
    std::string ToSimpleString() const;

  private:
    // microseconds since the Epoch
    long microseconds_;
};

inline bool operator<(const Timestamp& lhs, const Timestamp& rhs) {
  return lhs.microseconds() < rhs.microseconds();
}

inline bool operator==(const Timestamp& lhs, const Timestamp& rhs) {
  return lhs.microseconds() - rhs.microseconds();
}

inline double difftime(const Timestamp& lhs, const Timestamp& rhs) {
  long microseconds = lhs.microseconds() - rhs.microseconds();
  return static_cast<double>(microseconds) / Timestamp::kMicrosecondsPerSecond;
}

inline Timestamp addtime(const Timestamp& timestamp, double seconds) {
  long microseconds = static_cast<long>(seconds * Timestamp::kMicrosecondsPerSecond + timestamp.microseconds());
  return Timestamp(microseconds);
}

#endif // UTIL_PTIME_H_

