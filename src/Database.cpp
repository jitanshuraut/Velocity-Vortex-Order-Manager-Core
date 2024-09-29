#include "Database.hpp"

void Database::insertOrder(const Order &order)
{
    std::string sql = "INSERT INTO Orders (id, symbol, type, side) VALUES (?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string id = order.getId();
    std::string symbol = order.getSymbol();
    std::string order_type = order.getOrderType();
    std::string side = order.getSide();

    std::cout << "Inserting Order: "
              << "ID: " << id << ", "
              << "Symbol: " << symbol << ", "
              << "Type: " << order_type << ", "
              << "Side: " << side << std::endl;

    if (sqlite3_bind_text(stmt, 1, id.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Error binding ID: " << sqlite3_errmsg(db) << std::endl;
    }
    if (sqlite3_bind_text(stmt, 2, symbol.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Error binding Symbol: " << sqlite3_errmsg(db) << std::endl;
    }
    if (sqlite3_bind_text(stmt, 3, order_type.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Error binding Order Type: " << sqlite3_errmsg(db) << std::endl;
    }
    if (sqlite3_bind_text(stmt, 4, side.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
    {
        std::cerr << "Error binding Side: " << sqlite3_errmsg(db) << std::endl;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Failed to insert data: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

Database::~Database()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

void Database::printAllOrders()
{
    std::string sql = "SELECT id, symbol, type, side FROM Orders;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string symbol = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string type = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        std::string side = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

        std::cout << "Order: "
                  << "ID: " << id
                  << ", Symbol: " << symbol
                  << ", Type: " << type
                  << ", Side: " << side
                  << std::endl;
    }

    sqlite3_finalize(stmt);
}
