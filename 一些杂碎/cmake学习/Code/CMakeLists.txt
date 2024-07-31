# 设置CMake的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(MyProject VERSION 1.0)

# 设置编译器
set(CMAKE_C_COMPILER arm-linux-gcc)

# 查找并包含所有src目录下的.c文件
file(GLOB_RECURSE SOURCES "src/*.c")

# 设置目标可执行文件及其源文件
add_executable(my_program ${SOURCES})

# 链接数学库和线程库
target_link_libraries(my_program m pthread)
