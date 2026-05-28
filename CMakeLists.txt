cmake_minimum_required(VERSION 3.20)

project(CopyLine)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    CopyLine
    src/daemon/main.cpp
    src/daemon/clipboard/clipboard.cpp
    src/daemon/queue/queue.cpp
    src/daemon/input/input.cpp
    src/daemon/paste/paste.cpp
    src/daemon/core/core.cpp
    src/daemon/ipc/ipc.cpp
    src/daemon/config/config.cpp
    src/daemon/tray/tray.cpp    
)
add_executable(
    copyline-cli
    src/cli/main.cpp
)
