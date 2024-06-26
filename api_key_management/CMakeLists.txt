cmake_minimum_required(VERSION 3.25)
project(api_key_management)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(userver REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(api_key_management src/main.cpp)
target_link_libraries(api_key_management PRIVATE userver::core)





# cmake_minimum_required(VERSION 3.12)
# project(my_microservice)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# find_package(userver REQUIRED)

# add_executable(my_microservice main.cpp)

# target_link_libraries(my_microservice PRIVATE userver::core)
