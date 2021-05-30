#ifndef fl_Logging_h__
#define fl_Logging_h__

#include "flConfig.h"

namespace flEngine
{
  namespace Logging
  {
    /**
     * @brief Different log levels. Higher values are lower severity.
     */
    enum LogLevel
    {
      LogLevel_None = -1,
      LogLevel_Failure = 0,
      LogLevel_Assert = 1,
      LogLevel_Error = 2,
      LogLevel_Warning = 3,
      LogLevel_Info = 4,
      LogLevel_All = LogLevel_Info,
      LogLevel_Count = 5,
    };

    /**
     * @brief Log information to the console.
     */
    flEXPORT void Log(flIN LogLevel logLevel, flIN char const *function, flIN int64_t lineNumber, flIN char const *messageFormat, ...);

    /**
     * @brief Log an assertion failure on a condition
     */
    flEXPORT void Assert(flIN bool condition, flIN char const *function, flIN int64_t lineNumber, flIN char const *messageFormat, ...);

    /**
     * @brief Log an assertion failure.
     */
    flEXPORT void Fail(flIN char const *function, flIN int64_t lineNumber, flIN char const *messageFormat, ...);

    /**
     * @brief Set the log level filter.
     */
    flEXPORT void SetLogLevel(flIN LogLevel logLevel);

    /**
     * @brief Get the active log level.
     */
    flEXPORT LogLevel GetLogLevel();
  }

  // template<typename T> std::string Repr(T const & o) {
  //   std::stringstream stream;
  //   stream << typeid(o).name() << std::hex << (uint64_t)&o;
  //   return stream.str();
  // }
}


/**
 * @brief Helper to add a log that includes the current function name an line.
 */
#define flLog(level, message, ...) (level <= flEngine::Logging::GetLogLevel() ? flEngine::Logging::Log(level, __FUNCTION__, __LINE__, message, __VA_ARGS__) : void())

/**
 * @brief Helper to log some information that includes the current function name an line.
 */
#define flInfo(message, ...) flLog(flEngine::Logging::LogLevel_Info, message, __VA_ARGS__)

/**
 * @brief Helper to log a warning that includes the current function name an line.
 */
#define flWarning(message, ...) flLog(flEngine::Logging::LogLevel_Warning, message, __VA_ARGS__)

/**
 * @brief Helper to log an error that includes the current function name an line.
 */
#define flError(message, ...) flLog(flEngine::Logging::LogLevel_Error, message, __VA_ARGS__)

/**
 * @brief Macro that pushes an error on a condition. Reports the function name and line number.
 */
#define flLogIf(condition, level, message, ...) (condition ? (flLog(level, message, __VA_ARGS__), true) : false)

/**
 * @brief Macro that pushes an error on a condition. Reports the function name and line number.
 */
#define flInfoIf(condition, message, ...) flLogIf( <= && (condition), message, __VA_ARGS__)

/**
 * @brief Macro that pushes an error on a condition. Reports the function name and line number.
 */
#define flWarningIf(condition, message, ...) flLogIf(condition, flEngine::Logging::LogLevel_Warning, message, __VA_ARGS__)

/**
 * @brief Macro that pushes an error on a condition. Reports the function name and line number.
 */
#define flErrorIf(condition, message, ...) flLogIf(condition, flEngine::Logging::LogLevel_Error, message, __VA_ARGS__)

 /**
  * @brief A helper macro that asserts logs a failure message with the function name and line number
 *
 * This function causes a debug break if the condition fails.
 */
#define flAssert(condition, message, ...) flEngine::Logging::Assert(condition, __FUNCTION__, __LINE__, message, __VA_ARGS__)

 /**
  * @brief A helper macro that asserts logs a failure message with the function name and line number.
  *
  * This function causes a debug break.
  */
#define flFail(message, ...) flEngine::Logging::Fail(message, __FUNCTION__, __LINE__, , __VA_ARGS__)

#endif // flError_h__
