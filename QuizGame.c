#include <stdio.h>
#include <windows.h>

void showMainMenu(){
    printf("==================================================\n");
    printf("                      MAIN MENU\n");
    printf("==================================================\n");
    printf("1. Manage Data\n");
    printf("2. Play\n");
    printf("3. Exit\n");
    printf("Note: Select an option by typing its corresponding number.\n");
    printf("What would you like to do: ");
}

void mainMenu(){
    int choice = 0;

    while(1){//infinite loop that will run until a break statement is encountered.
        showMainMenu();
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                printf("Setting up admin menu for you...\n");
                Sleep(1000);
                break;
            case 2:
                printf("Setting up game screen for you...\n");
                Sleep(1000);
                break;
            case 3:
                printf("exiting, until next time...\n");
                Sleep(1000);
                abort();
                return;
            default:
                printf("Oops that didn't do anything, please try again...\n");
                Sleep(1000);
        }
    }
}

int main(){
    mainMenu();

    return 0;
}