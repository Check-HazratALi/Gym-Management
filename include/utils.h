#ifndef UTILS_H
#define UTILS_H

#include "common.h"

// Utility functions
void clearScreen(void);
void waitForEnter(void);
int generateId(void);
void getCurrentDate(char* dateStr);
void getCurrentDateTime(char* dateTimeStr);
void maskPassword(char* password);
void saveDataToFile(void);
void loadDataFromFile(void);

// Auth functions
void displayWelcomeScreen(void);
void displayLoginScreen(void);
void displayMainMenu(void);
int authenticateUser(char* username, char* password);

#endif