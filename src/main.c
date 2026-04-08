#include "../include/common.h"
#include "../include/member.h"
#include "../include/membership.h"
#include "../include/attendance.h"
#include "../include/reports.h"
#include "../include/utils.h"

// Initialize global variables
Member members[MAX_MEMBERS];
Membership memberships[MAX_MEMBERSHIPS];
Attendance attendances[MAX_ATTENDANCE];
User admin = {"admin", "admin123"};

int memberCount = 0;
int membershipCount = 0;
int attendanceCount = 0;

int main() {
    SetConsoleOutputCP(65001);
    loadDataFromFile();
    
    while(1) {
        displayWelcomeScreen();
        displayLoginScreen();
        
        int choice;
        while(1) {
            displayMainMenu();
            printf("\n\tEnter your choice: ");
            scanf("%d", &choice);
            
            switch(choice) {
                case 1:
                    memberManagement();
                    break;
                case 2:
                    membershipOperation();
                    break;
                case 3:
                    dailyOperation();
                    break;
                case 4:
                    reportsAnalytics();
                    break;
                case 5:
                    saveDataToFile();
                    printf("\n\tThank you for using Gym Management System!\n");
                    printf("\tSaving data... Goodbye!\n");
                    exit(0);
                default:
                    printf("\n\tInvalid choice! Please try again.\n");
                    waitForEnter();
            }
        }
    }
    return 0;
}