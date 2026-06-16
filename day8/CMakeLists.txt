# 表示这个项目至少要用 CMake 3.10
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(BlockManagerTest)

# 使用 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 头文件目录
include_directories(include)

# 生成可执行文件
add_executable(BlockManagerTest
    main.cpp
    src/BlockManager.cpp
)