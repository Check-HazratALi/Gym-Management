#include "../include/reports.h"
#include "../include/utils.h"

extern Member members[];
extern Membership memberships[];
extern Attendance attendances[];
extern int memberCount;
extern int membershipCount;
extern int attendanceCount;

void reportsAnalytics() {
    int choice;
    
    while(1) {
        clearScreen();
        printf("\n\n");
        printf("\t╔══════════════════════════════════════════════════════════════╗\n");
        printf("\t║                  REPORTS AND ANALYTICS                       ║\n");
        printf("\t╠══════════════════════════════════════════════════════════════╣\n");
        printf("\t║              1. Member Report                                ║\n");
        printf("\t║              2. Revenue Report                               ║\n");
        printf("\t║              3. Attendance Report                            ║\n");
        printf("\t║              4. Active Members Report                        ║\n");
        printf("\t║              5. Back to Main Menu                            ║\n");
        printf("\t╚══════════════════════════════════════════════════════════════╝\n");
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: generateMemberReport(); break;
            case 2: generateRevenueReport(); break;
            case 3: generateAttendanceReport(); break;
            case 4: activeMembersReport(); break;
            case 5: return;
            default:
                printf("\n\tInvalid choice! Please try again.\n");
                waitForEnter();
        }
    }
}

void generateMemberReport() {
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                      MEMBER REPORT                           ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    int totalMembers = memberCount;
    int activeMembers = 0;
    int maleCount = 0, femaleCount = 0, otherCount = 0;
    
    for(int i = 0; i < memberCount; i++) {
        if(members[i].isActive) activeMembers++;
        
        if(strcmp(members[i].gender, "Male") == 0) maleCount++;
        else if(strcmp(members[i].gender, "Female") == 0) femaleCount++;
        else otherCount++;
    }
    
    printf("\t╔════════════════════════════════════════════╗\n");
    printf("\t║           MEMBERSHIP STATISTICS            ║\n");
    printf("\t╠════════════════════════════════════════════╣\n");
    printf("\t║ Total Members Registered:      %-11d ║\n", totalMembers);
    printf("\t║ Active Members:                %-11d ║\n", activeMembers);
    printf("\t║ Inactive Members:              %-11d ║\n", totalMembers - activeMembers);
    printf("\t╠════════════════════════════════════════════╣\n");
    printf("\t║           GENDER DISTRIBUTION              ║\n");
    printf("\t╠════════════════════════════════════════════╣\n");
    printf("\t║ Male Members:                  %-11d ║\n", maleCount);
    printf("\t║ Female Members:                %-11d ║\n", femaleCount);
    printf("\t║ Other:                         %-11d ║\n", otherCount);
    printf("\t╚════════════════════════════════════════════╝\n");
    
    waitForEnter();
}

void generateRevenueReport() {
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                      REVENUE REPORT                          ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    float totalRevenue = 0;
    float monthlyRevenue = 0, quarterlyRevenue = 0, yearlyRevenue = 0;
    
    for(int i = 0; i < membershipCount; i++) {
        if(strcmp(memberships[i].paymentStatus, "Paid") == 0) {
            totalRevenue += memberships[i].amount;
            
            if(strcmp(memberships[i].type, "Monthly") == 0)
                monthlyRevenue += memberships[i].amount;
            else if(strcmp(memberships[i].type, "Quarterly") == 0)
                quarterlyRevenue += memberships[i].amount;
            else if(strcmp(memberships[i].type, "Yearly") == 0)
                yearlyRevenue += memberships[i].amount;
        }
    }
    
    printf("\t╔══════════════════════════════════════════════════════╗\n");
    printf("\t║                REVENUE BREAKDOWN                     ║\n");
    printf("\t╠══════════════════════════════════════════════════════╣\n");
    printf("\t║ Total Revenue:                    $%-15.2f ║\n", totalRevenue);
    printf("\t╠══════════════════════════════════════════════════════╣\n");
    printf("\t║ Monthly Memberships Revenue:       $%-15.2f ║\n", monthlyRevenue);
    printf("\t║ Quarterly Memberships Revenue:     $%-15.2f ║\n", quarterlyRevenue);
    printf("\t║ Yearly Memberships Revenue:        $%-15.2f ║\n", yearlyRevenue);
    printf("\t╠══════════════════════════════════════════════════════╣\n");
    printf("\t║ Total Paid Memberships:            %-18d ║\n", membershipCount);
    printf("\t╚══════════════════════════════════════════════════════╝\n");
    
    waitForEnter();
}

void generateAttendanceReport() {
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                    ATTENDANCE REPORT                         ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("\tTop 10 Most Active Members:\n");
    printf("\t═══════════════════════════════════════════════════════════════\n");
    
    int memberAttendance[100] = {0};
    
    for(int i = 0; i < attendanceCount; i++) {
        for(int j = 0; j < memberCount; j++) {
            if(members[j].id == attendances[i].memberId) {
                memberAttendance[j]++;
                break;
            }
        }
    }
    
    for(int i = 0; i < memberCount && i < 10; i++) {
        if(memberAttendance[i] > 0)
            printf("\t%-20s: %d visits\n", members[i].name, memberAttendance[i]);
    }
    
    printf("\n\tTotal Check-ins Recorded: %d\n", attendanceCount);
    waitForEnter();
}

void activeMembersReport() {
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                  ACTIVE MEMBERS REPORT                       ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("\tActive Members List:\n");
    printf("\t═══════════════════════════════════════════════════════════════\n\n");
    
    int activeCount = 0;
    for(int i = 0; i < memberCount; i++) {
        if(members[i].isActive) {
            activeCount++;
            printf("\t%d. %s - %s (Joined: %s)\n", 
                   activeCount, members[i].name, members[i].email, members[i].joinDate);
        }
    }
    
    printf("\n\tTotal Active Members: %d\n", activeCount);
    waitForEnter();
}