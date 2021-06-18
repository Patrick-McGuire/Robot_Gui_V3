cmake_minimum_required(VERSION 3.19)
project(Robot_Gui_V3)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(Robot_Gui_V3 main.cpp GUIMaker.cpp GUIMaker.h CustomWidgets/TextBoxWidget.cpp CustomWidgets/TextBoxWidget.h CustomWidgets/BaseWidget.cpp CustomWidgets/BaseWidget.h RobotGUI.cpp RobotGUI.h WidgetInfo.cpp WidgetInfo.h WidgetData.cpp WidgetData.h Constants.h)

set(Qt5_DIR "~/Qt/5.12.2/clang_64/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
target_link_libraries(Robot_Gui_V3 Qt5::Core Qt5::Widgets )

#set(OpenCV_DIR)

find_package( OpenCV REQUIRED )
set(SOURCE_FILES main.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )

