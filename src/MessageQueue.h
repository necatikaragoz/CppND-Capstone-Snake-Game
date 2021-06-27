
#include <queue>
#include <iostream>
#include <random>
#include <deque>
#include <mutex>
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