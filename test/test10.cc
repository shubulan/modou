#include "EventLoop.h"
#include "Channel.h"
#include <sys/timerfd.h>
#include <vector>

modou::EventLoop* g_loop;
void timeout() {
    printf("Timeout!\n");
    g_loop->quit();
}

int main() {
    modou::EventLoop loop;
    g_loop = &loop;
    int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    modou::Channel channel(&loop, timerfd);
    channel.enableReading();
    channel.setReadCallback(timeout);

    struct itimerspec howlong;
    bzero(&howlong, sizeof(howlong));
    howlong.it_value.tv_sec = 5;
    ::timerfd_settime(timerfd, 0, &howlong, NULL);

    loop.loop();
    ::close(timerfd);
    

  return 0;
}
