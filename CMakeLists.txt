cmake_minimum_required(VERSION 3.16)
project(Robot_Gui_V3)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(Robot_Gui_V3 main.cpp XML/rapidxml/rapidxml_print.hpp XML/rapidxml/rapidxml.hpp XML/rapidxml/rapidxml_iterators.hpp XML/rapidxml/rapidxml_utils.hpp GUIMaker.cpp GUIMaker.h CustomWidgets/TextBoxWidget.cpp CustomWidgets/TextBoxWidget.h CustomWidgets/BaseWidget.cpp CustomWidgets/BaseWidget.h RobotGUI.cpp RobotGUI.h Configuration/WidgetInfo.cpp Configuration/WidgetInfo.h WidgetData.cpp WidgetData.h Constants.h Networking/LocalServer.cpp Networking/LocalServer.h Configuration/TabInfo.cpp Configuration/TabInfo.h CustomWidgets/VideoWidget.cpp CustomWidgets/VideoWidget.h XML/XMLInput.cpp XML/XMLInput.h XML/XMLOutput.cpp XML/XMLOutput.h CustomWidgets/BaseWidgetCollection.cpp CustomWidgets/BaseWidgetCollection.h XML/XMLConstants.h)
#add_executable(XML/rapidxml/rapidxml_print.hpp XML/rapidxml/rapidxml.hpp XML/rapidxml/rapidxml_iterators.hpp XML/rapidxml/rapidxml_utils.hpp)

set(Qt5_DIR "~/Qt/5.12.2/clang_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

target_link_libraries(Robot_Gui_V3 Qt5::Core Qt5::Widgets Qt5::Network)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(/usr/include/)

find_package( OpenCV REQUIRED )
set(SOURCE_FILES main.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

