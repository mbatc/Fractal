#include "flLog.h"
#include "ctThreading.h"
#include "ctString.h"
#include "ctDateTime.h"

namespace flEngine
{
  namespace Logging
  {
    static ctString _logLevelName[LogLevel_Count]
    {
      "Error  ",
      "Warning",
      "Info   "
    };

    static LogLevel _logLevel = LogLevel_All;

    void Log(flIN LogLevel code, flIN const char* message, flIN const char* function, flIN int64_t lineNumber)
    {
      if (_logLevel < code)
        return;

      char timeBuff[100];
      time_t now = time(0);
      strftime(timeBuff, 100, "%H:%M:%S.00", localtime(&now));

      printf("[%s] %s | %s (%s:%lld)\n",
        timeBuff,
        _logLevelName[code].c_str(),
        message,
        function,
        lineNumber
      );

      if (code == LogLevel_Error)
        ctFail(message);
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
