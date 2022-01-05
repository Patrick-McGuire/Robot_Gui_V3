/*
 * Core functions that I use often
 */


#include <sstream>
#include <iomanip>
#include "CommonFunctions.h"
#include "chrono"


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
 * Gets value from a <string string> map for a given key
 * If that value is not there, returns a default
 */
std::string CommonFunctions::GetStringFromMap(std::map<std::string, std::string> _map, const std::string &_key, std::string _default_value) {
    if (_map.count(_key)) {
        return _map[_key];
    } else {
        return _default_value;
    }
}


/*
 * Takes in string like "(r,g,b)" or "{r,g,b}" and returns a std::array of the r,g,b values
 */
std::array<int, 3> CommonFunctions::GetRGBFromString(const std::string &input, std::array<int, 3> default_value) {
    auto cut_down_string = CommonFunctions::Strip(input, WHITESPACE + "(){}rgb");
    auto split_string = CommonFunctions::SplitString(cut_down_string, ",");
    if (split_string.size() == 3) {
        std::array<int, 3> output = {std::atoi(split_string[0].c_str()), std::atoi(split_string[1].c_str()), std::atoi(split_string[2].c_str())};
        return output;
    } else {
        return default_value;
    }
}

QColor CommonFunctions::GetQColorFromString(const std::string &input, std::array<int, 3> default_value) {
    if (input.find("rgb(") == std::string::npos) {
        return QColor(input.c_str());
    } else {
        auto r_g_b = CommonFunctions::GetRGBFromString(input, default_value);
        return {r_g_b[0], r_g_b[1], r_g_b[2]};
    }
}

std::string CommonFunctions::GetStringFromRGB(std::array<int, 3> r_g_b) {
    return ("rgb(" + std::to_string(r_g_b[0]) + "," + std::to_string(r_g_b[1]) + "," + std::to_string(r_g_b[2]) + ")");
}

std::string CommonFunctions::GenerateDarkerColor(const std::string &input_color, int delta) {
    auto r_g_b = CommonFunctions::GetRGBFromString(input_color);
    r_g_b[0] = CommonFunctions::Clamp(r_g_b[0] - delta, 0, 255);
    r_g_b[1] = CommonFunctions::Clamp(r_g_b[1] - delta, 0, 255);
    r_g_b[2] = CommonFunctions::Clamp(r_g_b[2] - delta, 0, 255);
    return CommonFunctions::GetStringFromRGB(r_g_b);
}

std::string CommonFunctions::GetContrastingTextColor(const std::string &background_color) {
    auto r_g_b = CommonFunctions::GetRGBFromString(background_color);
    if (fmax(fmax(r_g_b[0], r_g_b[1]), r_g_b[2]) > 127) {
        return "rgb(0,0,0)";
    } else {
        return "rgb(255,255,255)";
    }
}

std::string CommonFunctions::LowerCaseString(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });
    return input;
}

double CommonFunctions::getEpochTime() {
    return (double) std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch()).count() / 1000;
}