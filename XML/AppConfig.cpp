//
// Created by patrick on 11/12/21.
//

#include "AppConfig.h"

#include <utility>

void AppConfig::parseConfig() {
    if(createConfigDir()) {
        xmlFilepath = configNoXmlPath;
    } else {
        std::ifstream file(getConfigPath() + std::string(configFileName));
        std::string activeLine;
        while (std::getline(file, activeLine)) {
            std::string key = split(activeLine, configSep, 0);
            std::string val = split(activeLine, configSep, 1);
            if(key == configXmlPath) {
                xmlFilepath = val;
            }
        }
    }

}

void AppConfig::setConfig() {
    std::ofstream outfile;
    outfile.open(getConfigPath() + std::string(configFileName), std::ofstream::out | std::ofstream::trunc);
    outfile << configXmlPath << configSep << xmlFilepath << std::endl;
    outfile.close();
}

bool AppConfig::createConfigDir() {
    if(std::experimental::filesystem::create_directories(getConfigPath())) {
        createConfigFile();
        return true;
    } else if(!fileExists(getConfigPath() + std::string(configFileName))) {
        createConfigFile();
        return true;
    }
    return false;
}

void AppConfig::setDefaultXmlPath(std::string path) {
    xmlFilepath = std::move(path);
}

std::string AppConfig::getDefaultXmlPath() {
    return xmlFilepath;
}

void AppConfig::createConfigFile() {
    std::ofstream outfile (getConfigPath() + std::string(configFileName));
    outfile << configXmlPath << configSep << configNoXmlPath << std::endl;
    outfile.close();
}

std::string AppConfig::getConfigPath() {
    return getpwuid(getuid())->pw_dir + std::string(configFilePath);
}

std::string AppConfig::split(const std::string &str, char delim, int index) {
    std::stringstream strStream(str);
    std::string item;
    for(int i = 0; std::getline(strStream, item, delim); i++) {
        if(i == index) {
            return item;
        }
    }
    return "";
}

bool AppConfig::fileExists(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

