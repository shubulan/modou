#pragma once

#include <sstream>
#include <thread>

#include "log.h"

using std::thread;

namespace modou {

// using tid_t = thread::id;

struct tid_t {
  thread::id tid;
  template <typename OStream>
  friend OStream& operator<<(OStream& os, const tid_t& c) {
    std::ostringstream oss;
    oss << c.tid;
    return os << oss.str();
  }

  bool operator==(const tid_t& r) const { return tid == r.tid; }
};

class CurrentThread {
 public:
  static tid_t tid() { return tid_t{std::this_thread::get_id()}; }
};

class Thread {
 public:
  using FuncPtr = void (*)();
  Thread(FuncPtr func) : func_(func) {}

  void start() {
    info("thread start");
    thread_ = std::thread(func_);
  }

  void join() { thread_.join(); }

 private:
  std::thread thread_;

  FuncPtr func_;
};

};  // namespace modou
