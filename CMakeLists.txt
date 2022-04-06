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
        XML/XMLInput.cpp XML/XMLInput.h
        XML/XMLOutput.cpp XML/XMLOutput.h
        XML/AppConfig.cpp XML/AppConfig.h)

set(widget_type_files
        CustomWidgets/VideoWidget.cpp CustomWidgets/VideoWidget.h
        CustomWidgets/TextBoxWidget.cpp CustomWidgets/TextBoxWidget.h
        CustomWidgets/BaseWidget.cpp CustomWidgets/BaseWidget.h
        CustomWidgets/TabWidget.cpp CustomWidgets/TabWidget.h
        CoreWidgets/MenuWidget.cpp CoreWidgets/MenuWidget.h
        CustomWidgets/SimpleButtonWidget.cpp CustomWidgets/SimpleButtonWidget.h
        CustomWidgets/MultiBarGraphWidget.cpp CustomWidgets/MultiBarGraphWidget.h
        CustomWidgets/AnnunciatorWidget.cpp CustomWidgets/AnnunciatorWidget.h
        CustomWidgets/SimpleConsoleWidget.cpp CustomWidgets/SimpleConsoleWidget.h
        CustomWidgets/ROVStatusWidget.cpp CustomWidgets/ROVStatusWidget.h
        CustomWidgets/CompleteConsoleWidget.cpp CustomWidgets/CompleteConsoleWidget.h
        CustomWidgets/MissionStatusWidget.cpp CustomWidgets/MissionStatusWidget.h
        CustomWidgets/DropDownTextBoxWidget.cpp CustomWidgets/DropDownTextBoxWidget.h
        CustomWidgets/CompassWidget.cpp CustomWidgets/CompassWidget.h
        CustomWidgets/SettingsTab.cpp CustomWidgets/SettingsTab.h)

set(widget_part_files
        CustomWidgets/WidgetParts/SimpleBarGraph.cpp CustomWidgets/WidgetParts/BaseGraphDisplay.h
        CustomWidgets/WidgetParts/CircleBarGraph.cpp CustomWidgets/WidgetParts/CircleBarGraph.h
        CustomWidgets/WidgetParts/LineTextDisplay.cpp CustomWidgets/WidgetParts/LineTextDisplay.h
        CustomWidgets/WidgetParts/CompassDisplay.cpp CustomWidgets/WidgetParts/CompassDisplay.h
        CustomWidgets/WidgetParts/BasicImageDisplay.cpp CustomWidgets/WidgetParts/BasicImageDisplay.h
        CustomWidgets/WidgetParts/SideTabWidget.cpp CustomWidgets/WidgetParts/SideTabWidget.h)

set(settings_panel_files
        CustomWidgets/SettingsPanels/BaseSettingsPanel.cpp CustomWidgets/SettingsPanels/BaseSettingsPanel.h CustomWidgets/SettingsPanels/InterfaceSettings.cpp CustomWidgets/SettingsPanels/InterfaceSettings.h CustomWidgets/SettingsPanels/RawDataView.cpp CustomWidgets/SettingsPanels/RawDataView.h)

set(interface_files
        Interface/DataInput.cpp Interface/DataInput.h
        Interface/BaseInterface.cpp
        Interface/ThreadedInterface.cpp Interface/ThreadedInterface.h
        Interface/RandomDataInterface.cpp Interface/RandomDataInterface.h
        Interface/WebcamStreamInterface.cpp
        Interface/FlagCheckerInterface.cpp Interface/FlagCheckerInterface.h
        )

set(core_files
        GUIMaker.cpp GUIMaker.h
        GuiInstance.cpp GuiInstance.h
        WidgetData.h
        RobotGui.h
        GuiCore.cpp GuiCore.h
        Theme.cpp Theme.h
        CommonFunctions.cpp CommonFunctions.h
        InternalJson.cpp InternalJson.h
        CustomJSONStructure.h)

set(all_gui_files
        ${rapidxml_files}
        ${widget_type_files}
        ${widget_part_files}
        ${settings_panel_files}
        ${networking_files}
        ${interface_files}
        ${xml_interface_files}
        ${core_files} CustomWidgets/LivePlotWidget.cpp CustomWidgets/LivePlotWidget.h Interface/ServerInterface.cpp Interface/ServerInterface.h)

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

