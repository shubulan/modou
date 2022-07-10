#pragma once

#include <spdlog/spdlog.h>

#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_sinks.h"

namespace modou {

inline std::shared_ptr<spdlog::logger> createLogger() {
  auto console = spdlog::stdout_logger_mt("modou");
  console->set_pattern("[%H:%M:%S:%e] [%t] [%l] %v");
  return console;
}

inline std::shared_ptr<spdlog::logger> getModouLogger() {
  static auto console = createLogger();
  return console;
}

template <typename... Args>
inline void trace(spdlog::format_string_t<Args...> fmt, Args&&... args) {
  getModouLogger()->trace(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void debug(spdlog::format_string_t<Args...> fmt, Args&&... args) {
  getModouLogger()->debug(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void info(spdlog::format_string_t<Args...> fmt, Args&&... args) {
  getModouLogger()->info(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void warn(spdlog::format_string_t<Args...> fmt, Args&&... args) {
  getModouLogger()->warn(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void error(spdlog::format_string_t<Args...> fmt, Args&&... args) {
  getModouLogger()->error(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void critical(spdlog::format_string_t<Args...> fmt, Args&&... args) {
  getModouLogger()->critical(fmt, std::forward<Args>(args)...);
}

}  // namespace modou
