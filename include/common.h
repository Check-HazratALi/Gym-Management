#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

// Global constants
#define MAX_MEMBERS 100
#define MAX_MEMBERSHIPS 100
#define MAX_ATTENDANCE 500
#define MAX_NAME 50
#define MAX_EMAIL 100
#define MAX_PHONE 15
#define MAX_ADDRESS 100
#define MAX_DATE 20
#define MAX_TYPE 20
#define MAX_STATUS 20

// Structure definitions
typedef struct {
    int id;
    char name[MAX_NAME];
    char email[MAX_EMAIL];
    char phone[MAX_PHONE];
    char address[MAX_ADDRESS];
    int age;
    char gender[10];
    char joinDate[MAX_DATE];
    int isActive;
} Member;

typedef struct {
    int id;
    int memberId;
    char type[MAX_TYPE];
    float amount;
    char startDate[MAX_DATE];
    char endDate[MAX_DATE];
    char paymentStatus[MAX_STATUS];
} Membership;

typedef struct {
    int id;
    int memberId;
    char checkInTime[MAX_DATE];
    char checkOutTime[MAX_DATE];
    char date[MAX_DATE];
} Attendance;

typedef struct {
    char username[50];
    char password[50];
} User;

// Global variables
extern Member members[MAX_MEMBERS];
extern Membership memberships[MAX_MEMBERSHIPS];
extern Attendance attendances[MAX_ATTENDANCE];
extern User admin;

extern int memberCount;
extern int membershipCount;
extern int attendanceCount;

#endif