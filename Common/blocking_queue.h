#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <condition_variable>
#include <exception>
#include <mutex>
#include <queue>

template <class T>
class BlockingQueue {
    std::mutex m;
    std::queue<T> queue;
    std::condition_variable cv;
    bool permanently_closed;

    public:
        BlockingQueue();
        ~BlockingQueue();
        
        BlockingQueue(const BlockingQueue&) = delete;
        BlockingQueue& operator=(const BlockingQueue&) = delete;
        BlockingQueue(BlockingQueue&& other) = delete;
        BlockingQueue& operator=(BlockingQueue&& other) = delete;
        
        void push(T t);
        T pop();
        void close();
        
};

#endif
