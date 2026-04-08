#include "../include/membership.h"
#include "../include/utils.h"

extern Member members[];
extern Membership memberships[];
extern int memberCount;
extern int membershipCount;

void membershipOperation() {
    int choice;
    
    while(1) {
        clearScreen();
        printf("\n\n");
        printf("\t╔══════════════════════════════════════════════════════════════╗\n");
        printf("\t║                   MEMBERSHIP OPERATION                       ║\n");
        printf("\t╠══════════════════════════════════════════════════════════════╣\n");
        printf("\t║              1. Add New Membership                           ║\n");
        printf("\t║              2. View All Memberships                         ║\n");
        printf("\t║              3. Renew Membership                             ║\n");
        printf("\t║              4. Cancel Membership                            ║\n");
        printf("\t║              5. Back to Main Menu                            ║\n");
        printf("\t╚══════════════════════════════════════════════════════════════╝\n");
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addMembership(); break;
            case 2: viewMemberships(); break;
            case 3: renewMembership(); break;
            case 4: cancelMembership(); break;
            case 5: return;
            default:
                printf("\n\tInvalid choice! Please try again.\n");
                waitForEnter();
        }
    }
}

void addMembership() {
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                    ADD NEW MEMBERSHIP                        ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    Membership newMembership;
    newMembership.id = generateId();
    
    printf("\tEnter Member ID: ");
    scanf("%d", &newMembership.memberId);
    
    int memberExists = 0;
    for(int i = 0; i < memberCount; i++) {
        if(members[i].id == newMembership.memberId) {
            memberExists = 1;
            break;
        }
    }
    
    if(!memberExists) {
        printf("\n\t✗ Member not found!\n");
        waitForEnter();
        return;
    }
    
    printf("\tSelect Membership Type:\n");
    printf("\t1. Monthly ($50)\n");
    printf("\t2. Quarterly ($135)\n");
    printf("\t3. Yearly ($500)\n");
    printf("\tEnter choice: ");
    
    int typeChoice;
    scanf("%d", &typeChoice);
    
    switch(typeChoice) {
        case 1:
            strcpy(newMembership.type, "Monthly");
            newMembership.amount = 50.0;
            break;
        case 2:
            strcpy(newMembership.type, "Quarterly");
            newMembership.amount = 135.0;
            break;
        case 3:
            strcpy(newMembership.type, "Yearly");
            newMembership.amount = 500.0;
            break;
        default:
            strcpy(newMembership.type, "Monthly");
            newMembership.amount = 50.0;
    }
    
    getCurrentDate(newMembership.startDate);
    
    if(strcmp(newMembership.type, "Monthly") == 0)
        sprintf(newMembership.endDate, "30 days later");
    else if(strcmp(newMembership.type, "Quarterly") == 0)
        sprintf(newMembership.endDate, "90 days later");
    else
        sprintf(newMembership.endDate, "365 days later");
    
    strcpy(newMembership.paymentStatus, "Paid");
    memberships[membershipCount++] = newMembership;
    
    printf("\n\t✓ Membership added successfully! Amount: $%.2f\n", newMembership.amount);
    waitForEnter();
}

void viewMemberships() {
    clearScreen();
    printf("\n\n");
    printf("\t╔═══════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("\t║                                    ALL MEMBERSHIPS                                        ║\n");
    printf("\t╠═══════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("\t║ ID  │ Member ID │ Type       │ Amount  │ Start Date │ End Date      │ Status           ║\n");
    printf("\t╠═══════════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    for(int i = 0; i < membershipCount; i++) {
        printf("\t║ %-4d│ %-9d│ %-11s│ $%-7.2f│ %-11s│ %-14s│ %-16s ║\n",
               memberships[i].id, memberships[i].memberId, memberships[i].type,
               memberships[i].amount, memberships[i].startDate,
               memberships[i].endDate, memberships[i].paymentStatus);
    }
    
    printf("\t╚═══════════════════════════════════════════════════════════════════════════════════════════╝\n");
    waitForEnter();
}

void renewMembership() {
    int memberId, found = 0;
    
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                     RENEW MEMBERSHIP                         ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("\tEnter Member ID to renew membership: ");
    scanf("%d", &memberId);
    
    for(int i = 0; i < membershipCount; i++) {
        if(memberships[i].memberId == memberId) {
            found = 1;
            printf("\n\tCurrent Membership: %s (Ends: %s)\n", 
                   memberships[i].type, memberships[i].endDate);
            printf("\n\tRenewing membership...\n");
            
            Membership renewedMembership = memberships[i];
            renewedMembership.id = generateId();
            getCurrentDate(renewedMembership.startDate);
            strcpy(renewedMembership.paymentStatus, "Paid");
            
            memberships[membershipCount++] = renewedMembership;
            printf("\n\t✓ Membership renewed successfully!\n");
            break;
        }
    }
    
    if(!found) printf("\n\t✗ No membership found for this member!\n");
    waitForEnter();
}

void cancelMembership() {
    int memberId, found = 0;
    
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                    CANCEL MEMBERSHIP                         ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("\tEnter Member ID to cancel membership: ");
    scanf("%d", &memberId);
    
    for(int i = 0; i < membershipCount; i++) {
        if(memberships[i].memberId == memberId) {
            found = 1;
            strcpy(memberships[i].paymentStatus, "Cancelled");
            
            for(int j = 0; j < memberCount; j++) {
                if(members[j].id == memberId) {
                    members[j].isActive = 0;
                    break;
                }
            }
            
            printf("\n\t✓ Membership cancelled successfully!\n");
            break;
        }
    }
    
    if(!found) printf("\n\t✗ No membership found for this member!\n");
    waitForEnter();
}

