cmake_minimum_required(VERSION 3.19)
project(Robot_Gui_V3)

set(CMAKE_CXX_STANDARD 11)

set(Qt5_DIR "~/Qt/5.12.2/clang_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(Robot_Gui_V3 main.cpp)

target_link_libraries(Robot_Gui_V3 Qt5::Core Qt5::Widgets)