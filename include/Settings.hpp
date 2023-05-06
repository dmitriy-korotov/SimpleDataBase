#pragma once
#ifndef SETTINGS_HPP
#define SETTINGS_HPP



#define _CRT_SECURE_NO_VARNINGS

// DEBUG
#define ON 1
#define OFF 0
#define DEBUG OFF

// WINDOW SETTINGS
#define WINDOW_WIDTH 120
#define WINDOW_HEIGHT 30

// FILE SETTINGS
#define BASE_DIR "res/DataBaseTables/"
#define FOLDER_WIDTH_TABLES "Tables/"

#define FILE_WITH_NAME_TABLES "names_of_tables.txt"
#define FILE_WITH_NAME_TABLEs_2 "names_of_tables_2.txt"

#define FILE_EXPANSION ".txt"

// LENGTH NAME SETTINGS
#define MAX_LENGTH_NAME_TABLE 120

// USING CONTAINER
#define VECTOR 0
#define MY_ARRAY 1
#define CONTAINER VECTOR

// BUFFER SETTINGS
#define BUFFER_SIZE 255

// ERRORS
#define TABLE_ERROR "ERROR: error working with table!"
#define DATABASE_ERROR "ERROR: error working with data base!"

// MEMORY CHECKING
#define MEMORY_CHECK OFF

// TABLE SETTINGS
#define WIDTH_COLUMN 20

#endif // !SETTINGS_HPP