#include <iostream>
#include <string>
#include <memory>

// Define log levels
enum LogLevel { INFO = 1, DEBUG = 2, ERROR = 3 };

// Abstract Handler
class Logger {
protected:
    std::shared_ptr<Logger> nextLogger;
    LogLevel level;

public:
    Logger(LogLevel level) : level(level), nextLogger(nullptr) {}
    
    void setNext(std::shared_ptr<Logger> next) {
        nextLogger = next;
    }

    void logMessage(LogLevel msgLevel, const std::string& message) {
        if (this->level <= msgLevel) {
            write(message);
        }
        if (nextLogger) {
            nextLogger->logMessage(msgLevel, message);
        }
    }

    virtual void write(const std::string& message) = 0;
};

// Concrete Handlers
class InfoLogger : public Logger {
public:
    InfoLogger(LogLevel level) : Logger(level) {}
    void write(const std::string& message) override {
        std::cout << "[INFO]: " << message << std::endl;
    }
};

class ErrorLogger : public Logger {
public:
    ErrorLogger(LogLevel level) : Logger(level) {}
    void write(const std::string& message) override {
        std::cerr << "[ERROR]: " << message << std::endl;
    }
};

// Client code
int main() {
    auto info = std::make_shared<InfoLogger>(INFO);
    auto error = std::make_shared<ErrorLogger>(ERROR);

    // Form the chain: Error -> Info
    error->setNext(info);

    error->logMessage(INFO, "System started.");
    error->logMessage(ERROR, "Critical failure detected!");

    return 0;
}
