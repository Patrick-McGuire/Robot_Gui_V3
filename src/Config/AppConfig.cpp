//
// Created by patrick on 11/12/21.
//

#include "AppConfig.h"

#include <utility>

void RobotGui::AppConfig::parse() {
    if (createDir()) {
        xmlFilepath = RobotGui::APP_CONFIG_NO_XML_PATH;
    } else {
        std::ifstream file(getPath() + std::string(RobotGui::APP_CONFIG_FILE_NAME));
        std::string activeLine;
        while (std::getline(file, activeLine)) {
            std::string key = splitStr(activeLine, RobotGui::APP_CONFIG_SEP, 0);
            std::string val = splitStr(activeLine, RobotGui::APP_CONFIG_SEP, 1);
            if (key == RobotGui::APP_CONFIG_XML_PATH) {
                xmlFilepath = val;
            }
        }
    }

}

void RobotGui::AppConfig::write() {
    std::ofstream outfile;
    outfile.open(getPath() + std::string(RobotGui::APP_CONFIG_FILE_NAME), std::ofstream::out | std::ofstream::trunc);
    outfile << RobotGui::APP_CONFIG_XML_PATH << RobotGui::APP_CONFIG_SEP << xmlFilepath << std::endl;
    outfile.close();
}

void RobotGui::AppConfig::setDefaultXmlPath(std::string path) {
    xmlFilepath = std::move(path);
}

std::string RobotGui::AppConfig::getDefaultXmlPath() const {
    return xmlFilepath;
}

bool RobotGui::AppConfig::createDir() {
    if (std::experimental::filesystem::create_directories(getPath())) {
        createFile();
        return true;
    } else if (!fileExists(getPath() + std::string(RobotGui::APP_CONFIG_FILE_NAME))) {
        createFile();
        return true;
    }
    return false;
}

void RobotGui::AppConfig::createFile() {
    std::ofstream outfile(getPath() + std::string(RobotGui::APP_CONFIG_FILE_NAME));
    outfile << RobotGui::APP_CONFIG_XML_PATH << RobotGui::APP_CONFIG_SEP << RobotGui::APP_CONFIG_NO_XML_PATH << std::endl;
    outfile.close();
}

std::string RobotGui::AppConfig::getPath() {
    return getpwuid(getuid())->pw_dir + std::string(RobotGui::APP_CONFIG_FILE_PATH);
}

std::string RobotGui::AppConfig::splitStr(const std::string &str, char delim, int index) {
    std::stringstream strStream(str);
    std::string item;
    for (int i = 0; std::getline(strStream, item, delim); i++) {
        if (i == index) {
            return item;
        }
    }
    return "";
}

bool RobotGui::AppConfig::fileExists(const std::string &path) {
    if (FILE *file = fopen(path.c_str(), "r")) {
        fclose(file);
        return true;
    }
    return false;
}

void RobotGui::AppConfig::load() {
    std::string rootPath = getPath();
    AppConfig::loadImageFromFile(rootPath + RobotGui::APP_CONFIG_ARROW_ASSET_PATH, RobotGui::ARROW_ASSET_NAME);
    AppConfig::loadImageFromFile(rootPath + RobotGui::APP_CONFIG_COMPASS_ASSET_PATH, RobotGui::COMPASS_ASSET_NAME);
    RobotGui::AppConfig::loadImageFromFile(rootPath + RobotGui::APP_CONFIG_CROSS_HAIR_ASSET_PATH, RobotGui::CROSS_HAIR_ASSET_NAME);
    RobotGui::AppConfig::loadImageFromFile(rootPath + RobotGui::APP_CONFIG_ROLL_DIAL_ASSET_PATH, RobotGui::ROLL_DIAL_ASSET_NAME);
    RobotGui::AppConfig::loadImageFromFile(rootPath + RobotGui::APP_CONFIG_ROLL_POINTER_ASSET_PATH, RobotGui::ROLL_POINTER_ASSET_NAME);
}

void RobotGui::AppConfig::loadImageFromFile(const std::string& filePath, const std::string& target) {
    if (AppConfig::fileExists(filePath)) {
        assets[target] = cv::imread(filePath, cv::IMREAD_UNCHANGED);
    } else {
        std::cout << "Can't load image from filepath " << filePath << std::endl;
    }
}

cv::Mat RobotGui::AppConfig::getAsset(const std::string &key) {
    return assets.count(key) != 0 ? assets[key] : cv::Mat();
}