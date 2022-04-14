#include "RandomDataInterface.h"
#include "../CustomJSONStructure.h"
#include "ThreadedInterface.h"

RobotGui::RandomDataInterface::RandomDataInterface(int _interval) : ThreadedInterface() {
    interval = _interval;
}

void RobotGui::RandomDataInterface::run() {
    double i = 0;
    double j = 0;

    ConsoleJSONStruct console(10);
    DropDownTextBoxJSONStruct dropDown;

    double lastThing = 0;
    bool sign = false;

    while (isActive()) {
        if (rand() % 1000 < 20) {
            sign = !sign;
        }
        lastThing += ((rand() % 100) / 35) * (sign ? -1 : 1);
        setDouble("KEY5", lastThing);


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
        setString("missionStatus", "In Mission");
        setDouble("batteryVoltage", rand());
        setDouble("current", i);

        //Lets make a lot of keys for testing
        int max_letters = 5;
        int lines_to_add = 50;
        for (int k = 0; k < lines_to_add; k++) {
            std::string key;
            for (int l = 0; l < k % max_letters; l++) {
                char letter = int(k / max_letters) + 97;
                key += letter;
            }
            setDouble(key, i + k);
        }

        AnnunciatorJSONStruct annunciator;
        for (int k = 0; k < 5; k++) {
            annunciator.addAnnunciator(std::to_string(k) + " " + std::to_string(i), int((j / 20.0) + k) % 4, "description");
        }

        setMap("annunciator", annunciator.getStruct());
        setMap("annunciator_2", annunciator.getStruct());

        console.addLog("AAA " + std::to_string(j), int(j / 20.0) % 3);
        setMap("testarray", console.getStruct());


        setBool("allowedToArm", i >= 100);
        setBool("armed", i >= 200);
        setInt("status", int((float(i) / 360.0) * 3));

        dropDown.addLine("test1", "aaa", "bbb", 0);
        dropDown.addLine("test1", "ccc", "ddd", 1);
        dropDown.addLine("test2", "test", std::to_string(i), 0);
        dropDown.addLine("test2", "test1aaaa", "bbb" + std::to_string(i), 1);
        dropDown.addLine("test2", "t2", "aaa" + std::to_string(i), 2);
        dropDown.addLine("test2", "test3", std::to_string(i), 3);
        setMap("diagnostics_agg", dropDown.getStruct());

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

std::string RobotGui::RandomDataInterface::randomString(size_t length) {
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
