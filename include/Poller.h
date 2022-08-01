#pragma once
#include <map>

#include "EventLoop.h"

struct pollfd;

namespace modou {

class Channel;
class Timestamp {};

extern const int kPollTimeMs;
class Poller {
 public:
  using ChannelList = std::vector<Channel*>;
  Poller(EventLoop* loop);
  ~Poller();

  // Polls the I/O events.
  // must be called in the loop thread
  Timestamp poll(int timeoutMs, ChannelList* activeChannels);

  // change the interested I/O events defined by channel;
  // must be called in the loop thread
  void updateChannel(Channel* channel);

  // Poller 应该和 eventloop是一个线程
  void assertInLoopThread() { ownerLoop_->assertInLoopThread(); }

 private:
  void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

  using ChannelMap = std::map<int, Channel*>;
  using PollFdList = std::vector<struct pollfd>;

  EventLoop* ownerLoop_;
  // poll 有自己的管理事件的结构:sturct pollfd,
  // 需要自己处理pollfd 和 channel之间的映射
  PollFdList pollfds_;
  ChannelMap channels_;
};

}  // namespace modou
