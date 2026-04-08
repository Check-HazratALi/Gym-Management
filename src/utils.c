#include "../include/utils.h"

extern Member members[];
extern Membership memberships[];
extern Attendance attendances[];
extern int memberCount;
extern int membershipCount;
extern int attendanceCount;

void clearScreen() {
    system(CLEAR_SCREEN);
}

void waitForEnter() {
    printf("\n\tPress Enter to continue...");
    getchar();
    getchar();
}

int generateId() {
    return rand() % 9000 + 1000;
}

void getCurrentDate(char* dateStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateStr, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void getCurrentDateTime(char* dateTimeStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateTimeStr, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void saveDataToFile() {
    // Create data directory if it doesn't exist
    system("mkdir data 2> nul");
    
    FILE* fp = fopen("data/members.dat", "wb");
    if(fp) {
        fwrite(&memberCount, sizeof(int), 1, fp);
        fwrite(members, sizeof(Member), memberCount, fp);
        fclose(fp);
    }
    
    fp = fopen("data/memberships.dat", "wb");
    if(fp) {
        fwrite(&membershipCount, sizeof(int), 1, fp);
        fwrite(memberships, sizeof(Membership), membershipCount, fp);
        fclose(fp);
    }
    
    fp = fopen("data/attendance.dat", "wb");
    if(fp) {
        fwrite(&attendanceCount, sizeof(int), 1, fp);
        fwrite(attendances, sizeof(Attendance), attendanceCount, fp);
        fclose(fp);
    }
}

void loadDataFromFile() {
    FILE* fp = fopen("data/members.dat", "rb");
    if(fp) {
        fread(&memberCount, sizeof(int), 1, fp);
        fread(members, sizeof(Member), memberCount, fp);
        fclose(fp);
    }
    
    fp = fopen("data/memberships.dat", "rb");
    if(fp) {
        fread(&membershipCount, sizeof(int), 1, fp);
        fread(memberships, sizeof(Membership), membershipCount, fp);
        fclose(fp);
    }
    
    fp = fopen("data/attendance.dat", "rb");
    if(fp) {
        fread(&attendanceCount, sizeof(int), 1, fp);
        fread(attendances, sizeof(Attendance), attendanceCount, fp);
        fclose(fp);
    }
}