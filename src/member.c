#include "../include/member.h"
#include "../include/utils.h"

extern Member members[];
extern int memberCount;

void memberManagement() {
    int choice;
    
    while(1) {
        clearScreen();
        printf("\n\n");
        printf("\t╔══════════════════════════════════════════════════════════════╗\n");
        printf("\t║                    MEMBER MANAGEMENT                         ║\n");
        printf("\t╠══════════════════════════════════════════════════════════════╣\n");
        printf("\t║              1. Add New Member                               ║\n");
        printf("\t║              2. View All Members                             ║\n");
        printf("\t║              3. Edit Member Details                          ║\n");
        printf("\t║              4. Delete Member                                ║\n");
        printf("\t║              5. Search Member                                ║\n");
        printf("\t║              6. Reactivate Member                            ║\n"); 
        printf("\t║              7. Back to Main Menu                            ║\n");
        printf("\t╚══════════════════════════════════════════════════════════════╝\n");
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addMember(); break;
            case 2: viewMembers(); break;
            case 3: editMember(); break;
            case 4: deleteMember(); break;
            case 5: searchMember(); break;
            case 6: reactivateMember(); break; 
            case 7: return;
            default:
                printf("\n\tInvalid choice! Please try again.\n");
                waitForEnter();
        }
    }
}

void addMember() {
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                      ADD NEW MEMBER                          ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    Member newMember;
    newMember.id = generateId();
    
    printf("\tEnter Full Name: ");
    getchar();
    fgets(newMember.name, sizeof(newMember.name), stdin);
    newMember.name[strcspn(newMember.name, "\n")] = 0;
    
    printf("\tEnter Email: ");
    fgets(newMember.email, sizeof(newMember.email), stdin);
    newMember.email[strcspn(newMember.email, "\n")] = 0;
    
    printf("\tEnter Phone: ");
    fgets(newMember.phone, sizeof(newMember.phone), stdin);
    newMember.phone[strcspn(newMember.phone, "\n")] = 0;
    
    printf("\tEnter Address: ");
    fgets(newMember.address, sizeof(newMember.address), stdin);
    newMember.address[strcspn(newMember.address, "\n")] = 0;
    
    printf("\tEnter Age: ");
    scanf("%d", &newMember.age);
    
    printf("\tEnter Gender (Male/Female/Other): ");
    scanf("%s", newMember.gender);
    
    getCurrentDate(newMember.joinDate);
    newMember.isActive = 1;
    
    members[memberCount++] = newMember;
    
    printf("\n\t✓ Member added successfully! Member ID: %d\n", newMember.id);
    waitForEnter();
}

void viewMembers() {
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("\t║                                              ALL MEMBERS LIST                                                ║\n");
    printf("\t╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("\t║ ID  │ Name                │ Email                    │ Phone      │ Age │ Gender │ Join Date  │ Status     ║\n");
    printf("\t╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    for(int i = 0; i < memberCount; i++) {
        printf("\t║ %-4d│ %-20s│ %-25s│ %-11s│ %-4d│ %-7s│ %-11s│ %-10s ║\n",
               members[i].id, members[i].name, members[i].email,
               members[i].phone, members[i].age, members[i].gender,
               members[i].joinDate, members[i].isActive ? "Active" : "Inactive");
    }
    
    printf("\t╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    waitForEnter();
}

void editMember() {
    int id, found = 0;
    
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                      EDIT MEMBER                             ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("\tEnter Member ID to edit: ");
    scanf("%d", &id);
    
    for(int i = 0; i < memberCount; i++) {
        if(members[i].id == id) {
            found = 1;
            printf("\n\tCurrent Details:\n");
            printf("\tName: %s\n", members[i].name);
            printf("\tEmail: %s\n", members[i].email);
            printf("\tPhone: %s\n", members[i].phone);
            
            printf("\n\tEnter New Details (press Enter to keep current value):\n");
            getchar();
            
            char input[100];
            
            printf("\tEnter New Name [%s]: ", members[i].name);
            fgets(input, sizeof(input), stdin);
            if(strlen(input) > 1) {
                input[strcspn(input, "\n")] = 0;
                strcpy(members[i].name, input);
            }
            
            printf("\tEnter New Email [%s]: ", members[i].email);
            fgets(input, sizeof(input), stdin);
            if(strlen(input) > 1) {
                input[strcspn(input, "\n")] = 0;
                strcpy(members[i].email, input);
            }
            
            printf("\tEnter New Phone [%s]: ", members[i].phone);
            fgets(input, sizeof(input), stdin);
            if(strlen(input) > 1) {
                input[strcspn(input, "\n")] = 0;
                strcpy(members[i].phone, input);
            }
            
            printf("\n\t✓ Member updated successfully!\n");
            break;
        }
    }
    
    if(!found) printf("\n\t✗ Member not found!\n");
    waitForEnter();
}

void deleteMember() {
    int id, found = 0;
    
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                      DELETE MEMBER                           ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("\tEnter Member ID to delete: ");
    scanf("%d", &id);
    
    for(int i = 0; i < memberCount; i++) {
        if(members[i].id == id) {
            found = 1;
            members[i].isActive = 0;
            printf("\n\t✓ Member marked as inactive successfully!\n");
            break;
        }
    }
    
    if(!found) printf("\n\t✗ Member not found!\n");
    waitForEnter();
}

void searchMember() {
    char searchTerm[50];
    int found = 0;
    
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                      SEARCH MEMBER                           ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("\tEnter name or ID to search: ");
    scanf("%s", searchTerm);
    
    clearScreen();
    printf("\n\tSearch Results:\n");
    printf("\t════════════════════════════════════════════════════════════════\n");
    
    for(int i = 0; i < memberCount; i++) {
        char idStr[10];
        sprintf(idStr, "%d", members[i].id);
        
        if(strstr(members[i].name, searchTerm) || strcmp(idStr, searchTerm) == 0) {
            found = 1;
            printf("\n\tID: %d\n", members[i].id);
            printf("\tName: %s\n", members[i].name);
            printf("\tEmail: %s\n", members[i].email);
            printf("\tPhone: %s\n", members[i].phone);
            printf("\tStatus: %s\n", members[i].isActive ? "Active" : "Inactive");
            printf("\t────────────────────────────────────────────────\n");
        }
    }
    
    if(!found) printf("\n\t✗ No members found matching '%s'\n", searchTerm);
    waitForEnter();
}

void reactivateMember() {
    int id, found = 0;
    
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                    REACTIVATE MEMBER                         ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    printf("\tInactive Members List:\n");
    printf("\t═══════════════════════════════════════════════════════════════\n");
    
    int inactiveCount = 0;
    for(int i = 0; i < memberCount; i++) {
        if(!members[i].isActive) {
            inactiveCount++;
            printf("\tID: %d - %s (%s)\n", members[i].id, members[i].name, members[i].email);
        }
    }
    
    if(inactiveCount == 0) {
        printf("\n\tNo inactive members found!\n");
        waitForEnter();
        return;
    }
    
    printf("\n\tEnter Member ID to reactivate: ");
    scanf("%d", &id);
    
    for(int i = 0; i < memberCount; i++) {
        if(members[i].id == id) {
            found = 1;
            if(members[i].isActive) {
                printf("\n\tThis member is already active!\n");
            } else {
                members[i].isActive = 1;
                printf("\n\t✓ Member '%s' has been reactivated successfully!\n", members[i].name);
            }
            break;
        }
    }
    
    if(!found) {
        printf("\n\t✗ Member not found!\n");
    }
    waitForEnter();
}