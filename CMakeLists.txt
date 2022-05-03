cmake_minimum_required(VERSION 3.16)
project(Robot_Gui_V3)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Run bash script to finish setup tasks
execute_process(
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND scripts/compile_helper.bash ${CMAKE_SOURCE_DIR}
)

set(rapidxml_files
        lib/rapidxml/rapidxml_print.hpp
        lib/rapidxml/rapidxml.hpp
        lib/rapidxml/rapidxml_iterators.hpp
        lib/rapidxml/rapidxml_utils.hpp
        )

set(xml_interface_files
        src/Config/XMLInput.cpp src/Config/XMLInput.h
        src/Config/XMLOutput.cpp src/Config/XMLOutput.h
        src/Config/AppConfig.cpp src/Config/AppConfig.h)

set(widget_type_files
        src/CustomWidgets/VideoWidget.cpp src/CustomWidgets/VideoWidget.h
        src/CustomWidgets/TextBoxWidget.cpp src/CustomWidgets/TextBoxWidget.h
        src/CustomWidgets/BaseWidget.cpp src/CustomWidgets/BaseWidget.h
        src/CustomWidgets/TabWidget.cpp src/CustomWidgets/TabWidget.h
        src/CoreWidgets/MenuWidget.cpp src/CoreWidgets/MenuWidget.h
        src/CustomWidgets/SimpleButtonWidget.cpp src/CustomWidgets/SimpleButtonWidget.h
        src/CustomWidgets/MultiBarGraphWidget.cpp src/CustomWidgets/MultiBarGraphWidget.h
        src/CustomWidgets/AnnunciatorWidget.cpp src/CustomWidgets/AnnunciatorWidget.h
        src/CustomWidgets/SimpleConsoleWidget.cpp src/CustomWidgets/SimpleConsoleWidget.h
        src/CustomWidgets/ROVStatusWidget.cpp src/CustomWidgets/ROVStatusWidget.h
        src/CustomWidgets/CompleteConsoleWidget.cpp src/CustomWidgets/CompleteConsoleWidget.h
        src/CustomWidgets/MissionStatusWidget.cpp src/CustomWidgets/MissionStatusWidget.h
        src/CustomWidgets/DropDownTextBoxWidget.cpp src/CustomWidgets/DropDownTextBoxWidget.h
        src/CustomWidgets/CompassWidget.cpp src/CustomWidgets/CompassWidget.h
        src/CustomWidgets/SettingsTab.cpp src/CustomWidgets/SettingsTab.h src/CustomWidgets/AttitudeWidget.cpp src/CustomWidgets/AttitudeWidget.h)

set(widget_part_files
        src/CustomWidgets/WidgetParts/SimpleBarGraph.cpp src/CustomWidgets/WidgetParts/BaseGraphDisplay.h
        src/CustomWidgets/WidgetParts/CircleBarGraph.cpp src/CustomWidgets/WidgetParts/CircleBarGraph.h
        src/CustomWidgets/WidgetParts/LineTextDisplay.cpp src/CustomWidgets/WidgetParts/LineTextDisplay.h
        src/CustomWidgets/WidgetParts/CompassDisplay.cpp src/CustomWidgets/WidgetParts/CompassDisplay.h
        src/CustomWidgets/WidgetParts/BasicImageDisplay.cpp src/CustomWidgets/WidgetParts/BasicImageDisplay.h
        src/CustomWidgets/WidgetParts/SideTabWidget.cpp src/CustomWidgets/WidgetParts/SideTabWidget.h src/CustomWidgets/WidgetParts/AttitudeDisplay.cpp src/CustomWidgets/WidgetParts/AttitudeDisplay.h)

set(settings_panel_files
        src/CustomWidgets/SettingsPanels/BaseSettingsPanel.cpp src/CustomWidgets/SettingsPanels/BaseSettingsPanel.h src/CustomWidgets/SettingsPanels/InterfaceSettings.cpp src/CustomWidgets/SettingsPanels/InterfaceSettings.h src/CustomWidgets/SettingsPanels/RawDataView.cpp src/CustomWidgets/SettingsPanels/RawDataView.h)

set(interface_files
        src/Interface/DataInput.cpp src/Interface/DataInput.h
        src/Interface/BaseInterface.cpp
        src/Interface/ThreadedInterface.cpp src/Interface/ThreadedInterface.h
        src/Interface/RandomDataInterface.cpp src/Interface/RandomDataInterface.h
        src/Interface/WebcamStreamInterface.cpp
        src/Interface/FlagCheckerInterface.cpp src/Interface/FlagCheckerInterface.h
        )

set(core_files
        src/GUIMaker.cpp src/GUIMaker.h
        src/GuiInstance.cpp src/GuiInstance.h
        src/WidgetData.h
        src/RobotGui.h
        src/GuiCore.cpp src/GuiCore.h
        src/Theme.cpp src/Theme.h
        lib/CommonFunctions.cpp lib/CommonFunctions.h
        src/InternalJson.cpp src/InternalJson.h
        src/CustomJSONStructure.h)

set(all_gui_files
        ${rapidxml_files}
        ${widget_type_files}
        ${widget_part_files}
        ${settings_panel_files}
        ${networking_files}
        ${interface_files}
        ${xml_interface_files}
        ${core_files} src/CustomWidgets/LivePlotWidget.cpp src/CustomWidgets/LivePlotWidget.h src/Interface/ServerInterface.cpp src/Interface/ServerInterface.h)

add_executable(Robot_Gui_V3 main.cpp ${all_gui_files})
set(SOURCE_FILES main.cpp)
include_directories(/usr/include/)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(OpenCV REQUIRED)

target_link_libraries(Robot_Gui_V3 Qt5::Core Qt5::Widgets Qt5::Network Qt5::Charts)
target_link_libraries(Robot_Gui_V3 stdc++fs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


message(STATUS ${OpenCV_INCLUDE_DIRS})
message(STATUS ${OpenCV_LIBS})


include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

