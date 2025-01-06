void accountAdmin(char *account,char *password,int *userChoice,int*lock);

void loadBrand(Category*category,int*size);

void saveBrand(Category*category,int size);

void uplowerBrand(char *str);

void addBrand(Category*category,int *size);

void printBrand(Category*category,int *size);

void repairBrand(Category*category,int size);

void deleteBrand(Category*category,int *size,int *choice);

void searchBrand(Category*category,int size);

void sortBrand(Category*category,int size);

void saveSizeItem(int sum);

void loadSizeItem(int sum);

void categoryShow(int *choice,Category *category,int *size,int *lock,Phone *Item);

void manager(Category*categoty,Phone*Item,int *size, int *lock,int *choice);
