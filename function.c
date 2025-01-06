#include "datatype.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int accountAdmin(char *account,char *password,int *userChoice,int *lock){
    char adAccount[50];
    char adPassword[50];
    char adminAccount[] = "huy123@gmail.com";
    adminAccount[strcspn(adminAccount, "\n")]='\0';
    char adminPassWord[] = "012345";
    adminPassWord[strcspn(adminPassWord, "\n")]='\0';
    FILE * acc=fopen("account.bin", "wb");
    fwrite(&adminAccount, 50, 1, acc);
    fwrite(&adminPassWord, 50, 1, acc);
    fclose(acc);
    acc=fopen("account.bin", "rb");
    fread(&adAccount, 50, 1, acc);
    fread(&adPassword, 50, 1, acc);
    fclose(acc);
    printf("\n\n\t\tLOGIN\n");
    printf("===============================\n");
    printf("Email : ");
    fgets(account, 50, stdin);
    account[strcspn(account, "\n")]='\0';
    printf("Password : ");
    fgets(password, 50, stdin);
    password[strcspn(password, "\n")]='\0';
    printf("===============================\n");
    if(strcmp(account, adAccount)!=0||strcmp(password, adPassword)!=0){
        printf("Wrong account or password.\n");
        
        while(*userChoice!=9||*userChoice!=0){
            printf("Go back [9] or exit [0] : ");
            scanf("%d",userChoice);
            if(*userChoice==9){
                break;
            }else if (*userChoice==0){
                break;
            }else{
                printf("Only [9] or [0].\n");
            }
            
        }
    }else{
        printf("\t\tCorrect Account.\n");
        printf("===============================\n");
        printf("|+++++++WELLCOME ADMIN++++++++|\n");
        printf("===============================\n");
        printf("\n");
        *lock =1;
    }
    return *lock;
}


void saveBrand(Category*category,int size){
    FILE*file=fopen("category.bin", "wb");
    fwrite(&size, sizeof(size)/sizeof(int), 1, file);
    fwrite(category, sizeof(Category), size, file);
    fclose(file);
}


void loadBrand(Category* category, int* size) {
    FILE* file = fopen("category.bin", "rb");
    fread(size, sizeof(*size)/sizeof(int), 1, file);
    fread(category, sizeof(Category), *size, file);
    fclose(file);
}


void uplowerBrand(char *str){
    for(int i=0;str[i];i++){
        str[i]=tolower(str[i]);
    }
}


void addBrand(Category*category,int *size){
    printf("\n\n+++++++++ADD BRAND+++++++++\n");
    while(1){
        printf("Input Brand Name : ");
        fgets(category[*size].categoryName, 50, stdin);
        category[*size].categoryName[strcspn(category[*size].categoryName, "\n")]='\0';
        uplowerBrand(category[*size].categoryName);
        int count = 0;
        for(int i =0;i<*size;i++){
            uplowerBrand(category[i].categoryName);
            if(strcmp(category[*size].categoryName, category[i].categoryName)==0){
                count=1;
                break;
            }
        }
        if(count){
            printf("This brand already exists. Please enter a new brand");
        }else{
            category[*size].categoryId=(*size+1);
            (*size)++;
            printf("=============================\n");
            printf("Added successfully\n");
            printf("=============================\n");
            printf("\n\n");
            break;
        }
    }
}


void printBrand(Category*category,int *size){

    loadBrand(category, size);
    if(*size<=0){
        printf("Don have any Brand. You can choose [1] to add Brand.\n");
    }else{
        printf("\n\n      ++ALL BRANDS++\n");
        printf("=============================\n");
        printf("| ID    |  BRAND            |\n");
        printf("=============================\n");
        for(int i =0;i<*size;i++){
            category[i].categoryId=i+1;
            category[i].categoryName[0]=toupper(category[i].categoryName[0]);
            printf("  [%d]   |  %s\n",category[i].categoryId,category[i].categoryName);
            printf("-----------------------------\n");
        }
    }
}


