#pragma once
#include <string>

namespace Log {
    enum Level {
        INFO,
        SUCCESS,
        WARNING,
        ERRORL   // ERROR is keyword on some systems
    };

    void print(Level level, const std::string& msg);

    // Simple timer utility
    void startTimer(const std::string& label);
    void endTimer(const std::string& label);
}
