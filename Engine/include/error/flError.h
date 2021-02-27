#ifndef fl_Error_h__
#define fl_Error_h__

#include "../flConfig.h"

namespace flEngine
{
  namespace Error
  {
    /**
     * @brief Error codes that may be reported by the library
     */
    enum Code
    {
      Code_Failure,
      Code_BadArgs,
      Code_Success,
      Code_Count,
    };

    /**
     * @brief Push an error to the stack.
     */
    flEXPORT void Push(flIN Code code, flIN const char *info, flIN const char *function = nullptr, flIN int64_t lineNumber = -1);

    /**
     * @brief Get the last error code reported.
     */
    flEXPORT Code GetLast();

    /**
     * @brief Get extended information for the last error.
     */
    flEXPORT const char* GetInfo();

    /**
     * @brief Get the function reported with the last error.
     */
    flEXPORT const char* GetFunction();

    /**
     * @brief Get the line number reported with the last error.
     */
    flEXPORT int64_t GetLine();

    /**
     * @brief Get the number of errors reported
     */
    flEXPORT int64_t GetErrorCount();

    /**
     * @brief Returns true if there are any unprocessed errors.
     */
    flEXPORT bool HasErrors();

    /**
     * @broef Clear the error stack
     */
    flEXPORT void Clear();
  }
}

/**
 * @brief Helper to push an error that includes the current function name an line
 */
#define flPushError(code, info) flEngine::Error::Push(code, info, __FUNCTION__, __LINE__)

/**
 * @brief Macro that pushes an error on a condition. Reports the function name and line number.
 */
#define flErrorIf(condition, code, info) (condition ? (flPushError(code, info), true) : false)

#endif // flError_h__
