#include "BaseInterface.h"

BaseInterface::BaseInterface() {
    widgetData = nullptr;
}

void BaseInterface::setWidgetData(WidgetData *_widgetData) {
    widgetData = _widgetData;
}

bool BaseInterface::isActive() {
    return widgetData->getGuiActive();
}

void BaseInterface::setImg(const std::string &key, const cv::Mat &img) {
    widgetData->setImg(key, img);
}

bool BaseInterface::outputFlagExists(const std::string &key) {
    return widgetData->outputFlagExists(key);
}

bool BaseInterface::getFlagOutput(const std::string &key) {
    return widgetData->getFlagOutput(key);
}

void BaseInterface::clearOutputFlag(const std::string &key) {
    widgetData->clearOutputFlag(key);
}

std::map<std::string, bool> *BaseInterface::getFlagOutput() {
    return widgetData->getFlagOutput();
}

InternalJson::SharedPtr BaseInterface::getJson() {
    return widgetData->getJson();
}


void BaseInterface::setBool(const std::string &key, bool val) {
    widgetData->getJson()->mapGetOrAdd(key)->setBool(val);
    widgetData->setKeyUpdated(key);
}

void BaseInterface::setInt(const std::string &key, int val) {
    widgetData->getJson()->mapGetOrAdd(key)->setInt(val);
    widgetData->setKeyUpdated(key);
}

void BaseInterface::setDouble(const std::string &key, double val) {
    widgetData->getJson()->mapGetOrAdd(key)->setDouble(val);
    widgetData->setKeyUpdated(key);
}

void BaseInterface::setString(const std::string &key, const std::string &val) {
    widgetData->getJson()->mapGetOrAdd(key)->setString(val);
    widgetData->setKeyUpdated(key);
}

void BaseInterface::setMap(const std::string &key, const InternalJson::SharedPtr& val) {
    widgetData->getJson()->mapSet(key, val);
    widgetData->setKeyUpdated(key);
}

WidgetData *BaseInterface::getWidgetData() {
    return widgetData;
}