void repairBrand(Category*category,int size){
    int index;
    char temp[50];
    printf("\n\n++++++++REPAIR BRAND++++++++\n");
    printf("\n\n      ++ALL BRANDS++\n");
    printf("=============================\n");
    printf("| ID    |  BRAND            |\n");
    printf("=============================\n");
    for(int i =0;i<size;i++){
        category[i].categoryId=i+1;
        category[i].categoryName[0]=toupper(category[i].categoryName[0]);
        printf("  [%d]   |  %s\n",category[i].categoryId,category[i].categoryName);
        printf("-----------------------------\n");
    }
    printf("Input ID of Brand you want to repair :");
    scanf("%d",&index);
    fflush(stdin);
    while(index<0||index>size){
        printf("Invalid choice, please try again.\n");
        printf("Input ID of Brand you want to repair :");
        scanf("%d",&index);
        fflush(stdin);
        }
    while(1){
        category[index-1].categoryName[0]=toupper(category[index-1].categoryName[0]);
        printf("Old name : %s\n",category[index-1].categoryName);
        printf("Input a new name for this Brand : ");
        fgets(temp, 50, stdin);
        temp[strcspn(temp, "\n")]='\0';
        uplowerBrand(temp);
        int count = 0;
        for(int i =0;i<size;i++){
            uplowerBrand(category[i].categoryName);
            if(strcmp(temp, category[i].categoryName)==0){
                count=1;
                break;
            }
        }
        if(count){
            printf("This brand already exists. Please enter a new brand\n");
        }else{
            strcpy(category[index-1].categoryName, temp);
            printf("=============================\n");
            printf("Repaired successfully\n");
            printf("=============================\n");
            printf("\n\n");
            break;
        }
    }
}


void deleteBrand(Category*category,int *size,int *choice){
    int index;
    
    if(*size<1){
        printf("Do not have any Brand. Can you choose [1] in MENU to add.\n");
    }else{
        printf("\n\n++++++++DELETE BRAND++++++++\n");
        printf("\n\n      ++ALL BRANDS++\n");
        printf("=============================\n");
        printf("| ID    |  BRAND            |\n");
        printf("=============================\n");
        for(int i =0;i<*size;i++){
            category[i].categoryId=i+1;
            category[i].categoryName[0]=toupper(category[i].categoryName[0]);
            printf("  [%d]   |  %s\n",category[i].categoryId,category[i].categoryName);
            printf("-----------------------------\n");
        }
        printf("Input ID of Brand you want to delete :");
        scanf("%d",&index);
        fflush(stdin);
        printf("BRAND : %s\n",category[index-1].categoryName);
        while(index<=0||index>*size){
            printf("Invalid choice, please try again.\n");
            printf("Input ID of Brand you want to delete :");
            scanf("%d",&index);
            fflush(stdin);
        }
        int sure;
        while(sure!=0||sure!=1){
            printf("Are you sure to delete this Brand [0]NO/[1]YES ");
            scanf("%d",&sure);
            if(sure==1){
                for(int i=(index-1);i<=*size;i++){
                    category[i]=category[i+1];
                }
                for(int i =0;i<*size;i++){
                    category[i].categoryId=i+1;
                }
                (*size)--;
                printf("=============================\n");
                printf("Deleted successfully\n");
                printf("=============================\n");
                printf("\n\n");
                break;
            }else if (sure==0){
                break;
            }else{
                printf("ONLY [0] or [1].\n");
            }
        }
    }
}


void searchBrand(Category *category,int size){
    char searchName[50];
    int count = 0;
    printf("\n\n++++++++SEARCH BRAND++++++++\n");
    printf("Input name of Brand you want to search : ");
    fgets(searchName, 50, stdin);
    searchName[strcspn(searchName, "\n")]='\0';
    uplowerBrand(searchName);
    for(int i = 0;i<=(size+1);i++){
        uplowerBrand(category[i].categoryName);
        if(strcmp(category[i].categoryName, searchName)==0){
            category[i].categoryName[0]=toupper(category[i].categoryName[0]);
            printf("\n++++INFORMATION ABOUT YOUR BRAND++++\n");
            printf("====================================\n");
            printf("| ID : %d |",category[i].categoryId);
            printf(" Name : %s  \t\t\t|\n",category[i].categoryName);
            printf("====================================\n");
            printf("Searched successfully\n");
            printf("=============================\n");
            printf("\n\n");
            count++;
        }
    }
    if(count==0){
        printf("Your Brand does not exist.\n");
    }
}


