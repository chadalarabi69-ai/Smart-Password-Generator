#include <stdio.h>
#include <string.h>

#define SHIFT 3  


void encrypt(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] += SHIFT;
    }
}


void decrypt(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] -= SHIFT;
    }
}


void save_password(char *site, char *password) {
    FILE *f = fopen("passwords.txt", "a");
    if (!f) {
        printf("Error: Cannot open file.\n");
        return;
    }

    fprintf(f, "%s:%s\n", site, password); 
    fclose(f);

    printf("\nPassword saved successfully!\n");
}


void show_passwords() {
    FILE *f = fopen("passwords.txt", "r");
    if (!f) {
        printf("No passwords found!\n");
        return;
    }

    char line[200];
    int counter = 1;

    printf("\n--- Saved Passwords ---\n");

    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = 0;  

        char site[50], password[100];
       
        char *token = strtok(line, ":");
        if (token != NULL) strcpy(site, token);
        token = strtok(NULL, ":");
        if (token != NULL) strcpy(password, token);

        decrypt(password); 
        printf("%d. %s: %s\n", counter, site, password);
        counter++;
    }

    fclose(f);
}

int main() {
    int choice;
    char site[50], password[100];

    while (1) {
        printf("\n===== Password Manager =====\n");
        printf("1. Add new password\n");
        printf("2. Show all passwords\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("\nEnter site/account name: ");
            scanf("%s", site);
            printf("Enter password: ");
            scanf("%s", password);

            encrypt(password);
            save_password(site, password);
        }
        else if (choice == 2) {
            show_passwords();
        }
        else if (choice == 3) {
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}


