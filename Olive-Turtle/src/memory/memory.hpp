/**
 * @file memory.hpp
 * @author Benetton Alessandro (aleben98@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__
void memoryInit();
void createDir(const char * path);
void removeDir(const char * path);
const char * readFile(const char * path);
void writeFile(const char * path, const char * message);
void appendFile(const char * path, const char * message);
void deleteFile(const char * path);
bool pathExists(const char * path);
#endif