cmake_minimum_required(VERSION 3.20)
project(CopyLine)
set(CMAKE_CXX_STANDARD 17)

set(COMMON_SOURCES
    src/daemon/main.cpp
    src/daemon/clipboard/clipboard.cpp
    src/daemon/queue/queue.cpp
    src/daemon/paste/paste.cpp
    src/daemon/ipc/ipc.cpp
    src/daemon/config/config.cpp
)

if(WIN32)
    add_executable(CopyLine
        ${COMMON_SOURCES}
        src/daemon/core/core.cpp
        src/daemon/input/input.cpp
        src/daemon/tray/tray.cpp
    )
    add_executable(copyline-cli src/cli/main.cpp)

elseif(UNIX)
    add_executable(CopyLine
        ${COMMON_SOURCES}
        src/daemon/core/core_x11.cpp
        src/daemon/input/input_x11.cpp
        src/daemon/tray/tray_x11.cpp
        src/daemon/clipboard/clipboard_x11.cpp
    )
    add_executable(copyline-cli src/cli/main.cpp)

    find_package(X11 REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(APPINDICATOR REQUIRED appindicator3-0.1)

    target_include_directories(CopyLine PRIVATE 
        ${X11_INCLUDE_DIR}
        ${APPINDICATOR_INCLUDE_DIRS}
    )
    target_link_libraries(CopyLine PRIVATE
        ${X11_LIBRARIES}
        Xfixes
        Xtst
        ${APPINDICATOR_LIBRARIES}
    )
endif()