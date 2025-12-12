#include "logger.hpp"
#include <iostream>
#include <chrono>
#include <unordered_map>

namespace {
    std::string levelToString(Log::Level level) {
        switch (level) {
            case Log::INFO:    return "[INF]    ";
            case Log::SUCCESS: return "[SUCCESS]";
            case Log::WARNING: return "[WRN]    ";
            case Log::ERRORL:  return "[ERR]    ";
        }
        return "";
    }

    // Stores timers by label
    std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> timers;
}

namespace Log {

void print(Level level, const std::string& msg) {
    using namespace std::chrono;

    auto now = system_clock::now();
    auto t = system_clock::to_time_t(now);

    // Timestamp (YYYY-MM-DD HH:MM:SS)
    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);

    std::cout << buffer << " " << levelToString(level) << " " << msg << "\n";
}

void startTimer(const std::string& label) {
    timers[label] = std::chrono::high_resolution_clock::now();
}

void endTimer(const std::string& label) {
    using namespace std::chrono;

    if (timers.find(label) == timers.end()) {
        print(WARNING, "Timer '" + label + "' was not started.");
        return;
    }

    auto end = high_resolution_clock::now();
    auto start = timers[label];
    auto duration = duration_cast<milliseconds>(end - start).count();

    print(INFO, label + " took " + std::to_string(duration) + " ms");
    timers.erase(label);
}

}
