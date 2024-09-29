#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>
#include <string>
#include <iostream>
#include "order.hpp" 

class Database {
private:
    sqlite3* db;

public:
  
    Database(const std::string& dbName) {
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Database opened successfully!" << std::endl;
        }

        const char* createTableSQL = R"(
            CREATE TABLE IF NOT EXISTS Orders (
                id TEXT PRIMARY KEY,
                symbol TEXT,
                type TEXT,
                side TEXT
            );
        )";

        char* errMsg = 0;
        if (sqlite3_exec(db, createTableSQL, 0, 0, &errMsg) != SQLITE_OK) {
            std::cerr << "Failed to create table: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }
    
  
    ~Database();

    void insertOrder(const Order& order);
    void printAllOrders();
};

#endif 
