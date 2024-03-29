#ifndef ROBOT_GUI_V3_WIDGETBASECONFIG_H
#define ROBOT_GUI_V3_WIDGETBASECONFIG_H

#include "boost/optional.hpp"
#include "../../RobotGui.h"
#include "../../../lib/rapidxml/rapidxml.hpp"
#include "QObject"
#include "QDialog"
#include "QDialog"
#include "QPushButton"
#include "QCheckBox"
#include "QLineEdit"
#include "WidgetSettingsDialog.h"
#include "set"

namespace RobotGui {
    class WidgetSettingsDialog;

    namespace WidgetConstants {
        enum Type : int;
        enum Attribute : int;
    }
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

        ~WidgetBaseConfig();

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

        /**
         * Virtual function to be used for parsing additional xml information
         * @param node xml node to parse
         */
        virtual void parseXml(rapidxml::xml_node<> *node);

        /**
         * Saves any configuration data to a xml node
         * @param node node to output to
         * @param doc xml document to allocate in
         */
        virtual void outputXML(rapidxml::xml_node<> *node, rapidxml::xml_document<> *doc);

        void set(WidgetConstants::Attribute attr, bool val);

        void set(WidgetConstants::Attribute attr, int val);

        void set(WidgetConstants::Attribute attr, double val);

        void set(WidgetConstants::Attribute attr, std::string val);

        void require(WidgetConstants::Attribute attr);

        void require(WidgetConstants::Attribute attr, int def);

        void require(WidgetConstants::Attribute attr, double def);

        void require(WidgetConstants::Attribute attr, const std::string &def);

        bool isRequired(WidgetConstants::Attribute attr);

        /**
         * Members
         */
        // Required members
        WidgetConstants::Type type;
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

    signals:

        void configChanged();

    public slots:

        /**
         * Shows a menu in which to edit this config
         */
        void showEditMenu();

    protected:

        /**
         * Constructor
         * @param _type type of widget this is for
         */
        explicit WidgetBaseConfig(WidgetConstants::Type _type);

        virtual void customCreateDialog(WidgetSettingsDialog *dialog);

    private:
        void require(WidgetConstants::Attribute attr, bool defBool, int defInt, double defDouble, const std::string& defString, const std::string &defStyle);

        void set(WidgetConstants::Attribute attr, bool boolVal, int intVal, double doubleVal, std::string strVal, std::string defStyle, bool overwrite=true);

        void createDialog(WidgetSettingsDialog *dialog);

        std::set<WidgetConstants::Attribute> requiredAttributes;



    };
}

#endif //ROBOT_GUI_V3_WIDGETBASECONFIG_H
