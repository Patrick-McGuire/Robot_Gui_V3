#ifndef ROBOT_GUI_V3_SOURCEMAPCONFIG_H
#define ROBOT_GUI_V3_SOURCEMAPCONFIG_H

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
    class SourceMapConfig : public WidgetBaseConfig {
    Q_OBJECT
    public:
        /**
         * This class is only to be accessed though a shared pointer
         */
        typedef std::shared_ptr<SourceMapConfig> SharedPtr;

        /**
         * Static create method inorder to only use shared pointers
         * @param _type type to make this config
         * @return std::shared_ptr container new WidgetBaseConfig
         */
        static SharedPtr create(WidgetConstants::Type _type);

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

        void parseXml(rapidxml::xml_node<> *node) override;

        // Required
        std::map<std::string, std::string> sourceMap;


    private:

        /**
         * Constructor
         * @param _type type of widget this is for
         */
        explicit SourceMapConfig(WidgetConstants::Type _type);
    };
}

#endif //ROBOT_GUI_V3_SOURCEMAPCONFIG_H
