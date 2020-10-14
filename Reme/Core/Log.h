#pragma once

#include <Reme/Core/Alias.h>
#include <spdlog/spdlog.h>

#include <spdlog/fmt/ostr.h>

namespace Reme {
class Log {
public:
    static void initialize(const char*);
    inline static const RefPtr<spdlog::logger>& core_logger() { return s_core_logger; }
    inline static const RefPtr<spdlog::logger>& logger() { return s_client_logger; }

private:
    static RefPtr<spdlog::logger> s_core_logger;
    static RefPtr<spdlog::logger> s_client_logger;
};
} // namespace Reme

// Log macros
#ifndef REME_DISABLE_LOGGING

#    define LOG_TRACE(...) ::Reme::Log::logger()->trace(__VA_ARGS__)
#    define LOG_INFO(...) ::Reme::Log::logger()->info(__VA_ARGS__)
#    define LOG_WARN(...) ::Reme::Log::logger()->warn(__VA_ARGS__)
#    define LOG_ERROR(...) ::Reme::Log::logger()->error(__VA_ARGS__)
#    define LOG_CRITICAL(...) ::Reme::Log::logger()->critical(__VA_ARGS__)

#    define CORE_LOG_TRACE(...) ::Reme::Log::core_logger()->trace(__VA_ARGS__)
#    define CORE_LOG_INFO(...) ::Reme::Log::core_logger()->info(__VA_ARGS__)
#    define CORE_LOG_WARN(...) ::Reme::Log::core_logger()->warn(__VA_ARGS__)
#    define CORE_LOG_ERROR(...) ::Reme::Log::core_logger()->error(__VA_ARGS__)
#    define CORE_LOG_CRITICAL(...) ::Reme::Log::core_logger()->critical(__VA_ARGS__)

#else

#    define LOG_TRACE(...)
#    define LOG_INFO(...)
#    define LOG_WARN(...)
#    define LOG_ERROR(...)
#    define LOG_CRITICAL(...)

#    define CORE_LOG_TRACE(...)
#    define CORE_LOG_INFO(...)
#    define CORE_LOG_WARN(...)
#    define CORE_LOG_ERROR(...)
#    define CORE_LOG_CRITICAL(...)

#endif
