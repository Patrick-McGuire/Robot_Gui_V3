#ifndef ROBOT_GUI_V3_DATAINPUT_H
#define ROBOT_GUI_V3_DATAINPUT_H
#include "../WidgetData.h"

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
     * Different types of inputs
     */
    enum DataInputType {
        CUSTOM_MSG_FORMAT,
        THREADED,
    };

    DataInput(WidgetData *_widgetData, DataInputType _type);

    /**
     * Parses a buffer into widgetData format
     * @param input buffer to parse
     * @param len length of buffer
     */
    void parse(const char *input, int len);

private:
    union LengthConverter {
        std::int32_t length;
        std::uint8_t bytes[4];
    };
    LengthConverter messageSize;
    WidgetData *widgetData;
    DataInputType type;

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
    void parseImg(const char *input, int len);
};


#endif //ROBOT_GUI_V3_DATAINPUT_H
