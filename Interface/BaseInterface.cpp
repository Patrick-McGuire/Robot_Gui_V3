#include "BaseInterface.h"

BaseInterface::BaseInterface() {
    widgetData = nullptr;
}

void BaseInterface::setWidgetData(WidgetData *_widgetData) {
    widgetData = _widgetData;
}

InternalJson::Types BaseInterface::getJsonKeyType(const std::string &key) {
    return widgetData->getJsonKeyType(key);
}

bool BaseInterface::isActive() {
    return widgetData->getGuiActive();
}

void BaseInterface::setImg(const std::string &key, const cv::Mat &img) {
    widgetData->setImg(key, img);
}

void BaseInterface::setJSON(const std::string &key, const InternalJson::SharedPtr &val) {
    widgetData->setJSON(key, val);
}

void BaseInterface::setBool(const std::string &key, bool val) {
    auto currentKeyType = widgetData->getJsonKeyType(key);
    auto json = widgetData->getJSON(key);
    json->setBool(val);
    if(currentKeyType == InternalJson::none_t) {
        widgetData->setJSON(key, json);
    } else {
        widgetData->setKeyUpdated(key);
    }
}

void BaseInterface::setInt(const std::string &key, int val) {
    auto currentKeyType = widgetData->getJsonKeyType(key);
    auto json = widgetData->getJSON(key);
    json->setInt(val);
    if(currentKeyType == InternalJson::none_t) {
        widgetData->setJSON(key, json);
    } else {
        widgetData->setKeyUpdated(key);
    }
}

void BaseInterface::setDouble(const std::string &key, double val) {
    auto currentKeyType = widgetData->getJsonKeyType(key);
    auto json = widgetData->getJSON(key);
    json->setDouble(val);
    if(currentKeyType == InternalJson::none_t) {
        widgetData->setJSON(key, json);
    } else {
        widgetData->setKeyUpdated(key);
    }
}

void BaseInterface::setString(const std::string &key, const std::string &val) {
    auto currentKeyType = widgetData->getJsonKeyType(key);
    auto json = widgetData->getJSON(key);
    json->setString(val);
    if(currentKeyType == InternalJson::none_t) {
        widgetData->setJSON(key, json);
    } else {
        widgetData->setKeyUpdated(key);
    }
}

bool BaseInterface::getBool(const std::string &key) {
    return widgetData->getBool(key);
}

int BaseInterface::getInt(const std::string &key) {
    return widgetData->getInt(key);
}

double BaseInterface::getDouble(const std::string &key) {
    return widgetData->getDouble(key);
}

std::string BaseInterface::getString(const std::string &key) {
    return widgetData->getString(key);
}

cv::Mat BaseInterface::getImg(const std::string &key) {
    return widgetData->getImg(key);
}

InternalJson::SharedPtr BaseInterface::getJSON(const std::string &key) {
    return widgetData->getJSON(key);
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
