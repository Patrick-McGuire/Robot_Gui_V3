//
// Created by nathan on 10/30/20.
//

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <iostream>

namespace CommonFunctions {
    double Clamp(double value, double minValue, double maxValue);

    double Interpolate(double value, double in_min, double in_max, double out_min, double out_max);

    double AngleDiffRadians(double from, double to);

    double DegreesToRadians(double degrees);

    double RadiansToDegrees(double radians);

    std::vector<std::string> SplitString(std::string input, const std::string &delimiter);

    std::string RoundToString(double input, int decimals);

    std::string LStrip(const std::string &s, const std::string &white_space_chars);

    std::string LStrip(const std::string &s);

    std::string RStrip(const std::string &s, const std::string &white_space_chars);

    std::string RStrip(const std::string &s);

    std::string Strip(const std::string &s, const std::string &white_space_chars);

    std::string Strip(const std::string &s);

    std::map<std::string, std::string> CreateMapFromString(std::string input);

    std::array<int, 3> GetRGBFromString(const std::string& input, std::array<int, 3> default_value = {255, 255, 255});
};