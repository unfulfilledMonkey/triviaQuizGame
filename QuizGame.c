/**********************************************************Libraries************************************************************/
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

/**********************************************************Structures**********************************************************/
struct triviaQuestionData{
    char topic[20];
    int questionNum;
    char question[150];
    char firstChoice[30];
    char secondChoice[30];
    char thirdChoice[30];
    char answer[30];
};

/**********************************************************Global Variables****************************************************/
struct triviaQuestionData records[100];
int recordCount = 0;

/**********************************************************Function Prototypes*************************************************/
//utility
void clearScreen();
void hidePassword(char *password, int maxLen);

//for files
int loadQuestions(struct triviaQuestionData records[], int *recordCount);

//menus
void mainMenu();
void adminMenu();
void showMainMenu();
void showAdminMenu();

//admin actions
int checkPassword();
void addQuestion(struct triviaQuestionData records[], int *recordCount);

/**********************************************************Functions***********************************************************/
//function to automatically clear the screen
void clearScreen(){
    system("cls");
}

//function loads all questions in question.txt
int loadQuestions(struct triviaQuestionData records[], int *recordCount){
    FILE *fp = fopen("questions.txt", "r");
    if(fp == NULL){
        *recordCount = 0;
        return 0;
    }

    char line[512];
    *recordCount = 0;
    while(fgets(line, sizeof(line), fp) && *recordCount < 100){
        struct triviaQuestionData q;
        int fields = sscanf(line, "%19[^|]|%d|%149[^|]|%29[^|]|%29[^|]|%29[^|]|%29[^\n]",
            q.topic,
            &q.questionNum,
            q.question,
            q.firstChoice,
            q.secondChoice,
            q.thirdChoice,
            q.answer
        );
        if(fields == 7){
            records[*recordCount] = q;
            (*recordCount)++;
        }
    }
    fclose(fp);
    return *recordCount;
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
    char correctPassword[] = "superspecialprivilege";
    char choice;
    int flag = 1;
    int number = 0;

    while(flag == 1){
        printf("Enter Password: ");
        hidePassword(password, 100);

        if(strcmp(password, correctPassword) == 0){
            flag = 0;
            number = 1;
        }else{
            printf("That doesn't seem right. Would you like to try again?(Y/N): ");
            scanf(" %c", &choice); //space to clear input buffer
            switch(choice){
                case 'Y':
                    break;
                case 'y':
                    break;
                case 'N':
                    return number;
                case 'n':
                    return number;
                default:
                    printf("Please input a correct input ('Y','y','N','n')\n");
            }
            clearScreen();
        }
    }
    
    return number;
}

//function to add new questions
void addQuestion(struct triviaQuestionData record[], int *recordCount){
    char questionInput[150];
    char answerInput [30];

    clearScreen();
    printf("Input New Question (Please >:0): ");
    fgets(questionInput, sizeof(questionInput), stdin);
    questionInput[strcspn(questionInput, "\n")] = 0; //removes newline character from input string

    printf("Input New Answer (Pretty :3): ");
    fgets(answerInput, sizeof(answerInput), stdin);
    answerInput[strcspn(answerInput, "\n")] = 0;

    //compare input with all records then return to start if input exists already
    for(int i = 0; i < *recordCount; i++){
        if(strcmp(records[i].question, questionInput) == 0
            && strcmp(records[i].answer, answerInput) == 0){
                printf("Auah Man... This question & answer already exists:\n");
                printf("Q%d: %s\nAnswer: %s\n", records[i].questionNum, 
                       records[i].question, records[i].answer);
                printf("See? Maybe your input was wrong or you forgot :')\n");
                printf("Please wait returning to admin menu...");
                Sleep(4000);
                return;
            }
    }

    //fill out variables for new question
    struct triviaQuestionData newRecord;
    strcpy(newRecord.question, questionInput);
    strcpy(newRecord.answer, answerInput);

    printf("Input topic: ");
    fgets(newRecord.topic, sizeof(newRecord.topic), stdin);
    newRecord.topic[strcspn(newRecord.topic, "\n")] = 0;

    printf("Input first choice: ");
    fgets(newRecord.firstChoice, sizeof(newRecord.firstChoice), stdin);
    newRecord.firstChoice[strcspn(newRecord.firstChoice, "\n")] = 0;

    printf("Input second choice: ");
    fgets(newRecord.secondChoice, sizeof(newRecord.secondChoice), stdin);
    newRecord.secondChoice[strcspn(newRecord.secondChoice, "\n")] = 0;

    printf("Input third choice: ");
    fgets(newRecord.thirdChoice, sizeof(newRecord.thirdChoice), stdin);
    newRecord.thirdChoice[strcspn(newRecord.thirdChoice, "\n")] = 0;

    //generate question number depending on current records present in topic
    int maxQNum = 0;
    for (int i = 0; i < *recordCount; i++) {
        if (strcmp(records[i].topic, newRecord.topic) == 0 &&
            records[i].questionNum > maxQNum) {
            maxQNum = records[i].questionNum;
        }
    }
    newRecord.questionNum = maxQNum + 1; 

    //checks if question is above max before adding
    if(*recordCount < 100){
        records[*recordCount] = newRecord;
        (*recordCount)++;

        //save to external file
        FILE *fp = fopen("questions.txt", "a");
        if(fp != NULL){
            fprintf(fp, "%s|%d|%s|%s|%s|%s|%s\n",
                newRecord.topic,
                newRecord.questionNum,
                newRecord.question,
                newRecord.firstChoice,
                newRecord.secondChoice,
                newRecord.thirdChoice,
                newRecord.answer);
            fclose(fp);
        }else{
             printf("Error: Could not open file for saving!\n");
        }
        printf("New Question Added Successfully! Yippee >:)!\n");
        printf("Mission Complete...Returning to Admin Menu...");
        Sleep(1000);
        return;
    }else{
        printf("EHRM...Record limit reached. Cannot add more.\n");
    }
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
                    addQuestion(records, &recordCount);
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
    loadQuestions(records, &recordCount);
    mainMenu();

    return 0;
}