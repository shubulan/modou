#include "Channel.h"

#include <poll.h>

#include "EventLoop.h"
#include "log.h"

namespace modou {
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop, int fd)
    : loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1) {}

void Channel::update() { loop_->updateChannel(this); }

void Channel::handleEvent() {
  if (revents_ & POLLNVAL) {
    warn("Channel::handle_event() POLLNVAL");
  }
  if (revents_ & (POLLERR | POLLNVAL)) {
    if (errorCallback_) errorCallback_();
  }

  if (revents_ & (POLLIN | POLLNVAL)) {
    if (readCallback_) readCallback_();
  }

  if (revents_ & (POLLOUT | POLLNVAL)) {
    if (writeCallback_) writeCallback_();
  }
}
}  // namespace modou
