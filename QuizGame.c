#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

struct triviaQuestionData{
    char topic[20];
    int questionNum;
    char question[150];
    char firstChoice[30];
    char secondChoice[30];
    char thirdChoice[30];
    char answer[30];
};

struct triviaQuestionData records[100];

//function to automatically clear the screen
void clearScreen(){
    system("cls");
}

//function to hide input with ****
void hidePassword(char *password, int maxLen){
    int i = 0;
    char currentChar;

    while(1){
        currentChar = _getch();
        if(currentChar == 13){// if user presses "enter"
            break;
        }else if(currentChar == 8){// if user presses "delete/backspace"
            if(i>0){
                i--;
                printf("\b \b");
            }
        }else if(i<maxLen - 1 && currentChar >= 32 && currentChar <= 126){
            password[i++] = currentChar;
            printf("*");
        }
    }

    password[i] = '\0';
    printf("\n");
}

//function that checks password if correct
int checkPassword(){
    char password[100];
    char correctPassword[] = "superSpecialPrivilege@!";
    int flag = 1;
    int number = 0;

    while(flag == 1){
        printf("Enter Password: ");
        hidePassword(password, 100);

        if(strcmp(password, correctPassword) == 0){
            flag = 0;
            number = 1;
        }else{
            printf("That doesn't seem right. Try again.");
            Sleep(1000);
            clearScreen();
        }
    }
    
    return number;
}

//function that prints adminmain menu
void showAdminMenu(){
    printf("==============================================================================\n");
    printf("                                   ADMIN MENU\n");
    printf("==============================================================================\n");
    printf("1. Add Question\n");
    printf("2. Edit Question\n");
    printf("3. Delete Question\n");
    printf("4. Import data\n");
    printf("5. Export data\n");
    printf("6. Back to Main Menu\n");
    printf("Note: Select an option by typing its corresponding number.\n");
    printf("What would you like to do: ");
}

//function that handles user input in admin menu
void adminMenu(){
    int authorized = 0;
    int choice = 0;

    clearScreen();
    authorized = checkPassword();

    if(authorized == 1){
        while(1){
            clearScreen();
            showAdminMenu();
            scanf("%d", &choice);
            while (getchar() != '\n'); 

            switch(choice){
                case 1:
                    printf("Setting up workspace to add questions...");
                    Sleep(1000);
                    break;
                case 2:
                    printf("Setting up workspace to edit questions...");
                    Sleep(1000);
                    break;
                case 3:
                    printf("Setting up workspace to delete questions...");
                    Sleep(1000);
                    break;
                case 4:
                    printf("Setting up workspace to import questions...");
                    Sleep(1000);
                    break;
                case 5:
                    printf("Setting up workspace to export questions...");
                    Sleep(1000);
                    break;
                case 6:
                    printf("Returning to Main Menu, Cya Soon :)");
                    Sleep(1000);
                    return;
                default:
                    printf("Ayayay that didn't seem right, try again...");
                    Sleep(1000);
            }
        }
    }
}

//function that prints main menu
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

//function handles user input in main menu
void mainMenu(){
    int choice = 0;

    while(1){//infinite loop that will run until a break statement is encountered.
        clearScreen();
        showMainMenu();
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                printf("Setting up admin menu for you...\n");
                Sleep(1000);
                adminMenu();
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

//main function
int main(){
    mainMenu();

    return 0;
}