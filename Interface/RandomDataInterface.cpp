#include "RandomDataInterface.h"

RandomDataInterface::RandomDataInterface(int _interval) : ThreadedInterface() {
    interval = _interval;
}

void RandomDataInterface::run() {
    double i = 0;
    double j = 0;

    while (isActive()) {
        setInt("KEY1", rand() % 10);
        setDouble("KEY2", (double) (rand() % 100) / 10);
        setString("KEY3", randomString(rand() % 10));
        setBool("KEY4", rand() % 2 == 1);

        setDouble("roll", i);
        setDouble("pitch", 10);
        setDouble("yaw", i);
        setDouble("altitude", float(i) / 80.0 - 10);
        setDouble("groundSpeed", 19.5);
        setDouble("verticalSpeed", (i / 15) - 10);
        setDouble("terrainAlt", (-i / 5) + 40);
        setDouble("j", j);
        setDouble("slowSweep", 1 - float(j) / 180.0);

        auto annunciatorData = std::make_shared<struct WidgetData::internalJSON>();
        annunciatorData->type = WidgetData::vector_t;
        for (int k = 0; k < 5; k++) {
            WidgetData::internalJSON_ptr a = std::make_shared<struct WidgetData::internalJSON>();
            a->type = WidgetData::vector_t;
            a->vector.push_back(WidgetData::getJSONObjectFromString(std::to_string(k) + " " + std::to_string(i)));
            a->vector.push_back(WidgetData::getJSONObjectFromInt(int(j / 20.0) % 3));
            a->vector.push_back(WidgetData::getJSONObjectFromString("Description"));
            annunciatorData->vector.push_back(a);
        }
        setJSON("annunciator", annunciatorData);
        setJSON("annunciator_2", annunciatorData);

        std::this_thread::sleep_for(std::chrono::milliseconds(interval));

        i += 3;
        if (i > 360) {
            i = 0;
        }

        j += 0.5;
        if (j > 360) {
            j = 0;
        }
    }
}

std::string RandomDataInterface::randomString(size_t length) {
    auto randChar = []() -> char {
        const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randChar);
    return str;
}
