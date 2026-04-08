#include "../include/attendance.h"
#include "../include/utils.h"

extern Member members[];
extern Attendance attendances[];
extern int memberCount;
extern int attendanceCount;

void dailyOperation() {
    int choice;
    
    while(1) {
        clearScreen();
        printf("\n\n");
        printf("\t╔══════════════════════════════════════════════════════════════╗\n");
        printf("\t║                     DAILY OPERATION                          ║\n");
        printf("\t╠══════════════════════════════════════════════════════════════╣\n");
        printf("\t║              1. Member Check-In                              ║\n");
        printf("\t║              2. Member Check-Out                             ║\n");
        printf("\t║              3. View Today's Attendance                      ║\n");
        printf("\t║              4. Back to Main Menu                            ║\n");
        printf("\t╚══════════════════════════════════════════════════════════════╝\n");
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: checkIn(); break;
            case 2: checkOut(); break;
            case 3: viewTodayAttendance(); break;
            case 4: return;
            default:
                printf("\n\tInvalid choice! Please try again.\n");
                waitForEnter();
        }
    }
}

void checkIn() {
    int memberId, found = 0;
    
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                      MEMBER CHECK-IN                         ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("\tEnter Member ID: ");
    scanf("%d", &memberId);
    
    for(int i = 0; i < memberCount; i++) {
        if(members[i].id == memberId && members[i].isActive) {
            found = 1;
            
            Attendance newAttendance;
            newAttendance.id = generateId();
            newAttendance.memberId = memberId;
            getCurrentDate(newAttendance.date);
            getCurrentDateTime(newAttendance.checkInTime);
            strcpy(newAttendance.checkOutTime, "Not checked out");
            
            attendances[attendanceCount++] = newAttendance;
            
            printf("\n\t✓ Member %s checked in successfully at %s\n", 
                   members[i].name, newAttendance.checkInTime);
            break;
        }
    }
    
    if(!found) printf("\n\t✗ Member not found or inactive!\n");
    waitForEnter();
}

void checkOut() {
    int memberId, found = 0;
    
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                      MEMBER CHECK-OUT                        ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("\tEnter Member ID: ");
    scanf("%d", &memberId);
    
    char today[20];
    getCurrentDate(today);
    
    for(int i = attendanceCount - 1; i >= 0; i--) {
        if(attendances[i].memberId == memberId && 
           strcmp(attendances[i].date, today) == 0 &&
           strcmp(attendances[i].checkOutTime, "Not checked out") == 0) {
            found = 1;
            getCurrentDateTime(attendances[i].checkOutTime);
            printf("\n\t✓ Member checked out successfully at %s\n", attendances[i].checkOutTime);
            break;
        }
    }
    
    if(!found) printf("\n\t✗ No active check-in found for this member today!\n");
    waitForEnter();
}

void viewTodayAttendance() {
    char today[20];
    getCurrentDate(today);
    
    clearScreen();
    printf("\n\n");
    printf("\t╔═══════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("\t║                             TODAY'S ATTENDANCE (%s)                            ║\n", today);
    printf("\t╠═══════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("\t║ Member ID │ Member Name           │ Check-In Time      │ Check-Out Time              ║\n");
    printf("\t╠═══════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    int todayCount = 0;
    for(int i = 0; i < attendanceCount; i++) {
        if(strcmp(attendances[i].date, today) == 0) {
            char memberName[50] = "Unknown";
            for(int j = 0; j < memberCount; j++) {
                if(members[j].id == attendances[i].memberId) {
                    strcpy(memberName, members[j].name);
                    break;
                }
            }
            
            printf("\t║ %-9d │ %-22s│ %-19s│ %-28s ║\n",
                   attendances[i].memberId, memberName,
                   attendances[i].checkInTime, attendances[i].checkOutTime);
            todayCount++;
        }
    }
    
    if(todayCount == 0)
        printf("\t║                         No attendance records for today                               ║\n");
    
    printf("\t╚═══════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n\tTotal check-ins today: %d\n", todayCount);
    waitForEnter();
}