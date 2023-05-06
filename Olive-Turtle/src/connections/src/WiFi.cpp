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


#include "Arduino.h"
#include "WiFi.h"
#include <WiFiMulti.h>

#include "../WiFi.hpp"
#include "../../utilities/loggerLib.hpp"
#include "../secrets.hpp"



bool wifiSetup(bool rebootOnFail){

}

bool wifiStatus(bool reconnect) {
	bool status = WiFi.status() == WL_CONNECTED;
	if (!status && reconnect) {
		status = wifiSetup(false);
	}
	return status;
}