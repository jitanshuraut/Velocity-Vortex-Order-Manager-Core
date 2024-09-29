#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP

#include "order.hpp"
#include "APIClient.hpp"
#include "Queue.hpp" 
#include <json/json.h> 
#include <string>
#include <iostream>
#include <optional> 

class OrderManager {
private:
    APIClient apiClient;

public:
    OrderManager(const std::string& apiKey, const std::string& secretKey)
        : apiClient(apiKey, secretKey) {}

    void createOrder(const std::string& side, const std::string& type, const std::string& timeInForce,
                               const std::string& symbol, const std::string& qty, 
                               const std::optional<std::string>& limitPrice, 
                               const std::optional<std::string>& stopPrice, 
                               const std::optional<std::string>& trailPrice, 
                               const std::optional<std::string>& trailPercent);

    void processOrderQueue();
    void getAllOrders();
    void deleteAllOrders();
    void getOrderById(const std::string& orderId);
    void deleteOrderById(const std::string& orderId);


private:
    Order parseOrderFromJson(const std::string& response);
};

#endif 
