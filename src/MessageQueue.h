#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <mutex>
#include <deque>
#include <condition_variable>

template <class T>
class MessageQueue
{
public:
    void send(T &&msg);
    T receive();

private:
    std::deque<T> _messages;
    std::mutex _mutex;
    std::condition_variable _cond;
    
};

#endif /* End of MESSAGEQUEUE_H */