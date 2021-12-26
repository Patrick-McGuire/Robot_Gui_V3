cmake_minimum_required(VERSION 3.16)
project(Robot_Gui_V3)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(rapidxml_files
        XML/rapidxml/rapidxml_print.hpp
        XML/rapidxml/rapidxml.hpp
        XML/rapidxml/rapidxml_iterators.hpp
        XML/rapidxml/rapidxml_utils.hpp
        )

set(xml_interface_files
        XML/XMLInput.cpp XML/XMLInput.h
        XML/XMLOutput.cpp XML/XMLOutput.h
        XML/AppConfig.cpp XML/AppConfig.h)

set(widget_type_files
        CustomWidgets/VideoWidget.cpp CustomWidgets/VideoWidget.h
        CustomWidgets/TextBoxWidget.cpp CustomWidgets/TextBoxWidget.h
        CustomWidgets/BaseWidget.cpp CustomWidgets/BaseWidget.h
        CustomWidgets/TabWidget.cpp CustomWidgets/TabWidget.h
        CustomWidgets/MenuWidget.cpp CustomWidgets/MenuWidget.h
        CustomWidgets/SimpleButtonWidget.cpp CustomWidgets/SimpleButtonWidget.h
        CustomWidgets/MultiBarGraphWidget.cpp CustomWidgets/MultiBarGraphWidget.h)

set(widget_part_files
        CustomWidgets/WidgetParts/SimpleBarGraph.cpp CustomWidgets/WidgetParts/BaseGraphDisplay.h
        CustomWidgets/WidgetParts/CircleBarGraph.cpp CustomWidgets/WidgetParts/CircleBarGraph.h)

set(interface_files
        Interface/DataInput.cpp Interface/DataInput.h
        Interface/BaseInterface.cpp
        Interface/ThreadedInterface.cpp Interface/ThreadedInterface.h
        Interface/RandomDataInterface.cpp Interface/RandomDataInterface.h
        Interface/WebcamStreamInterface.cpp
        Interface/LocalServer.cpp
        )

set(core_files
        GUIMaker.cpp GUIMaker.h
        GuiInstance.cpp GuiInstance.h
        WidgetData.cpp WidgetData.h
        RobotGui.h
        CoreGui.cpp CoreGui.h
        Theme.cpp Theme.h
        CommonFunctions.cpp CommonFunctions.h
        )

set(all_gui_files
        ${rapidxml_files}
        ${widget_type_files}
        ${widget_part_files}
        ${networking_files}
        ${interface_files}
        ${xml_interface_files}
        ${core_files})

add_executable(Robot_Gui_V3 main.cpp ${all_gui_files})
set(SOURCE_FILES main.cpp)
include_directories(/usr/include/)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(OpenCV REQUIRED)

target_link_libraries(Robot_Gui_V3 Qt5::Core Qt5::Widgets Qt5::Network)
target_link_libraries(Robot_Gui_V3 stdc++fs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


message(STATUS ${OpenCV_INCLUDE_DIRS})
message(STATUS ${OpenCV_LIBS})


include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

