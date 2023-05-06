/**
 * @file loggerLib.hpp
 * @author Benetton Alessandro (aleben98@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LOGGERLIB_H
#define LOGGERLIB_H
void logInfo(const char *module, const char *message);
void logError(const char *module, const char *message);
void logWarning(const char *module, const char *message);
void logDebug(const char *module, const char *message);
void logVerbose(const char *module, const char *message);
void logInfof(const char *module, const char *fmt, ...);
void logErrorf(const char *module, const char *fmt, ...);
void logWarningf(const char *module, const char *fmt, ...);
void logDebugf(const char *module, const char *fmt, ...);
void logVerbosef(const char *module, const char *fmt, ...);
#endif