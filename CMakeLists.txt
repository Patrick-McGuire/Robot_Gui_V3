cmake_minimum_required(VERSION 3.16)
project(Robot_Gui_V3)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(Robot_Gui_V3 main.cpp XML/rapidxml/rapidxml_print.hpp XML/rapidxml/rapidxml.hpp XML/rapidxml/rapidxml_iterators.hpp XML/rapidxml/rapidxml_utils.hpp GUIMaker.cpp GUIMaker.h CustomWidgets/TextBoxWidget.cpp CustomWidgets/TextBoxWidget.h CustomWidgets/BaseWidget.cpp CustomWidgets/BaseWidget.h RobotGUI.cpp RobotGUI.h WidgetData.cpp WidgetData.h Constants.h Networking/LocalServer.cpp Networking/LocalServer.h CustomWidgets/VideoWidget.cpp CustomWidgets/VideoWidget.h XML/XMLInput.cpp XML/XMLInput.h XML/XMLOutput.cpp XML/XMLOutput.h XML/XMLConstants.h ConfigStructs.h CustomWidgets/TabWidget.cpp CustomWidgets/TabWidget.h)

set(Qt5_DIR "~/Qt/5.12.2/clang_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

target_link_libraries(Robot_Gui_V3 Qt5::Core Qt5::Widgets Qt5::Network)
target_link_libraries(Robot_Gui_V3 stdc++fs)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")

include_directories(/usr/include/)

find_package( OpenCV REQUIRED )
set(SOURCE_FILES main.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

