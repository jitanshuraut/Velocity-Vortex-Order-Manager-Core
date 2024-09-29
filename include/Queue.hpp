#ifndef GLOBAL_QUEUE_HPP
#define GLOBAL_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "order.hpp"

class GlobalQueue
{
public:
    static GlobalQueue &getInstance()
    {
        static GlobalQueue instance;
        return instance;
    }

    std::vector<Order> dequeueBatch(size_t n);
    void enqueue(const Order &order);
    bool dequeue(Order &order);
    bool isEmpty() const;
    void printQueue() const;

private:
    GlobalQueue() = default;
    GlobalQueue(const GlobalQueue &) = delete;
    GlobalQueue &operator=(const GlobalQueue &) = delete;

    std::queue<Order> orderQueue;
    mutable std::mutex mtx;
};

#endif
