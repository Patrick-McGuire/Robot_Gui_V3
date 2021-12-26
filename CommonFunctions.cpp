/*
 * Core functions that I use often
 */


#include <sstream>
#include <iomanip>
#include "CommonFunctions.h"


//Clamps a value between a min and max value
double CommonFunctions::Clamp(double value, double minValue, double maxValue) {
    return fmin(fmax(value, minValue), maxValue);
}

//Like the arduino map function
//Returns "value" scaled from between in_min and in_max to between out_min adn out_max
double CommonFunctions::Interpolate(double value, double in_min, double in_max, double out_min, double out_max) {
    double in_span = in_max - in_min;
    double out_span = out_max - out_min;

    double scaled = double(value - in_min) / double(in_span);
    return out_min + (scaled * out_span);
}

/*
 * Takes a current and desired angle in radians, returns a signed difference in angle in radians
 * It should do to - from
 */
double CommonFunctions::AngleDiffRadians(double from, double to) {
    // logic from https://bitbucket.org/whoidsl/ds_base/src/master/ds_util/src/ds_util/angle.cpp
    double dot = sin(from) * sin(to) + cos(from) * cos(to);
    double cross = cos(from) * sin(to) - sin(from) * cos(to);
    double diff = atan2(cross, dot);
    return diff;
}


//Converts degrees to radians
double CommonFunctions::DegreesToRadians(double degrees) {
    return degrees * 0.0174533;
}

//Converts radians to degrees
double CommonFunctions::RadiansToDegrees(double radians) {
    return radians * 57.2958;
}

//Splits a sting around a delimiter, and returns a vector
//Copied from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> CommonFunctions::SplitString(std::string input, const std::string &delimiter) {
    std::vector<std::string> out;
    size_t pos = 0;
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        out.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    out.push_back(input);
    return out;
}

//Rounds and converts to string
//Used for printing stuff to the screen
std::string CommonFunctions::RoundToString(double input, int decimals) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(decimals) << input;
    return stream.str();
}


const std::string WHITESPACE = " \n\r\t\f\v";

//Strips off leading whitespace
std::string CommonFunctions::LStrip(const std::string &s, const std::string &white_space_chars) {
    size_t start = s.find_first_not_of(white_space_chars);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string CommonFunctions::LStrip(const std::string &s) {
    return CommonFunctions::LStrip(s, WHITESPACE);
}

//Strips off trailing whitespace
std::string CommonFunctions::RStrip(const std::string &s, const std::string &white_space_chars) {
    size_t end = s.find_last_not_of(white_space_chars);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string CommonFunctions::RStrip(const std::string &s) {
    return CommonFunctions::RStrip(s, WHITESPACE);
}

//Strips leading and trailing whitespace
std::string CommonFunctions::Strip(const std::string &s, const std::string &white_space_chars) {
    return CommonFunctions::LStrip(CommonFunctions::RStrip(s, white_space_chars), white_space_chars);
}

//Strips leading and trailing whitespace
std::string CommonFunctions::Strip(const std::string &s) {
    return CommonFunctions::Strip(s, WHITESPACE);
}


/*
 * Takes a key-value string formatted correctly, and returns a map containing that data
 *
 * Formatting example
 * {a: b, c: d}
 */
std::map<std::string, std::string> CommonFunctions::CreateMapFromString(std::string input) {
    input.erase(0, 1);
    input.erase(input.size() - 1);
    std::map<std::string, std::string> out_map;

    auto split_by_commas = CommonFunctions::SplitString(input, ",");
    for (const auto &split_section : split_by_commas) {
        auto data = CommonFunctions::SplitString(split_section, ":");
        out_map.insert({CommonFunctions::Strip(data[0], WHITESPACE + "\""), CommonFunctions::Strip(data[1], WHITESPACE + "\"")});
    }

    return out_map;
}

/*
 * Takes in string like "(r,g,b)" or "{r,g,b}" and returns a std::array of the r,g,b values
 */
std::array<int, 3> CommonFunctions::GetRGBFromString(const std::string& input, std::array<int, 3> default_value) {
    auto cut_down_string = CommonFunctions::Strip(input, WHITESPACE + "(){}rgb");
    auto split_string = CommonFunctions::SplitString(cut_down_string, ",");
    if (split_string.size() == 3) {
        std::array<int, 3> output = {std::atoi(split_string[0].c_str()), std::atoi(split_string[1].c_str()), std::atoi(split_string[2].c_str())};
        return output;
    } else {
        return default_value;
    }
}

