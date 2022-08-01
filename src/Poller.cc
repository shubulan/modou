#include "Poller.h"

#include <poll.h>

#include "Channel.h"

namespace modou {

const int kPollTimeMs = 20;
Poller::Poller(EventLoop* loop) : ownerLoop_(loop) {}

Poller::~Poller() {}

Timestamp Poller::poll(int timeoutMs, ChannelList* activeChannels) {
  int numEvents = ::poll(&(*pollfds_.begin()), pollfds_.size(), timeoutMs);
  // Timestamp now(Timestamp::now());
  if (numEvents > 0) {
    trace("{} events happended", numEvents);
    fillActiveChannels(numEvents, activeChannels);
  } else if (numEvents == 0) {
    trace("nothing happend");
  } else {
    error("Poller::poll()");
  }
  return Timestamp();
}

void Poller::fillActiveChannels(int numEvents,
                                ChannelList* activeChannels) const {
  for (PollFdList::const_iterator pfd = pollfds_.begin();
       pfd != pollfds_.end() && numEvents > 0; ++pfd) {
    if (pfd->revents > 0) {
      --numEvents;
      ChannelMap::const_iterator ch = channels_.find(pfd->fd);
      assert(ch != channels_.end());
      Channel* channel = ch->second;
      channel->set_revents(pfd->revents);
      assert(channel->fd() == pfd->fd);
      activeChannels->push_back(channel);
    }
  }
}

void Poller::updateChannel(Channel* channel) {
  assertInLoopThread();
  trace("fd = {} events = {}", channel->fd(), channel->events());
  if (channel->index() < 0) {
    // 添加新的channel
    assert(channels_.find(channel->fd()) == channels_.end());
    struct pollfd pfd;
    pfd.fd = channel->fd();
    pfd.events = static_cast<short>(channel->events());
    pfd.revents = 0;
    pollfds_.push_back(pfd);
    int idx = static_cast<int>(pollfds_.size()) - 1;
    channel->setIndex(idx);
    channels_[pfd.fd] = channel;
  } else {
    assert(channels_.find(channel->fd()) != channels_.end());
    assert(channels_[channel->fd()] == channel);
    int idx = channel->index();
    assert(0 <= idx && idx < static_cast<int>(pollfds_.size()));
    struct pollfd& pfd = pollfds_[idx];
    assert(pfd.fd == channel->fd() || pfd.fd == -1);
    pfd.events = static_cast<short>(channel->events());
    pfd.revents = 0;
    if (channel->isNoneEvents()) {
      pfd.fd = -1;
    }
  }
}

}  // namespace modou
