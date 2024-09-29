cmake_minimum_required(VERSION 3.10)
project(QuantBox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)


find_package(CURL REQUIRED)
find_package(jsoncpp REQUIRED)

include_directories(/usr/include) 
link_directories(/usr/lib/x86_64-linux-gnu)  


set(SOURCES
    src/main.cpp
    src/order.cpp
    src/order_manager.cpp
    src/Queue.cpp
    src/Database.cpp  
    src/utils.cpp
)


add_executable(QuantBox ${SOURCES})

target_link_libraries(QuantBox ${CURL_LIBRARIES} jsoncpp_lib sqlite3)
