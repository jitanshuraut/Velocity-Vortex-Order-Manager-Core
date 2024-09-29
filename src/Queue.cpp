#include "Queue.hpp"

void GlobalQueue::enqueue(const Order& order) {
    std::lock_guard<std::mutex> lock(mtx);
    orderQueue.push(order);
}

bool GlobalQueue::dequeue(Order& order) {
    std::lock_guard<std::mutex> lock(mtx);
    if (orderQueue.empty()) {
        return false;
    }
    order = orderQueue.front();
    orderQueue.pop();
    return true;
}

 std::vector<Order> GlobalQueue::dequeueBatch(size_t n) {
        std::lock_guard<std::mutex> lock(mtx);
        std::vector<Order> batch;
        while (!orderQueue.empty() && batch.size() < n) {
            batch.push_back(orderQueue.front());
            orderQueue.pop();
        }
        return batch;
    }

bool GlobalQueue::isEmpty() const {
    std::lock_guard<std::mutex> lock(mtx);
    return orderQueue.empty();
}

void GlobalQueue::printQueue() const {
    std::lock_guard<std::mutex> lock(mtx); 

    std::queue<Order> copyQueue = orderQueue; 
    while (!copyQueue.empty()) {
        Order order = copyQueue.front();
        copyQueue.pop();
        std::cout << "Order: Type: " << order.getOrderType() ;
        std::cout<< ", Price: " << order.getId()<< std::endl;
    }
}