#include "BaseInterface.h"
#include "../WidgetData.h"
#include "../InternalJson.h"

RobotGui::BaseInterface::BaseInterface() {
    widgetData = nullptr;
}

void RobotGui::BaseInterface::setWidgetData(RobotGui::WidgetData *_widgetData) {
    widgetData = _widgetData;
}

bool RobotGui::BaseInterface::isActive() {
    return widgetData->getGuiActive();
}

void RobotGui::BaseInterface::setImg(const std::string &key, const cv::Mat &img) {
    widgetData->setImg(key, img);
}

bool RobotGui::BaseInterface::outputFlagExists(const std::string &key) {
    return widgetData->outputFlagExists(key);
}

bool RobotGui::BaseInterface::getFlagOutput(const std::string &key) {
    return widgetData->getFlagOutput(key);
}

void RobotGui::BaseInterface::clearOutputFlag(const std::string &key) {
    widgetData->clearOutputFlag(key);
}

RobotGui::InternalJson::SharedPtr RobotGui::BaseInterface::getFlagOutput() {
    return widgetData->getFlagOutput();
}

RobotGui::InternalJson::SharedPtr RobotGui::BaseInterface::getJson() {
    return widgetData->getJson();
}


void RobotGui::BaseInterface::setBool(const std::string &key, bool val) {
    widgetData->getJson()->mapGetOrAdd(key)->setBool(val);
    widgetData->setKeyUpdated(key);
}

void RobotGui::BaseInterface::setInt(const std::string &key, int val) {
    widgetData->getJson()->mapGetOrAdd(key)->setInt(val);
    widgetData->setKeyUpdated(key);
}

void RobotGui::BaseInterface::setDouble(const std::string &key, double val) {
    widgetData->getJson()->mapGetOrAdd(key)->setDouble(val);
    widgetData->setKeyUpdated(key);
}

void RobotGui::BaseInterface::setString(const std::string &key, const std::string &val) {
    widgetData->getJson()->mapGetOrAdd(key)->setString(val);
    widgetData->setKeyUpdated(key);
}

void RobotGui::BaseInterface::setMap(const std::string &key, const RobotGui::InternalJson::SharedPtr& val) {
    widgetData->getJson()->mapSet(key, val);
    widgetData->setKeyUpdated(key);
}

RobotGui::WidgetData *RobotGui::BaseInterface::getWidgetData() {
    return widgetData;
}
