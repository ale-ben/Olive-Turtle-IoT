/**
 * @file loggerLib.cpp
 * @author Benetton Alessandro (aleben98@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-15
 *
 * @copyright Copyright (c) 2023
 *
 */


#include "../timeLib.hpp"
#include "../loggerLib.hpp"

#include <Arduino.h>

void logMessage(const char *message, const char* level) {
	const int msgLen = strlen(message);
	const int levelLen = strlen(level);

	// Get timestamp
	char* timestamp;
	#ifdef TIMELIB_H
	timestamp = getTimestamp();
	#else
	timestamp = (char*)malloc(1);
	strcpy(timestamp, "\0");
	#endif

	const int timestampLen = strlen(timestamp);

	// Allocate memory for the message
	char* logMessage = (char*)malloc((msgLen + levelLen + timestampLen + 2) * sizeof(char));

	// Build the message as follows: [timestamp][level] [message]\0
	strcpy(logMessage, timestamp);
	strcat(logMessage, level);
	strcat(logMessage, " ");
	strcat(logMessage, message);
	strcat(logMessage, "\n\0");

	// Print the message
	Serial.print(logMessage);

	// Free memory
	free(timestamp);
	free(logMessage);
}

void logInfo(const char *message) {
	logMessage(message, "[I]");
}

void logError(const char *message){
	logMessage(message, "[E]");
}

void logWarning(const char *message){
	logMessage(message, "[W]");
}

void logDebug(const char *message){
	logMessage(message, "[D]");
}

void logVerbose(const char *message){
	logMessage(message, "[V]");
}