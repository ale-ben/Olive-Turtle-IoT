/**
 * @file wifiLib.cpp
 * @author Benetton Alessandro (aleben98@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../wifiLib.hpp"
#include "../loggerLib.hpp"

#include <WiFiManager.h> 
#include <Arduino.h>


WiFiManager wifiManager;

bool setupWifi(bool restartOnFail) {
	wifiManager.setConfigPortalTimeout(5*60); // Wait 5 minutes for connection
	wifiManager.setClass("invert"); // dark theme
	
	bool res = wifiManager.autoConnect("AutoConnectAP");

	 if(!res) {
        logError("Failed to connect to WiFi. Restarting...");
		if (restartOnFail) ESP.restart();
		return false;
    } 
    else {  
        logInfo("connected...yeey :)");
		return true;
    }
}

bool getConnectionStatus(bool reconnect) {
	bool status = WiFi.status() == WL_CONNECTED;
	if (!status && reconnect) {
		status = setupWifi();
	}
	return status;
}