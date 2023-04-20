/**
 * @file wifiLib.hpp
 * @author Benetton Alessandro (aleben98@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef WIFILIB_HPP
#define WIFILIB_HPP

/**
 * @brief Setup WiFi connection
 * 
 * @param restartOnFail Whether to restart the ESP if the connection fails
 * @return true If the connection is successful
 * @return false If the connection fails
 */
bool setupWifi(bool restartOnFail = true);

/**
 * @brief Get the Connection Status
 * 
 * @param reconnect Whether to reconnect if the connection is lost
 * @return true If the connection is successful
 * @return false If the connection fails
 */
bool getConnectionStatus(bool reconnect = false);

#endif