#ifndef ROBOT_GUI_V3_WIDGETCOLLECTIONCONFIG_H
#define ROBOT_GUI_V3_WIDGETCOLLECTIONCONFIG_H

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
    class WidgetCollectionConfig : public WidgetBaseConfig {
    Q_OBJECT
    public:
        /**
         * This class is only to be accessed though a shared pointer
         */
        typedef std::shared_ptr<WidgetCollectionConfig> SharedPtr;

        struct TabInfo {
            std::string name;
            std::vector<WidgetBaseConfig::SharedPtr> widgets;
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
        std::vector<TabInfo> tabs;
        //        std::vector<std::string> tabNames;
//        std::vector<std::vector<std::shared_ptr<WidgetConfig>>> tabWidgets;

    private:

        /**
         * Constructor
         * @param _type type of widget this is for
         */
        explicit WidgetCollectionConfig(WidgetType _type);
    };
}


#endif //ROBOT_GUI_V3_WIDGETCOLLECTIONCONFIG_H
