cmake_minimum_required(VERSION 3.10)
project(FoodOrderServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

add_executable(server main.cpp src/db.cpp)
target_include_directories(server PRIVATE include)

# Link Boost, OpenSSL, and pthread
target_link_libraries(server PRIVATE Boost::system OpenSSL::SSL OpenSSL::Crypto pthread mysqlclient)