void sortBrand(Category*category,int size){
    printf("\n\n=============================\n");
    printf("[1] A->Z.\n");
    printf("[2] Z->A.\n");
    printf("[0] Exit the program.\n");
    printf("=============================\n");
    printf("Choose your choice : ");
    int sortChoice;
    scanf("%d",&sortChoice);
    if (sortChoice==1){
    Category temp;
        for(int i =0;i<=size;i++){
            for(int j =0;j<=size;j++){
                if(category[j-2].categoryName[0] > category[j-1].categoryName[0]) {
                    temp = category[j-2];
                    category[j-2] = category[j-1];
                    category[j-1] = temp;
                }
            }
        }
    }else if(sortChoice==2){
        Category temp;
            for(int i =0;i<=size;i++){
                for(int j =0;j<=size;j++){
                    if(category[j].categoryName[0] < category[j+1].categoryName[0]) {
                        temp = category[j];
                        category[j] = category[j+1];
                        category[j+1] = temp;
                    }
                }
            }
        printf("\n\n      ++ALL BRANDS++\n");
        printf("=============================\n");
        printf("| ID    |  BRAND            |\n");
        printf("=============================\n");
        for(int i =0;i<size;i++){
            category[i].categoryId=i+1;
            category[i].categoryName[0]=toupper(category[i].categoryName[0]);
            printf("  [%d]   |  %s\n",category[i].categoryId,category[i].categoryName);
            printf("-----------------------------\n");
        }
    }else if(sortChoice==0){
        return;
    }else{
        printf("Invalid choice");
    }
    printf("=============================\n");
    printf("Sorted successfully\n");
    printf("=============================\n");
    printf("\n\n");
}


void saveSizeItem(int *sum){
    FILE*sz=fopen("productSize.bin", "wb");
    fwrite(sum, sizeof(int), 1, sz);
    fclose(sz);
}


void loadSizeItem(int *sum){
    FILE*sz=fopen("productSize.bin", "rb");
    fread(sum, sizeof(int), 1, sz);
    fclose(sz);
}


void saveItem(Phone*Item,int sum){
    FILE*itemPtr=fopen("Item.bin", "wb");
    fwrite(Item, sizeof(Phone),sum , itemPtr);
    fclose(itemPtr);
}


void loadItem(Phone*Item,int sum){
    FILE*itemPtr=fopen("Item.bin", "rb");
    fread(Item, sizeof(Phone),sum , itemPtr);
    fclose(itemPtr);
}


void addItem(Phone *Item, int *size, Category *category, int *sum) {
    printf("\n\n+++++++++ADD PHONE+++++++++\n");
    printf("=============================\n");
    printf("| ID    |  BRAND            |\n");
    printf("=============================\n");
    for(int i =0;i<*size;i++){
        category[i].categoryId=i+1;
        category[i].categoryName[0]=toupper(category[i].categoryName[0]);
        printf("  [%d]   |  %s\n",category[i].categoryId,category[i].categoryName);
        printf("-----------------------------\n");
    }
    printf("Choose Brand for this phone : ");
    int chooseId;
    scanf("%d",&chooseId);
    fflush(stdin);
    strcpy(Item[*sum].brand, category[chooseId-1].categoryName);
    while (1) {
        Item[*sum].Id = (*sum) + 1;
        printf("PHONE NAME: ");
        fgets(Item[*sum].name, 50, stdin);
        Item[*sum].name[strcspn(Item[*sum].name, "\n")] = '\0';
        uplowerBrand(Item[*sum].brand);
        uplowerBrand(Item[*sum].name);
        int count = 0;
        for (int i = 0; i < *sum; i++) {
            uplowerBrand(Item[i].brand);
            uplowerBrand(Item[i].name);
            if (strcmp(Item[i].brand, Item[*sum].brand) == 0 && strcmp(Item[i].name, Item[*sum].name) == 0) {
                count = 1;
                break;
            }
        }
        if (count) {
            printf("This phone already exists under this brand. Please enter a new name.\n");
        } else {
            printf("PHONE PRICE: ");
            scanf("%f", &Item[*sum].price);
            fflush(stdin);
            printf("=============================\n");
            printf("Added successfully\n");
            printf("=============================\n\n");
            (*sum)++;
            break;
        }
    }
}


