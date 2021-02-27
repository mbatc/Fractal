#include "error/flError.h"
#include "ctThreading.h"
#include "ctString.h"

using namespace flEngine::Error;

static const int64_t _maxErrors = 256;
static int64_t _errBegin = 0;
static int64_t _errEnd = 0;
static int64_t _count = 0;
static std::mutex _errLock;

struct ErrorReport
{
  Code code;
  ctString info;
  ctString function;
  int64_t line;
};

ErrorReport _lastError;
ErrorReport _errors[_maxErrors];

flEXPORT void flEngine::Error::Push(flIN Code code, flIN const char *info, flIN const char *function, flIN int64_t lineNumber)
{
  ErrorReport report;
  report.code = code;
  report.info = info;
  report.function = function;
  report.line = lineNumber;

  ctScopeLock lock(_errLock);
  _errors[_errEnd++] = std::move(report);
  _errEnd = _errEnd % _maxErrors;
  if (_errEnd == _errBegin)
    ++_errBegin;
  else
    ++_count;
}

flEXPORT Code flEngine::Error::GetLast()
{
  ctScopeLock lock(_errLock);
  if (_count > 0)
  {
    _lastError = _errors[_errEnd--];
    _errEnd = (_errEnd + _maxErrors) % _maxErrors;
    _count--;
  }
  else
  {
    _lastError = ErrorReport();
  }
}

flEXPORT const char* flEngine::Error::GetInfo()
{
  ctScopeLock lock(_errLock);
  return _lastError.info;
}

flEXPORT const char* flEngine::Error::GetFunction()
{
  ctScopeLock lock(_errLock);
  return _lastError.function;
}

flEXPORT int64_t flEngine::Error::GetLine()
{
  ctScopeLock lock(_errLock);
  return _lastError.line;
}

flEXPORT int64_t flEngine::Error::GetErrorCount()
{
  ctScopeLock lock(_errLock);
  return _count;
}

flEXPORT bool flEngine::Error::HasErrors()
{
  ctScopeLock lock(_errLock);
  return GetErrorCount() > 0;
}

flEXPORT void flEngine::Error::Clear()
{
  ctScopeLock lock(_errLock);
  _count = 0;
  _lastError = ErrorReport();
  _errEnd = _errBegin;
}
