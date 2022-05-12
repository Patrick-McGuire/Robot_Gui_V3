#ifndef ROBOT_GUI_V3_LINECONFIG_H
#define ROBOT_GUI_V3_LINECONFIG_H

#include "boost/optional.hpp"
#include "../../RobotGui.h"
#include "../../../lib/rapidxml/rapidxml.hpp"
#include "QObject"
#include "../BaseStructure/WidgetBaseConfig.h"

namespace RobotGui {

    /**
     * @class LineConfig
     * Class for configuration data that follows the line format
     *
     * @author Patrick McGuire (Patrick-McGuire)
     */
    class LineConfig : public WidgetBaseConfig {
    Q_OBJECT
    public:
        /**
         * This class is only to be accessed though a shared pointer
         */
        typedef std::shared_ptr<LineConfig> SharedPtr;

        /**
         * This hold information for each line
         */
        struct LineInfo {
            std::string label;
            std::string source;
            // Optional
            boost::optional<std::string> color;
            boost::optional<std::string> type;
            boost::optional<double> min;
            boost::optional<double> max;
        };

        /**
         * Static create method inorder to only use shared pointers
         * @param _type type to make this config
         * @return std::shared_ptr container new WidgetBaseConfig
         */
        static SharedPtr create(WidgetType _type);

        /**
         * Static create method inorder to only use shared pointers
         * @param _type type to make this config
         * @return std::shared_ptr container new WidgetBaseConfig
         */
        static SharedPtr create(const std::string &_type);

        /**
         * Static create method inorder to only use shared pointers
         * @return std::shared_ptr container new WidgetBaseConfig
         */
        static SharedPtr create();

        // Required
        std::vector<LineInfo> lines;


    private:

        /**
         * Constructor
         * @param _type type of widget this is for
         */
        explicit LineConfig(WidgetType _type);
    };
}

#endif //ROBOT_GUI_V3_LINECONFIG_H
