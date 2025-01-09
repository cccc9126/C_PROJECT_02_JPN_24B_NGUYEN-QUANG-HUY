#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "datatype.h"
#include "function.h"
int main(int argc, const char * argv[]) {
    Category category[100];
    char account[50];
    char password[50];
    int size=0;
    int choice;
    int userChoice;
    Phone Item[100];
    loadBrand(category, &size);
    do {
        int lock=0;
        printf("++++MOBIPHONE MANAGEMENT SYSTEM+++\n");
        printf("\t\tCHOOSE YOUR ROLE\n");
        printf("===============================\n");
        printf("| [1] Admin.                  |\n");
        printf("| [2] Employee.               |\n");
        printf("| [3] Customer.               |\n");
        printf("| [0] Exit the program.       |\n");
        printf("===============================\n");
        printf("Please Input Your Choice : ");
        scanf("%d",&userChoice);
        fflush(stdin);
        if(userChoice<0||userChoice>3){
            printf("\n\nInvalid choice, please try again.\n\n\n");
        }
        switch (userChoice) {
            case 1:
                accountAdmin(account,password,&userChoice, &lock);
                if(lock){

                    manager(category, Item, &size, &lock,&choice);
                }
                break;
            case 2:
                printf("\n\n===============================\n");
                printf("|+++++++WELLCOME EMPLOYEE++++++++|\n");
                printf("===============================\n");
                printf("\n");

                manager(category, Item, &size, &lock,&choice);
                
                break;
            case 3:
                lock=2;
                printf("\n\n===============================\n");
                printf("|+++++++WELLCOME CUSTOMER++++++++|\n");
                printf("===============================\n");
                printf("\n");

                
                manager(category, Item, &size, &lock,&choice);
                break;
            default:
                break;
        }
    } while (userChoice!=0);
    printf("Close the program. Goodbye...........\n");
    return 0;
}
