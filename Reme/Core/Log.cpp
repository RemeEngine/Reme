#include <Reme/Core/Log.h>

#include <spdlog/spdlog-inl.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Reme
{
	RefPtr<spdlog::logger> Log::s_core_logger;
	RefPtr<spdlog::logger> Log::s_client_logger;

	void Log::init(const char* app_class_name)
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(make<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(make<spdlog::sinks::basic_file_sink_mt>("./RemeEngine.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_core_logger = std::make_shared<spdlog::logger>("RemeEngine", logSinks.begin(), logSinks.end());
		spdlog::register_logger(s_core_logger);
		s_core_logger->set_level(spdlog::level::trace);
		s_core_logger->flush_on(spdlog::level::trace);

		s_client_logger = std::make_shared<spdlog::logger>(app_class_name, logSinks.begin(), logSinks.end());
		spdlog::register_logger(s_client_logger);
		s_client_logger->set_level(spdlog::level::trace);
		s_client_logger->flush_on(spdlog::level::trace);
	}
}
