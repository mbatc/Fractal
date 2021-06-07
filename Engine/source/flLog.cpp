#include "flLog.h"
#include "ctThreading.h"
#include "ctString.h"
#include "ctDateTime.h"

#define _CRT_SECURE_NO_WARNINGS

namespace flEngine
{
  namespace Logging
  {
    static ctString _logLevelName[LogLevel_Count]
    {
      "Failure",
      "Assert ",
      "Error  ",
      "Warning",
      "Info   "
    };

    static LogLevel _logLevel = LogLevel_All;

    void LogV(flIN LogLevel code, flIN const char *function, flIN int64_t lineNumber, flIN const char *messageFormat, va_list args)
    {
      if (_logLevel < code)
        return;

      char timeBuff[100];
      time_t now = time(0);

#ifdef flPLATFORM_WINDOWS
      tm t; // Safe version on windows
      localtime_s(&t, &now);
      strftime(timeBuff, 100, "%H:%M:%S.00", &t);
#else
      strftime(timeBuff, 100, "%H:%M:%S.00", localtime(&now));
#endif

      // Print prefix
      printf("[%s] %s | ",
        timeBuff,
        _logLevelName[code].c_str()
      );

      // Print message
      vprintf(messageFormat, args);

      // Print suffix
      printf(" (%s:%lld)\n",
        function,
        lineNumber
      );
    }

    void Log(flIN LogLevel code, flIN const char* function, flIN int64_t lineNumber, flIN const char *messageFormat, ...)
    {
      va_list argList;
      va_start(argList, messageFormat);
      LogV(code, function, lineNumber, messageFormat, argList);
      va_end(argList);
    }

    void Assert(flIN bool condition, flIN char const *function, flIN int64_t lineNumber, flIN char const *messageFormat, ...)
    {
      if (condition)
      {
        va_list argList;
        va_start(argList, messageFormat);
        LogV(LogLevel_Failure, function, lineNumber, messageFormat, argList);
        va_end(argList);
        __debugbreak();
      }
    }

    void Fail(flIN char const *function, flIN int64_t lineNumber, flIN char const *messageFormat, ...)
    {
      va_list argList;
      va_start(argList, messageFormat);
      LogV(LogLevel_Assert, function, lineNumber, messageFormat, argList);
      va_end(argList);
      __debugbreak();
    }

    void SetLogLevel(flIN LogLevel logLevel)
    {
      _logLevel = logLevel;
    }

    LogLevel GetLogLevel()
    {
      return _logLevel;
    }
  }
}
