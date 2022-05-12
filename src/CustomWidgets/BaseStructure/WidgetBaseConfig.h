#ifndef ROBOT_GUI_V3_WIDGETBASECONFIG_H
#define ROBOT_GUI_V3_WIDGETBASECONFIG_H

#include "boost/optional.hpp"
#include "../../RobotGui.h"
#include "../../../lib/rapidxml/rapidxml.hpp"
#include "QObject"

namespace RobotGui {
    enum WidgetType : int;

    /**
     * @class WidgetBaseConfig
     * Base class for configuration data
     *
     * @author Patrick McGuire (Patrick-McGuire)
     */
    class WidgetBaseConfig : public QObject {
    Q_OBJECT
    public:
        /**
         * This class is only to be accessed though a shared pointer
         */
        typedef std::shared_ptr<WidgetBaseConfig> SharedPtr;

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

        /**
         * Sets the type based on a string
         * @param _type type to set
         */
        static WidgetType getType(const std::string &_type);

        /**
         * Sets the type based on a string
         * @param _type type to set
         */
        std::string getTypeString() const;

        /**
         * Shows a menu in which to edit this config
         */
        void showEditMenu();

        /**
         * Members
         */
        // Required members
        WidgetType type;
        int x = 0;
        int y = 0;
        bool hidden = false;
        bool draggable = true;
        bool staticPos = false;
        std::string objectName;         // Not set by XML parser
        // Optional members
        boost::optional<std::string> title;
        boost::optional<std::string> source;
        boost::optional<int> height;
        boost::optional<int> width;
        boost::optional<int> size;
        boost::optional<std::string> min;
        boost::optional<std::string> max;
        boost::optional<double> range;
        boost::optional<int> rowNumber;
        boost::optional<int> columnNumber;
        // Optional style members
        boost::optional<std::string> font;
        boost::optional<std::string> backgroundColor;
        boost::optional<std::string> foregroundColor;
        boost::optional<std::string> relief;
        boost::optional<std::string> textColor;
        boost::optional<std::string> headerColor;
        boost::optional<std::string> borderColor;
        boost::optional<int> fontSize;
        boost::optional<int> borderWidth;

    protected:
        /**
         * Constructor
         * @param _type type of widget this is for
         */
        explicit WidgetBaseConfig(WidgetType _type);

    private slots:

        /**
         * Updates the members of this class based on the dialog
         */
        void onEdit();
    };
}

#endif //ROBOT_GUI_V3_WIDGETBASECONFIG_H
