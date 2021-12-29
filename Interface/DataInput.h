#ifndef ROBOT_GUI_V3_DATAINPUT_H
#define ROBOT_GUI_V3_DATAINPUT_H

#include "../WidgetData.h"
#include "opencv2/opencv.hpp"
#include "../InternalJson.h"

#define CUSTOM_MSG_HEADER_SIZE 6

/**
 * @class LocalServer
 * Server parses data into widgetData format
 *
 * @author Patrick McGuire (Patrick-McGuire)
 */
class DataInput {
public:
    /**
     * Constructor
     * @param _widgetData WidgetData object to input to
     */
    DataInput(WidgetData *_widgetData);

    /**
     * Parses a buffer into widgetData format
     * @param input buffer to parse
     * @param len length of buffer
     */
    void parse(char *input, int len);

private:
    /**
     * Parses a json string into widgetData format
     * @param input json to parse
     * @param len length of json string
     */
    void parseJson(const char *input, int len);

    /**
     * Parses a image from a buffer
     * @param input binary image
     * @param len size of image binary
     */
    void parseImg(char *input, int len);

    /**
     * Writes the output data to a given socket
     * @param returnType what data to return
     * @param socket socket to write to
     */
    void parseArray(rapidjson::Value *value, const InternalJson::SharedPtr &json);

    union LengthConverter {
        std::int32_t length;
        std::uint8_t bytes[4];
    };
    LengthConverter messageSize{};
    WidgetData *widgetData;
};


#endif //ROBOT_GUI_V3_DATAINPUT_H
