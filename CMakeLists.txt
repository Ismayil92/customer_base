cmake_minimum_required(VERSION 3.10)
project(CustomerService VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(SPDLOG_INCLUDE_DIR external/spdlog/include)

find_package(Threads REQUIRED)


add_executable(${PROJECT_NAME} src/main.cpp src/kunde.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE
                include 
                ${SPDLOG_INCLUDE_DIR}) 

target_link_libraries(${PROJECT_NAME} Threads::Threads)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
