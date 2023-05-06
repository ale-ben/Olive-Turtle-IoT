/**
 * @file memory.cpp
 * @author Benetton Alessandro (aleben98@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <Arduino.h>
#include "FS.h"
#include <LittleFS.h>

#include "../memory.hpp"
#include "../../utilities/stringConverter.hpp"
#include "../../utilities/loggerLib.hpp"

#define FORMAT_LITTLEFS_IF_FAILED true

void createDir(const char * path){
	logDebugf("MEM", "Creating Dir: %s\n", path);
	if(LittleFS.mkdir(path)) logDebug("MEM", "Dir created");
	else logWarning("MEM", "mkdir failed");

}

void removeDir(const char * path){
	logDebugf("MEM", "Removing Dir: %s\n", path);
	if(LittleFS.rmdir(path)) logDebug("MEM", "Dir removed");
	else logWarning("MEM", "rmdir failed");

}

const char * readFile(const char * path){
	logDebugf("MEM", "Reading file: %s\n", path);
	File file = LittleFS.open(path);
	if(!file || file.isDirectory()) {
		logWarning("MEM", "Failed to open file for reading");
		return NULL;
	}

	String fileContent = file.readString();
	return stringToConstCharArr(fileContent);
}

void writeFile(const char * path, const char * message){
	logDebugf("MEM", "Writing file: %s\n", path);

	File file = LittleFS.open(path, FILE_WRITE);
	if(!file) {
		logWarning("MEM", "Failed to open file for writing");
		return;
	}

	if(file.print(message)) logDebug("MEM", "File written");
	else logWarning("MEM", "Write failed");

	file.close();
}

void appendFile(const char * path, const char * message){
	logDebugf("MEM", "Appending to file: %s\n", path);

	File file = LittleFS.open(path, FILE_APPEND);
	if(!file) {
		logWarning("MEM", "Failed to open file for appending");
		return;
	}
	if(file.print(message)) logDebug("MEM", "- message appended");
	else logWarning("MEM", "- append failed");

	file.close();
}

void deleteFile(const char * path){
	logDebugf("MEM", "Deleting file: %s\n", path);
	
	if(LittleFS.remove(path)) logDebug("MEM", "- file deleted");
	else logWarning("MEM", "- delete failed");
}

bool pathExists(const char * path){
	return LittleFS.exists(path);
}

void memoryInit(){
	if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
		logWarning("MEM", "LittleFS Mount Failed");
		return;
	}
}


/* Unused functions
   void listDir(const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
   }

   void renameFile(const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\r\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("- file renamed");
    } else {
        Serial.println("- rename failed");
    }
   }

 */