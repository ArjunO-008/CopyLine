cmake_minimum_required(VERSION 3.20)

project(CopyLine)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    CopyLine
    src/main.cpp
    src/clipboard/clipboard.cpp
    src/queue/queue.cpp
    src/input/input.cpp
    src/paste/paste.cpp
    src/core/core.cpp
)