//
// Created by patrick on 11/12/21.
//

#include "AppConfig.h"

#include <utility>

void AppConfig::parse() {
    if(createDir()) {
        xmlFilepath = appConfigNoXmlPath;
    } else {
        std::ifstream file(getPath() + std::string(appConfigFileName));
        std::string activeLine;
        while (std::getline(file, activeLine)) {
            std::string key = splitStr(activeLine, appConfigSep, 0);
            std::string val = splitStr(activeLine, appConfigSep, 1);
            if(key == appConfigXmlPath) {
                xmlFilepath = val;
            }
        }
    }

}

void AppConfig::write() {
    std::ofstream outfile;
    outfile.open(getPath() + std::string(appConfigFileName), std::ofstream::out | std::ofstream::trunc);
    outfile << appConfigXmlPath << appConfigSep << xmlFilepath << std::endl;
    outfile.close();
}

void AppConfig::setDefaultXmlPath(std::string path) {
    xmlFilepath = std::move(path);
}

std::string AppConfig::getDefaultXmlPath() const {
    return xmlFilepath;
}

bool AppConfig::createDir() {
    if(std::experimental::filesystem::create_directories(getPath())) {
        createFile();
        return true;
    } else if(!fileExists(getPath() + std::string(appConfigFileName))) {
        createFile();
        return true;
    }
    return false;
}

void AppConfig::createFile() {
    std::ofstream outfile (getPath() + std::string(appConfigFileName));
    outfile << appConfigXmlPath << appConfigSep << appConfigNoXmlPath << std::endl;
    outfile.close();
}

std::string AppConfig::getPath() {
    return getpwuid(getuid())->pw_dir + std::string(appConfigFilePath);
}

std::string AppConfig::splitStr(const std::string &str, char delim, int index) {
    std::stringstream strStream(str);
    std::string item;
    for(int i = 0; std::getline(strStream, item, delim); i++) {
        if(i == index) {
            return item;
        }
    }
    return "";
}

bool AppConfig::fileExists(const std::string& path) {
    if (FILE *file = fopen(path.c_str(), "r")) {
        fclose(file);
        return true;
    }
    return false;
}

