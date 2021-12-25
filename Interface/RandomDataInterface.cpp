#include "RandomDataInterface.h"

RandomDataInterface::RandomDataInterface(int _interval) : ThreadedInterface() {
    interval = _interval;
}

void RandomDataInterface::run() {
    while (isActive()) {
        setInt("KEY1", rand() % 10);
        setDouble("KEY2", (double)(rand() % 100) / 10);
        setString("KEY3", randomString(rand() % 10));
        setBool("KEY4", rand() % 2 == 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}

std::string RandomDataInterface::randomString(size_t length) {
    auto randChar = []() -> char {
        const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n(str.begin(), length, randChar );
    return str;
}
