#include <iostream>
#include <thread>
#include <future>
#include <atomic>
#include <chrono>
#include "APIClient.hpp"
#include "order_manager.hpp"
#include "Queue.hpp"
#include "Database.hpp"
#include "order.hpp"
#include "utils.hpp"

std::atomic<bool> keepRunning(true);

void processOrders(Database &db)
{
    while (keepRunning.load())
    {
        if (!GlobalQueue::getInstance().isEmpty())
        {
            std::vector<Order> orders = GlobalQueue::getInstance().dequeueBatch(2);

            std::vector<std::future<void>> futures;

            for (auto &order : orders)
            {

                std::cout << "Inserting Order: " << "ID: " << order.getId() << ", " << "Symbol: " << order.getSymbol() << ", " << "Type: " << order.getOrderType() << ", " << "Side: " << order.getSide() << std::endl;
                futures.push_back(std::async(std::launch::async, [&db, order]()
                                             {
                    std::cout<<"inserted in DB"<<std::endl;
                    db.insertOrder(order);
                    db.printAllOrders(); }));
            }

            for (auto &future : futures)
            {
                future.get();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main()
{

    std::string apiKey = getEnvVariable("APCA_API_KEY_ID");
    std::string apiSecret = getEnvVariable("APCA_API_SECRET_KEY");
    APIClient apiClient(apiKey, secretKey);
    OrderManager orderManager(apiKey, secretKey);
    Database db("orders.db");

    std::thread orderProcessingThread(processOrders, std::ref(db));

    try
    {
        std::cout << "creating orrder" << std::endl;
        orderManager.createOrder("buy", "market", "ioc", "AAPL", "1", std::nullopt, std::nullopt, std::nullopt, std::nullopt);
        GlobalQueue::getInstance().printQueue();
        orderManager.createOrder("buy", "market", "ioc", "AAPL", "1", std::nullopt, std::nullopt, std::nullopt, std::nullopt);
        GlobalQueue::getInstance().printQueue();
        orderManager.createOrder("buy", "market", "ioc", "AAPL", "1", std::nullopt, std::nullopt, std::nullopt, std::nullopt);
        GlobalQueue::getInstance().printQueue();
        orderManager.createOrder("buy", "market", "ioc", "AAPL", "1", std::nullopt, std::nullopt, std::nullopt, std::nullopt);
        GlobalQueue::getInstance().printQueue();
        orderManager.createOrder("buy", "market", "ioc", "AAPL", "1", std::nullopt, std::nullopt, std::nullopt, std::nullopt);
        GlobalQueue::getInstance().printQueue();
        orderManager.createOrder("buy", "market", "ioc", "AAPL", "1", std::nullopt, std::nullopt, std::nullopt, std::nullopt);
        GlobalQueue::getInstance().printQueue();
        orderManager.createOrder("buy", "market", "ioc", "AAPL", "1", std::nullopt, std::nullopt, std::nullopt, std::nullopt);
        GlobalQueue::getInstance().printQueue();
        orderManager.createOrder("buy", "market", "ioc", "AAPL", "1", std::nullopt, std::nullopt, std::nullopt, std::nullopt);
        GlobalQueue::getInstance().printQueue();
        orderManager.createOrder("buy", "market", "ioc", "AAPL", "1", std::nullopt, std::nullopt, std::nullopt, std::nullopt);
        GlobalQueue::getInstance().printQueue();
        orderManager.createOrder("buy", "market", "ioc", "AAPL", "1", std::nullopt, std::nullopt, std::nullopt, std::nullopt);
        GlobalQueue::getInstance().printQueue();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to create order: " << e.what() << std::endl;
    }

    // Example: Get all orders
    // try {
    //     std::cout<<"getting all orders"<<std::endl;
    //     orderManager.getAllOrders();
    // } catch (const std::exception& e) {
    //     std::cerr << "Failed to get all orders: " << e.what() << std::endl;
    // }

    // Example: Delete all orders (be cautious with this operation)
    // try {
    //     orderManager.deleteAllOrders();
    // } catch (const std::exception& e) {
    //     std::cerr << "Failed to delete all orders: " << e.what() << std::endl;
    // }

    keepRunning.store(false);
    orderProcessingThread.join();
    std::cout << " exit..." << std::endl;

    db.printAllOrders();

    return 0;
}
