#include "BaseInterface.h"

BaseInterface::BaseInterface() {
    widgetData = nullptr;
}

void BaseInterface::setWidgetData(WidgetData *_widgetData) {
    widgetData = _widgetData;
}

WidgetData::internalJsonTypes BaseInterface::getKeyType(const std::string &key) {
    return widgetData->getKeyType(key);
}

bool BaseInterface::isActive() {
    return widgetData->getGuiActive();
}

void BaseInterface::setImg(const std::string &key, const cv::Mat &img) {
    widgetData->setImg(key, img);
}

void BaseInterface::setJSON(const std::string &key, const WidgetData::internalJSON_ptr &val) {
    widgetData->setJSON(key, val);
}

void BaseInterface::setBool(const std::string &key, bool val) {
    auto currentKeyType = widgetData->getKeyType(key);
    auto json = widgetData->getJSON(key);
    json->boolVal = val;
    json->type = WidgetData::bool_t;
    if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
        widgetData->setJSON(key, json);
    } else {
        widgetData->setKeyUpdated(key);
    }
}

void BaseInterface::setInt(const std::string &key, int val) {
    auto currentKeyType = widgetData->getKeyType(key);
    auto json = widgetData->getJSON(key);
    json->intVal = val;
    json->type = WidgetData::int_t;
    if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
        widgetData->setJSON(key, json);
    } else {
        widgetData->setKeyUpdated(key);
    }
}

void BaseInterface::setDouble(const std::string &key, double val) {
    auto currentKeyType = widgetData->getKeyType(key);
    auto json = widgetData->getJSON(key);
    json->doubleVal = val;
    json->type = WidgetData::double_t;
    if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
        widgetData->setJSON(key, json);
    } else {
        widgetData->setKeyUpdated(key);
    }
}

void BaseInterface::setString(const std::string &key, const std::string &val) {
    auto currentKeyType = widgetData->getKeyType(key);
    auto json = widgetData->getJSON(key);
    json->stringVal = val;
    json->type = WidgetData::string_t;
    if(currentKeyType == WidgetData::img_t || currentKeyType == WidgetData::none_t) {
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

WidgetData::internalJSON_ptr BaseInterface::getJSON(const std::string &key) {
    return widgetData->getJSON(key);
}
