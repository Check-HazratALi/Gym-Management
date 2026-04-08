#include "../include/utils.h"

void displayWelcomeScreen() {
    clearScreen();
    printf("\n\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                                                              ║\n");
    printf("\t║                  IRON PARADISE FITNESS CENTER                 ║\n");
    printf("\t║                                                              ║\n");
    printf("\t║                    \"Transform Your Body,                      ║\n");
    printf("\t║                     Transform Your Life\"                      ║\n");
    printf("\t║                                                              ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n\n");
    printf("\t                    ╔══════════════════════╗\n");
    printf("\t                    ║   Press Enter to     ║\n");
    printf("\t                    ║      Login           ║\n");
    printf("\t                    ╚══════════════════════╝\n");
    
    waitForEnter();
}

void displayLoginScreen() {
    char username[50];
    char password[50];
    int attempts = 0;
    
    while(attempts < 3) {
        clearScreen();
        printf("\n\n\n");
        printf("\t╔══════════════════════════════════════════════════════════════╗\n");
        printf("\t║                                                              ║\n");
        printf("\t║                         LOGIN PANEL                          ║\n");
        printf("\t║                                                              ║\n");
        printf("\t╚══════════════════════════════════════════════════════════════╝\n");
        printf("\n\n");
        
        printf("\t\tUsername: ");
        scanf("%s", username);
        printf("\t\tPassword: ");
        maskPassword(password);
        
        if(authenticateUser(username, password)) {
            printf("\n\n\t\tLogin Successful! Welcome, %s!\n", username);
            waitForEnter();
            return;
        } else {
            attempts++;
            printf("\n\n\t\tInvalid username or password! Attempts left: %d\n", 3 - attempts);
            waitForEnter();
        }
    }
    
    printf("\n\t\tToo many failed attempts. Exiting...\n");
    exit(0);
}

void displayMainMenu() {
    clearScreen();
    printf("\n\n");
    printf("\t╔══════════════════════════════════════════════════════════════╗\n");
    printf("\t║                                                              ║\n");
    printf("\t║                    GYM MANAGEMENT SYSTEM                     ║\n");
    printf("\t║                         MAIN MENU                            ║\n");
    printf("\t║                                                              ║\n");
    printf("\t╠══════════════════════════════════════════════════════════════╣\n");
    printf("\t║                                                              ║\n");
    printf("\t║              1. Member Management                            ║\n");
    printf("\t║              2. Membership Operation                         ║\n");
    printf("\t║              3. Daily Operation                              ║\n");
    printf("\t║              4. Reports and Analytics                        ║\n");
    printf("\t║              5. Exit                                         ║\n");
    printf("\t║                                                              ║\n");
    printf("\t╚══════════════════════════════════════════════════════════════╝\n");
}

int authenticateUser(char* username, char* password) {
    extern User admin;
    return (strcmp(username, admin.username) == 0 && 
            strcmp(password, admin.password) == 0);
}

void maskPassword(char* password) {
    int i = 0;
    char ch;
    while(1) {
        ch = getch();
        if(ch == '\r' || ch == '\n') {
            password[i] = '\0';
            break;
        } else if(ch == '\b' && i > 0) {
            i--;
            printf("\b \b");
        } else if(ch != '\b') {
            password[i++] = ch;
            printf("*");
        }
    }
}