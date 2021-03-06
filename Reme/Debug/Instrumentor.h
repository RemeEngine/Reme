#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#include <Reme/Core/Core.h>

namespace Reme {

using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

struct ProfileResult {
    std::string name;

    FloatingPointMicroseconds start;
    std::chrono::microseconds elapsed_time;
    std::thread::id thread_id;
};

struct InstrumentationSession {
    std::string name;
};

class Instrumentor {
private:
    std::mutex m_mutex;
    InstrumentationSession* m_current_session;
    std::ofstream m_output_stream;

public:
    Instrumentor()
        : m_current_session(nullptr)
    {
    }

    void begin_session(const std::string& name, const std::string& filepath = "results.json")
    {
        std::lock_guard lock(m_mutex);
        if (m_current_session) {
            // If there is already a current session, then close it before beginning new one.
            // Subsequent profiling output meant for the original session will end up in the
            // newly opened session instead.  That's better than having badly formatted
            // profiling output.

            if (Logger::core_logger()) // Edge case: begin_session() might be before Logger::initialize()
                CORE_LOG_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_current_session->name);

            internal_end_session();
        }
        m_output_stream.open(filepath);

        if (m_output_stream.is_open()) {
            m_current_session = new InstrumentationSession({ name });
            write_header();
        } else {
            if (Logger::core_logger()) // Edge case: begin_session() might be before Logger::initialize()
                CORE_LOG_ERROR("Instrumentor could not open results file '{0}'.", filepath);
        }
    }

    void end_session()
    {
        std::lock_guard lock(m_mutex);
        internal_end_session();
    }

    void write_profile(const ProfileResult& result)
    {
        std::stringstream json;

        std::string name = result.name;
        std::replace(name.begin(), name.end(), '"', '\'');

        json << std::setprecision(3) << std::fixed;
        json << ",{";
        json << "\"cat\":\"function\",";
        json << "\"dur\":" << (result.elapsed_time.count()) << ',';
        json << "\"name\":\"" << name << "\",";
        json << "\"ph\":\"X\",";
        json << "\"pid\":0,";
        json << "\"tid\":" << std::hash<std::thread::id>()(result.thread_id) << ",";
        json << "\"ts\":" << result.start.count();
        json << "}";

        std::lock_guard lock(m_mutex);
        if (m_current_session) {
            m_output_stream << json.str();
            m_output_stream.flush();
        }
    }

    static Instrumentor& the()
    {
        static Instrumentor s_instance;
        return s_instance;
    }

private:
    void write_header()
    {
        m_output_stream << "{\"otherData\": {},\"traceEvents\":[{}";
        m_output_stream.flush();
    }

    void write_footer()
    {
        m_output_stream << "]}";
        m_output_stream.flush();
    }

    // Note: you must already own lock on m_mutex before
    // calling internal_end_session()
    void internal_end_session()
    {
        if (m_current_session) {
            write_footer();
            m_output_stream.close();

            delete m_current_session;
            m_current_session = nullptr;
        }
    }
};

class InstrumentationTimer {
public:
    InstrumentationTimer(const char* name)
        : m_name(name)
        , m_stopped(false)
    {
        m_start_timepoint = std::chrono::steady_clock::now();
    }

    ~InstrumentationTimer()
    {
        if (!m_stopped)
            stop();
    }

    void stop()
    {
        auto end_timepoint = std::chrono::steady_clock::now();
        auto high_res_start = FloatingPointMicroseconds { m_start_timepoint.time_since_epoch() };
        auto elapsed_time = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_start_timepoint).time_since_epoch();

        Instrumentor::the().write_profile({ m_name, high_res_start, elapsed_time, std::this_thread::get_id() });

        m_stopped = true;
    }

private:
    const char* m_name;
    std::chrono::time_point<std::chrono::steady_clock> m_start_timepoint;
    bool m_stopped;
};

} // namespace Reme

#ifdef REME_RUN_PROFILE
// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
#    if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#        define FUNC_SIG __PRETTY_FUNCTION__
#    elif defined(__DMC__) && (__DMC__ >= 0x810)
#        define FUNC_SIG __PRETTY_FUNCTION__
#    elif defined(__FUNCSIG__)
#        define FUNC_SIG __FUNCSIG__
#    elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#        define FUNC_SIG __FUNCTION__
#    elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#        define FUNC_SIG __FUNC__
#    elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#        define FUNC_SIG __func__
#    elif defined(__cplusplus) && (__cplusplus >= 201103)
#        define FUNC_SIG __func__
#    else
#        define FUNC_SIG "FUNC_SIG unknown!"
#    endif

#    define PROFILE_BEGIN_SESSION(name, filepath) ::Reme::Instrumentor::the().begin_session(name, filepath)
#    define PROFILE_END_SESSION() ::Reme::Instrumentor::the().end_session()
#    define PROFILE_SCOPE(name) ::Reme::InstrumentationTimer timer##__LINE__(name);
#    define PROFILE_FUNCTION() PROFILE_SCOPE(FUNC_SIG)
#else
#    define PROFILE_BEGIN_SESSION(name, filepath)
#    define PROFILE_END_SESSION()
#    define PROFILE_SCOPE(name)
#    define PROFILE_FUNCTION()
#endif
