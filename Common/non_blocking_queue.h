#ifndef NON_BLOCKING_QUEUE_H
#define NON_BLOCKING_QUEUE_H

#include <mutex>
#include <queue>

template <class T>
class NonBlockingQueue {
    std::mutex m;
    std::queue<T> queue;

   public:
        NonBlockingQueue() {}
        ~NonBlockingQueue() {}
        
        NonBlockingQueue(const NonBlockingQueue&) = delete;
        NonBlockingQueue& operator=(const NonBlockingQueue&) = delete;
        NonBlockingQueue(NonBlockingQueue&& other) = delete;
        NonBlockingQueue& operator=(NonBlockingQueue&& other) = delete;

        void push(T t) {
            std::unique_lock<std::mutex> l(m);
            queue.push(t);
        }
        T pop() {
            std::unique_lock<std::mutex> l(m);

            if (queue.empty()) {
                return NULL;
            }

            T t = queue.front();
            queue.pop();
            return t;
        }
};

#endif
