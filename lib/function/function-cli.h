#ifndef FUNCTION_CLI_H
#define FUNCTION_CLI_H

char ***_cacheData;
int _cacheRow;

void loadCache(void);

void clearScreen(void);
void printMainScreen(void);

int menuNewCard(void);
void menuViewCard(void);

// Update cache data 
// 3d array i = _cacheRow
//          j = __CARD_INFO
//          k = __CARD_INFO_TEXT
void loadCache(void) {
  int row = 1;
  FILE *ptr_file;
  char buf[BUFFER_SIZE];

  char *dbUrl = (char *) malloc(__SYSTEM_TEXT * sizeof dbUrl);
  char *input = (char *) malloc(__SYSTEM_TEXT * sizeof input); 

  strcat(dbUrl, DB_URL);
  strcat(dbUrl, DB_NAME);
  strcat(dbUrl, DB_EXTENSION);

  ptr_file =fopen(dbUrl,"r");
  if (!ptr_file)
    throwError("There is no file here", "function.loadCache.dbUrl", dbUrl);

  while (fgets(buf, BUFFER_SIZE, ptr_file) != NULL) {
    strcat(input, buf);
    ++row;
  }
	fclose(ptr_file);

  _cacheRow = row;
  _cacheData = explode(input, ",", row);

  free(dbUrl);
  free(input);
}

// Clear user screen
// For OSX
//  system("cls")
// For WIN32 | WIN64
//  system("clear")
void clearScreen(void) {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

// Print main screen
void printMainScreen(void) {
  char buff[__SYSTEM_TEXT];
  char selectedMenu = 0;

  while (buff[0] != 'c') {
    clearScreen();
    renderMap("logo");

    renderMap("menu");

    if (!selectedMenu) renderMap("add-new-card-enable");
    else renderMap("add-new-card-disable");

    if (selectedMenu) renderMap("view-exist-card-enable");
    else renderMap("view-exist-card-disable");
    

    printf("\nUse\tw for up\n\ts for down\n\tc for enter\n");
    printf("Input> ");

    scanf(" %c", buff);

    if (buff[0] == 'w' && selectedMenu) --selectedMenu;
    else if (buff[0] == 's' && !selectedMenu) ++selectedMenu;
  }

  clearScreen();

  if (!selectedMenu) menuNewCard();
  else menuViewCard();
}

#define CHECK_GO_BACK(var, type)                  \
      if (type == "str") {                        \
        if (!strcmp(var, "0")) { \
          printMainScreen(); \
          return 0;\
        }\
      } else {                                    \
        if (!var) { \
          printMainScreen();              \
          return 0;\
        }\
      }

// New card 
// Get biographical information from input
// And save it to JSON file
int menuNewCard(void) {
  char buff[__SYSTEM_TEXT];

  char name[__CARD_INFO_TEXT];
  char surname[__CARD_INFO_TEXT];
  char address[__CARD_INFO_TEXT];
  char phoneNumber[__CARD_INFO_TEXT];
  char email[__CARD_INFO_TEXT];

  char isEmail = 0;
  int age, i;
  renderMap("add-new-card-disable");
  printf("\nEnter your biographical information (type 0 to go back)\n");

  printf("Name: ");
  scanf("%s", name);
  CHECK_GO_BACK(name, "str");


  printf("Surname: ");
  scanf("%s", surname);
  CHECK_GO_BACK(surname, "str");

  printf("Age: ");
  scanf("%d", &age);
  CHECK_GO_BACK(age, "int");

  printf("Phone Number: ");
  scanf("%s", phoneNumber);
  CHECK_GO_BACK(phoneNumber, "str");

  while (!isEmail) {
    printf("Email: ");
    scanf("%s", email);
    CHECK_GO_BACK(email, "str");

    
    for (i = 0 ; i < strlen(email) ; ++i) {
      if (email[i] == '@') isEmail = 1;
    }

    if (!isEmail) {
      printf("!!! Incorrect email format\n");
    }
  }

  clearScreen();
  renderMap("add-new-card-disable");
  printf("\n=============Summary Data=============\n");
  printf("Name\t\t= %s\nSurname\t\t= %s\nAge\t\t= %d\nPhone Number\t= %s\nEmail\t\t= %s", name, surname, age, phoneNumber, email);
  printf("\nIs everything correct? (Y/N) ");
  scanf(" %1s", buff);

  if (buff == 'N')

  return 0;
}

void menuViewCard() {
  loadCache();
}

#endif