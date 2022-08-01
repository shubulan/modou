#include "EventLoop.h"

#include "Channel.h"
#include "Poller.h"
#include "Thread.h"
#include "log.h"
namespace modou {

__thread EventLoop* t_loopInThisThread = nullptr;

void EventLoop::abortNotInLoopThread() {
  critical("abort: Not In Loop Thread");
  exit(1);
}

void EventLoop::abortTwoLoopInThread() {
  critical("abort: Two Loops In One Thread");
  exit(1);
}

EventLoop::EventLoop()
    : threadId_(CurrentThread::tid()),
      looping_(false),
      quit_(false),
      poller_(std::make_shared<Poller>(this)) {
  info("EventLoop created {} in thread: {}", fmt::ptr(this), threadId_);
  if (t_loopInThisThread) {
    abortTwoLoopInThread();
  } else {
    t_loopInThisThread = this;
  }
}

void EventLoop::updateChannel(Channel* channel) {
  assert(channel->ownerLoop() == this);
  assertInLoopThread();
  poller_->updateChannel(channel);
}

EventLoop::~EventLoop() {
  assert(!looping_);
  t_loopInThisThread = nullptr;
}
void EventLoop::loop() {
  assert(!looping_);
  assertInLoopThread();
  looping_ = true;
  quit_ = false;
  while (!quit_) {
    activeChannels_.clear();
    poller_->poll(500, &activeChannels_);
    for (auto it = activeChannels_.begin(); it != activeChannels_.end(); ++it) {
      (*it)->handleEvent();
    }
  }
  trace("EventLoop {} stop looping", fmt::ptr(this));
  looping_ = false;
}
}  // namespace modou
