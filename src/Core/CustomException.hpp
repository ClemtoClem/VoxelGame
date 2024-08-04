#ifndef CUSTOM_EXCEPTION_HPP
#define CUSTOM_EXCEPTION_HPP

#include <exception>
#include <string>
#include <sstream>
#include <ctime>
#include <functional>
#include <memory>
#include "Logger.hpp"

class CustomException : public std::exception {
    mutable LogLevel _level;
    mutable std::string _message;
    std::string _file;
    int _line;
    std::string _timestamp;

public:
    CustomException(LogLevel level, const std::string& message, const std::string& file, int line)
        : _level(level), _message(message), _file(file), _line(line) {
        // Get current time
        std::time_t now = std::time(nullptr);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        _timestamp = std::string(buf);
    }

    virtual const char* what() const noexcept override {
        std::ostringstream oss;
        oss << _timestamp << " - " << _file << ":" << _line << " - " << _message;
        return oss.str().c_str();
    }

    LogLevel getLevel() const noexcept {
        return _level;
    }

    const std::string& getMessage() const noexcept {
        return _message;
    }

    const std::string& getFile() const noexcept {
        return _file;
    }

    int getLine() const noexcept {
        return _line;
    }

    const std::string& getTimestamp() const noexcept {
        return _timestamp;
    }

    void generateLog() const {
        LOG(_level) << _timestamp << " - " << _file << ":" << _line << " - " << _message;
    }
};

// Macro to throw CustomException with file and line information
#define THROW_CUSTOM_EXCEPTION(loglevel, flux) { \
    std::ostringstream oss; \
    oss << flux; \
    throw CustomException(loglevel, oss.str(), __FILE__, __LINE__); \
}

#endif // CUSTOM_EXCEPTION_HPP
