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
      LogLevel_None    = -1,
      LogLevel_Error   = 0,
      LogLevel_Warning = 1,
      LogLevel_Info    = 2,
      LogLevel_All     = LogLevel_Info,
      LogLevel_Count   = 3,
    };

    /**
     * @brief Log information to the console.
     */
    flEXPORT void Log(flIN LogLevel logLevel, flIN const char * message, flIN const char *function = nullptr, flIN int64_t lineNumber = -1);

    /**
     * @brief Set the log level filter.
     */
    flEXPORT void SetLogLevel(flIN LogLevel logLevel);

    /**
     * @brief Get the active log level.
     */
    flEXPORT LogLevel GetLogLevel();
  }
}

/**
 * @brief Helper to add a log that includes the current function name an line.
 */
#define flLog(level, message) (level <= flEngine::Logging::GetLogLevel() ? flEngine::Logging::Log(level, message, __FUNCTION__, __LINE__) : void())

/**
 * @brief Helper to log some information that includes the current function name an line.
 */
#define flInfo(message) flLog(flEngine::Logging::LogLevel_Info, message)

/**
 * @brief Helper to log a warning that includes the current function name an line.
 */
#define flWarning(message) flLog(flEngine::Logging::LogLevel_Warning, message)

/**
 * @brief Helper to log an error that includes the current function name an line.
 */
#define flError(message) flLog(flEngine::Logging::LogLevel_Error, message)

/**
 * @brief Macro that pushes an error on a condition. Reports the function name and line number.
 */
#define flLogIf(condition, level, message) (condition ? (flLog(level, message), true) : false)

/**
 * @brief Macro that pushes an error on a condition. Reports the function name and line number.
 */
#define flInfoIf(condition, message) flLogIf( <= && (condition), message)

/**
 * @brief Macro that pushes an error on a condition. Reports the function name and line number.
 */
#define flWarningIf(condition, message) flLogIf(condition, flEngine::Logging::LogLevel_Warning, message)

/**
 * @brief Macro that pushes an error on a condition. Reports the function name and line number.
 */
#define flErrorIf(condition, message) flLogIf(condition, flEngine::Logging::LogLevel_Error, message)

#endif // flError_h__
