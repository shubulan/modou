#pragma once

#include <functional>

namespace modou {

class EventLoop;
class Channel {
 public:
  typedef std::function<void()> EventCallback;

  Channel(EventLoop* loop, int fd);
  ~Channel() {}

  void handleEvent();

  void setReadCallback(const EventCallback& cb) { readCallback_ = cb; };

  void setWriteCallback(const EventCallback& cb) { writeCallback_ = cb; };

  void setErrorCallback(const EventCallback& cb) { errorCallback_ = cb; };

  int fd() const { return fd_; }
  int events() const { return events_; }
  void set_revents(int revt) { revents_ = revt; }
  bool isNoneEvents() { return revents_ == kNoneEvent; }

  void enableReading() {
    events_ |= kReadEvent;
    update();
  }

  void enableWriting() {
    events_ |= kWriteEvent;
    update();
  }

  void disableReading() {
    events_ &= ~kReadEvent;
    update();
  }

  void disableWriting() {
    events_ &= ~kWriteEvent;
    update();
  }

  int index() { return index_; }
  void setIndex(int idx) { index_ = idx; }
  EventLoop* ownerLoop() { return loop_; }

 private:
  Channel(const Channel&) = delete;
  Channel& operator=(const Channel&) = delete;
  void update();

  static const int kNoneEvent;
  static const int kReadEvent;
  static const int kWriteEvent;

  EventLoop* loop_;
  const int fd_;

  int events_;
  int revents_;
  int index_;

  EventCallback readCallback_;
  EventCallback writeCallback_;
  EventCallback errorCallback_;
};
}  // namespace modou
