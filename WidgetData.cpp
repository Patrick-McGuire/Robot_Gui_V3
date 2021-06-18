//
// Created by patrick on 6/18/21.
//

#include "WidgetData.h"

//WidgetData::WidgetData() {
//
//}

std::string WidgetData::getString(std::string key) { return stringMap[key]; }
double WidgetData::getDouble(std::string key) {  return doubleMap[key]; }
int WidgetData::getInt(std::string key) { return intMap[key]; }

void WidgetData::setString(std::string key, std::string value) { stringMap[key] = value; }
void WidgetData::setInt(std::string key, int value) { intMap[key] = value; }
void WidgetData::setDouble(std::string key, double value) { doubleMap[key] = value; }
