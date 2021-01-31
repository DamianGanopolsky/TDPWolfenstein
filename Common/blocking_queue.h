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
        BlockingQueue(): permanently_closed(false) {}
        ~BlockingQueue(){
            while (!queue.empty()) {
                T t = queue.front();
                queue.pop();
                delete t;
            }
        }
        
        BlockingQueue(const BlockingQueue&) = delete;
        BlockingQueue& operator=(const BlockingQueue&) = delete;
        BlockingQueue(BlockingQueue&& other) = delete;
        BlockingQueue& operator=(BlockingQueue&& other) = delete;
        
        void push(T t) {
            std::unique_lock<std::mutex> l(m);
            queue.push(t);
            cv.notify_all();
        }

    T pop() {
        std::unique_lock<std::mutex> l(m);
        while (queue.empty()) {
            if (permanently_closed) {
                return NULL;
            }

            cv.wait(l);
        }

        T t = queue.front();
        queue.pop();
        return t;
    }

    void close() {
        std::unique_lock<std::mutex> l(m);
        permanently_closed = true;
        cv.notify_all();
    }
        
};

#endif
