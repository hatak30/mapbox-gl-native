#include <mbgl/platform/log.hpp>
#include <mbgl/util/enum.hpp>

#include <cstdio>
#include <cstdarg>
#include <sstream>

namespace mbgl {

namespace {

static std::unique_ptr<Log::Observer> currentObserver;

} // namespace

void Log::setObserver(std::unique_ptr<Observer> observer) {
    currentObserver = std::move(observer);
}

std::unique_ptr<Log::Observer> Log::removeObserver() {
    std::unique_ptr<Observer> observer;
    std::swap(observer, currentObserver);
    return observer;
}

void Log::record(EventSeverity severity, Event event, const std::string &msg) {
    record(severity, event, -1, msg);
}

void Log::record(EventSeverity severity, Event event, const char* format, ...) {
    va_list args;
    va_start(args, format);
    char msg[4096];
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    record(severity, event, -1, msg);
}

void Log::record(EventSeverity severity, Event event, int64_t code) {
    record(severity, event, code, std::string());
}

void Log::record(EventSeverity severity, Event event, int64_t code, const std::string &msg) {
    if (currentObserver && severity != EventSeverity::Debug &&
        currentObserver->onRecord(severity, event, code, msg)) {
        return;
    }

    std::stringstream logStream;

#if defined(__APPLE__)
    char name[32];
    pthread_getname_np(pthread_self(), name, sizeof(name));
    logStream << "{" << name << "}";
#elif defined(__GLIBC__) && defined(__GLIBC_PREREQ)
#if __GLIBC_PREREQ(2, 12)
    char name[32];
    pthread_getname_np(pthread_self(), name, sizeof(name));
    logStream << "{" << name << "}";
#endif
#endif

    logStream << "[" << Enum<Event>::toString(event) << "]";

    if (code >= 0) {
        logStream << "(" << code << ")";
    }

    if (!msg.empty()) {
        logStream << ": " << msg;
    }

    platformRecord(severity, logStream.str());
}

} // namespace mbgl