void printItem(Phone *Item, int *size, Category *category, int *sum){
    printf("\n\n+++++++++++++LIST PHONE++++++++++++++\n");
    printf("=====================================\n");
    for(int i = 0;i<*size;i++){
        category[i].categoryName[0]=toupper(category[i].categoryName[0]);
        printf("[%d] | %s\n",i+1,category[i].categoryName);
        uplowerBrand(category[i].categoryName);
        for(int j=0;j<*sum;j++){
            uplowerBrand(Item[j].brand);
            if(strcmp(Item[j].brand,category[i].categoryName)==0){
                printf("\t<> %s | %.2f $\n",Item[j].name,Item[j].price);
            }
        }
        printf("=====================================\n");
    }
}


void repairItem(Phone *Item, int *size, Category *category, int *sum){
    int index;
    int idTemp;
    printf("\n\n+++++++++REPAIR PHONE+++++++++\n");
    printf("=============================\n");
    printf("| ID    |  BRAND            |\n");
    printf("=============================\n");
    for(int i =0;i<*size;i++){
        category[i].categoryId=i+1;
        category[i].categoryName[0]=toupper(category[i].categoryName[0]);
        printf("  [%d]   |  %s\n",category[i].categoryId,category[i].categoryName);
        printf("-----------------------------\n");
    }
    printf("Input ID of Brand you want to repair : ");
    scanf("%d", &index);
    fflush(stdin);
    if (index < 1 || index > *size) {
        printf("Invalid brand ID. Please try again.\n");
        return;
    }
    printf("=================\n");
    printf(" NAME: %s\n", category[index - 1].categoryName);
    printf("=================\n");
    int j=0;
    int max;
    uplowerBrand(category[index-1].categoryName);
    for (int i = 0; i < *sum; i++) {
        if (strcmp(Item[i].brand, category[index-1].categoryName) == 0){
            j++;
            Item[i].Id=j;
            printf("ID: %d | ", Item[i].Id);
            printf("NAME: %s \n", Item[i].name);
            printf("PRICE: %.2f\n", Item[i].price);
            printf("------------------------------\n");
            max = j;
        }
    }
    if(max==0){
        printf("This Brand do not have any phone.\n\n");
        return;
    }else{
        printf("Input ID of Phone you want to repair : ");
        scanf("%d",&idTemp);
        fflush(stdin);
        if(idTemp<0||idTemp>max){
            printf("Invalid brand ID. Please try again.\n");
        }else{
            char temp[50];
            printf("NEW NAME : ");
            fgets(temp, 50, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            uplowerBrand(temp);
            
            int count = 0;
            for (int i = 0; i < *sum; i++) {
                if(strcmp(category[index-1].categoryName,Item[i].brand)==0){
                    uplowerBrand(Item[i].name);
                    if (strcmp(temp, Item[i].name) == 0) {
                        count = 1;
                        break;
                    }
                }
            }
            if (count) {
                printf("This phone already exists under this brand. Please enter a new name.\n");
            } else {
                for(int i=0;i<*sum;i++){
                    if(strcmp(category[index-1].categoryName,Item[i].brand)==0){
                        if(Item[i].Id==idTemp){
                            strcpy(Item[i].name,temp);
                            printf("NEW PRICE: ");
                            scanf("%f", &Item[i].price);
                            fflush(stdin);
                        }
                    }
                }
                printf("=============================\n");
                printf("Repair successfully\n");
                printf("=============================\n\n");
            }
        }
    }
}


void deleteItem(Phone *Item, int *size, Category *category, int *sum){
    int index;
    int idTemp;
    printf("\n\n++++++++DELETE PHONE++++++++\n");
    printf("=============================\n");
    printf("| ID    |  BRAND            |\n");
    printf("=============================\n");
    for(int i =0;i<*size;i++){
        category[i].categoryId=i+1;
        category[i].categoryName[0]=toupper(category[i].categoryName[0]);
        printf("  [%d]   |  %s\n",category[i].categoryId,category[i].categoryName);
        printf("-----------------------------\n");
    }
    printf("Input ID of Brand you want to delete : ");
    scanf("%d", &index);
    fflush(stdin);
    if (index < 1 || index > *size) {
        printf("Invalid brand ID. Please try again.\n");
        return;
    }
    printf("=================\n");
    printf(" NAME: %s\n", category[index - 1].categoryName);
    printf("=================\n");
    int j=0;
    int max;
    uplowerBrand(category[index-1].categoryName);
    for (int i = 0; i < *sum; i++) {
        if (strcmp(Item[i].brand, category[index-1].categoryName) == 0){
            j++;
            Item[i].Id=j;
            printf("ID: %d | ", Item[i].Id);
            printf("NAME: %s \n", Item[i].name);
            printf("PRICE: %.2f\n", Item[i].price);
            printf("------------------------------\n");
             max = j;
        }
    }
    if(max==0){
        printf("This Brand do not have any phone.\n\n");
        return;
    }
    printf("Input ID of Phone you want to delete : ");
    scanf("%d",&idTemp);
    fflush(stdin);
    if(idTemp<0||idTemp>max){
        printf("Invalid brand ID. Please try again.\n");
    }else{
        for(int i=0;i<*sum;i++){
            if(strcmp(Item[i].brand,category[index-1].categoryName)==0){
                    if(Item[i].Id==idTemp){
                        strcpy(Item[i].name,"");
                        strcpy(Item[i].brand,"");
                        break;
                }
            }
        }
        printf("=============================\n");
        printf("Delete successfully\n");
        printf("=============================\n\n");
    }
}


void searchItem(Phone *Item, int *size, Category *category, int *sum){
    char searchName[50];
    printf("\n\n++++++++SEARCH PHONE++++++++\n");
    printf("Input phone's name you want to search :");
    fgets(searchName, 50, stdin);
    searchName[strcspn(searchName, "\n")]='\0';
    uplowerBrand(searchName);
    int count =0;
    for(int i=0;i<*sum;i++){
        uplowerBrand(Item[i].name);
        if(strcmp(searchName, Item[i].name)==0){
            printf("\n\n%s\n",Item[i].brand);
            printf("==========================================\n");
            printf("NAME :  %s | PRICE : %f\n",Item[i].name,Item[i].price);
            printf("==========================================\n\n\n");
            count =1;
        }
    }
    if(count ==0){
        printf("\nDo not have any phong you search.\n\n");
    }
}


void sortItem(Phone *Item, int *size, Category *category, int *sum) {
    printf("\n\n++++++++SEARCH PHONE++++++++\n");
    printf("\n\n=============================\n");
    printf("[1] Price ascending.\n");
    printf("[2] Price descending.\n");
    printf("[0] Exit the program.\n");
    printf("=============================\n");
    printf("Choose your choice: ");
    int sortChoice;
    scanf("%d", &sortChoice);
    if (sortChoice < 0 || sortChoice > 2) {
        printf("Invalid choice!\n");
        return;
    }
    if (sortChoice == 1) {
        for (int i = 0; i < *sum - 1; i++) {
            for (int j = 0; j < *sum - 1 - i; j++) {
                if (Item[j].price > Item[j + 1].price) {
                    Phone temp = Item[j];
                    Item[j] = Item[j + 1];
                    Item[j + 1] = temp;
                }
            }
        }
    } else if (sortChoice == 2) {
        for (int i = 0; i < *sum - 1; i++) {
            for (int j = 0; j < *sum - 1 - i; j++) {
                if (Item[j].price < Item[j + 1].price) {
                    Phone temp = Item[j];
                    Item[j] = Item[j + 1];
                    Item[j + 1] = temp;
                }
            }
        }
    }
    printf("\n==========================\n");
    printItem(Item, size, category, sum);
}


void selection(Phone *Item, int *size, Category *category, int *sum){
    int menuChoice;
    float price1,price2;
    int index;
    printf("\n\n++++++++SELECTION PHONE++++++++\n");
    printf("        Selection Menu             \n");
    printf("===================================\n");
    printf("|[1] Cagetory.                     \n");
    printf("|[2] Price.                        \n");
    printf("|[0] Exit Menu.                    \n");
    printf("===================================\n");
    printf("Choose your choice : ");
    scanf("%d",&menuChoice);
    fflush(stdin);
    switch (menuChoice) {
        case 1:
            printf("\n\n+++++++++LIST PHONE+++++++++\n");
            printf("=============================\n");
            printf("| ID    |  BRAND            |\n");
            printf("=============================\n");
            for(int i =0;i<*size;i++){
                category[i].categoryId=i+1;
                category[i].categoryName[0]=toupper(category[i].categoryName[0]);
                printf("  [%d]   |  %s\n",category[i].categoryId,category[i].categoryName);
                printf("-----------------------------\n");
            }
            printf("Input ID of Brand you want to show: ");
            scanf("%d", &index);
            fflush(stdin);
            if (index < 1 || index > *size) {
                printf("Invalid brand ID. Please try again.\n");
                return;
            }
            printf("\n\n=================\n");
            printf(" NAME: %s\n", category[index - 1].categoryName);
            printf("=================\n");
            int j=0;
            uplowerBrand(category[index-1].categoryName);
            for (int i = 0; i < *sum; i++) {
                uplowerBrand(Item[i].brand);
                if (strcmp(Item[i].brand, category[index-1].categoryName) == 0){
                    j++;
                    Item[i].Id=j;
                    printf("ID: %d | ", Item[i].Id);
                    printf("NAME: %s \n", Item[i].name);
                    printf("PRICE: %.2f\n", Item[i].price);
                    printf("------------------------------\n");
                }
            }
            while(menuChoice!=9||menuChoice!=0){
                printf("Go back [9] or exit [0] : ");
                scanf("%d",&menuChoice);
                if(menuChoice==9){
                    printf("\n\n");
                    break;
                }else if (menuChoice==0){
                    break;
                }else{
                    printf("Only [9] or [0].\n");
                }
            }
            break;
        case 2:
            printf("Price from : ");
            scanf("%f",&price1);
            printf("To : ");
            scanf("%f",&price2);
            printf("\n\n\n===================\n");
            for(int i = 0;i<*size;i++){
                uplowerBrand(category[i].categoryName);
                printf("[%d] | %s\n",i+1,category[i].categoryName);
                uplowerBrand(category[i].categoryName);
                for(int j=0;j<*sum;j++){
                    uplowerBrand(Item[j].brand);
                    if(Item[j].price>price1 && Item[j].price < price2){
                        if(strcmp(Item[j].brand,category[i].categoryName)==0){
                            printf("\t[+] %s | %.2f $\n",Item[j].name,Item[j].price);
                        }
                    }
                }
                printf("===================\n");
            }
                while(menuChoice!=9||menuChoice!=0){
                    printf("Go back [9] or exit [0] : ");
                    scanf("%d",&menuChoice);
                    if(menuChoice==9){
                        printf("\n\n");
                        break;
                    }else if (menuChoice==0){
                        break;
                    }else{
                        printf("Only [9] or [0].\n");
                    }
                }
        default:
            break;
    }
}


void printItemMENU(Phone *Item,int *size,Category*category,int *lock){
    int phoneChoice;
    int sum=0;
    do{
        loadSizeItem(&sum);
        loadItem(Item,sum);
        printf("++++MOBIPHONE MANAGEMENT SYSTEM+++\n");
        printf("\t\t  PHONE MENU\n");
        printf("==============================\n");
        printf("| [1] Add A New Phone.       |\n");
        printf("| [2] Print All Phones.      |\n");
        printf("| [3] Repair Phone.          |\n");
        printf("| [4] Delete A Phone.        |\n");
        printf("| [5] Search Phone From Name.|\n");
        printf("| [6] Sort Phones.           |\n");
        printf("| [7] Selection Search.      |\n");
        printf("| [0] Exit The Program       |\n");
        printf("==============================\n");
        printf("\n\n");
        printf("Please Input Your Choice : ");
        scanf("%d",&phoneChoice);
        fflush(stdin);
        if(phoneChoice<0||phoneChoice>7){
            printf("Invalid choice, please try again.\n");
        }
        switch (phoneChoice) {
            case 0:
                break;
            case 1:
                if(*lock == 2){
                    printf("\n\n==========================================\n");
                    printf("++++ONLY ADMIN AND MANAGER CAN DO THIS++++\n");
                    printf("==========================================\n");
                    while(phoneChoice!=9||phoneChoice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",&phoneChoice);
                        if(phoneChoice==9){
                            break;
                        }else if (phoneChoice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                    printf("\n\n");
                }else{
                    addItem(Item, size, category, &sum);
                    saveSizeItem(&sum);
                    saveItem(Item, sum);
                    while(phoneChoice!=9||phoneChoice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",&phoneChoice);
                        if(phoneChoice==9){
                            printf("\n\n");
                            break;
                        }else if (phoneChoice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                }
                break;
            case 2:
                printItem(Item, size, category, &sum);
                
                while(phoneChoice!=9||phoneChoice!=0){
                    printf("Go back [9] or exit [0] : ");
                    scanf("%d",&phoneChoice);
                    if(phoneChoice==9){
                        break;
                    }else if (phoneChoice==0){
                        break;
                    }else{
                        printf("Only [9] or [0].\n");
                    }
                }
                break;
            case 3:
                if(*lock == 2){
                printf("\n\n==========================================\n");
                printf("++++ONLY ADMIN AND MANAGER CAN DO THIS++++\n");
                printf("==========================================\n");
                    while(phoneChoice!=9||phoneChoice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",&phoneChoice);
                        if(phoneChoice==9){
                            break;
                        }else if (phoneChoice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                printf("\n\n");
                }else{
                    repairItem(Item, size, category, &sum);
                    saveSizeItem(&sum);
                    saveItem(Item, sum);
                }
                break;
            case 4:
                if(*lock == 2){
                    printf("\n\n==========================================\n");
                    printf("++++ONLY ADMIN AND MANAGER CAN DO THIS++++\n");
                    printf("==========================================\n");
                    while(phoneChoice!=9||phoneChoice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",&phoneChoice);
                        if(phoneChoice==9){
                            break;
                        }else if (phoneChoice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                    printf("\n\n");
                }else{
                    deleteItem(Item, size, category, &sum);
                    saveSizeItem(&sum);
                    saveItem(Item, sum);
                    while(phoneChoice!=9||phoneChoice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",&phoneChoice);
                        if(phoneChoice==9){
                            break;
                        }else if (phoneChoice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                }
                break;
            case 5:
                searchItem(Item, size, category, &sum);
                while(phoneChoice!=9||phoneChoice!=0){
                    printf("Go back [9] or exit [0] : ");
                    scanf("%d",&phoneChoice);
                    if(phoneChoice==9){
                        break;
                    }else if (phoneChoice==0){
                        break;
                    }else{
                        printf("Only [9] or [0].\n");
                    }
                }
            printf("\n\n");
                break;
            case 6:
                sortItem(Item, size, category, &sum);
                while(phoneChoice!=9||phoneChoice!=0){
                    printf("Go back [9] or exit [0] : ");
                    scanf("%d",&phoneChoice);
                    if(phoneChoice==9){
                        break;
                    }else if (phoneChoice==0){
                        break;
                    }else{
                        printf("Only [9] or [0].\n");
                    }
                }
                break;
            case 7:
                selection(Item, size, category, &sum);
            default:
                break;
        }
    }while(phoneChoice!=0);
}


void categoryShow(int *choice,Category *category,int *size,int *lock,Phone *Item){
    do {
        printf("++++MOBIPHONE MANAGEMENT SYSTEM+++\n");
        printf("\t\t  PHONE MENU\n");
        printf("==============================\n");
        printf("| [1] Add A New Brand.       |\n");
        printf("| [2] Print All Brands.      |\n");
        printf("| [3] Repair Brands.         |\n");
        printf("| [4] Delete A Brand.        |\n");
        printf("| [5] Sreach Brand Form Name.|\n");
        printf("| [6] Sort Brands.           |\n");
        printf("| [0] Exit The Program.      |\n");
        printf("==============================\n");
        printf("Please Input Your Choice : ");
        scanf("%d",choice);
        fflush(stdin);
        if(*choice<0||*choice>6){
            printf("\n\nInvalid choice, please try again.\n\n\n");
        }
        switch (*choice) {
            case 1:
                if(*lock==1){
                    addBrand(category,size);
                    saveBrand(category,*size);
                    while(*choice!=9||*choice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",choice);
                        if(*choice==9){
                            break;
                        }else if (*choice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                }else if(*lock!=1){
                    printf("\n\n==============================\n");
                    printf("++++ONLY ADMIN CAN DO THIS++++\n");
                    printf("==============================\n");
                    while(*choice!=9||*choice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",choice);
                        if(*choice==9){
                            break;
                        }else if (*choice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                    printf("\n\n");
                }
                break;
            case 2:
                loadBrand(category,size);
                printBrand(category,size);
                while(*choice!=9||*choice!=0){
                    printf("Go back [9] or exit [0] : ");
                    scanf("%d",choice);
                    if(*choice==9){
                        break;
                    }else if (*choice==0){
                        break;
                    }else{
                        printf("Only [9] or [0].\n");
                    }
                }
                break;
            case 3:
                if(*lock==1){
                    repairBrand(category,*size);
                    saveBrand(category, *size);
                    while(*choice!=9||*choice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",choice);
                        if(*choice==9){
                            break;
                        }else if (*choice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                }else if(*lock!=1){
                    printf("\n\n==============================\n");
                    printf("++++ONLY ADMIN CAN DO THIS++++\n");
                    printf("==============================\n");
                    while(*choice!=9||*choice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",choice);
                        if(*choice==9){
                            break;
                        }else if (*choice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                    printf("\n\n");
                }
                break;
            case 4:
                if(*lock==1){
                    deleteBrand(category, size,choice);
                    saveBrand(category, *size);
                    while(*choice!=9||*choice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",choice);
                        if(*choice==9){
                            break;
                        }else if (*choice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                }else if(*lock!=1){
                    printf("\n\n==============================\n");
                    printf("++++ONLY ADMIN CAN DO THIS++++\n");
                    printf("==============================\n");
                    while(*choice!=9||*choice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",choice);
                        if(*choice==9){
                            break;
                        }else if (*choice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                    printf("\n\n");
                }
                break;
            case 5:
                    searchBrand(category, *size);
                    while(*choice!=9||*choice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",choice);
                        if(*choice==9){
                            break;
                        }else if (*choice==0){
                            break;
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                printf("\n\n");
                break;
            case 6:
                    sortBrand(category, *size);
                    while(*choice!=9||*choice!=0){
                        printf("Go back [9] or exit [0] : ");
                        scanf("%d",choice);
                        if(*choice==9){
                            break;
                        }else if (*choice==0){
                            break;
                            
                        }else{
                            printf("Only [9] or [0].\n");
                        }
                    }
                printf("\n\n");
                break;
            case 0:
                break;
            default:
                break;
        }
    } while (*choice!=0);
    printf("Close the management........\n");
}


void manager(Category*categoty,Phone*Item,int *size, int *lock,int *choice){
    int choiceManager;
    do {
        printf("++++MOBIPHONE MANAGEMENT SYSTEM+++\n");
        printf("\t\t\tMENU\n");
        printf("==============================\n");
        printf("| [1] Category.              |\n");
        printf("| [2] Product.               |\n");
        printf("| [0] Exit The Program.      |\n");
        printf("==============================\n");
        printf("Please Input Your Choice : ");
        scanf("%d",&choiceManager);
        switch (choiceManager) {
            case 1:
                categoryShow(choice, categoty, size, lock, Item);
                break;
            case 2:
                printItemMENU(Item, size, categoty, lock);
            default:
                break;
        }
    } while (choiceManager!=0);
}
