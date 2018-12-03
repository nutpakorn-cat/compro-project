#ifndef FUNCTION_CLI_H
#define FUNCTION_CLI_H


CSON_STRING _cacheData;

char isLoad = 0;

void printMainScreen(void);

int menuNewCard(void);
void menuViewCard(void);

// Clear user screen
// For OSX
//  system("cls")
// For WIN32 | WIN64
//  system("clear")


void checkLoad() {
  if (!isLoad) {
      CSON_STRING tData;
      tData = loadCache("user-data", __CARD_ROW, __CARD_INFO);
      isLoad = 1;

      _cacheData = (char***) malloc(__CARD_ROW * sizeof(char**));

      int m = 0;
      for (int i = 0 ; i < __CARD_ROW ; ++i) {
        _cacheData[i] = (char**) malloc(__CARD_INFO * sizeof(char*));
        for (int j = 0 ; j < __CARD_INFO ; ++j) {
          m = 0;
          _cacheData[i][j] = (char*) malloc(strlen(tData[i][j]) * sizeof(char));
          strcmp(_cacheData[i][j], "");
          for (int k = 0 ; k < strlen(tData[i][j]) ; ++k) {
            if (tData[i][j][k] != 0x2) {

              _cacheData[i][j][m++] = tData[i][j][k];
            }
          }
        }
      }
    }
}



// Print main screen
void printMainScreen(void) {
  while (1) {
  char tab = 2;
  char buff[__SYSTEM_TEXT];
  char selectedMenu = 0;

  strcpy(buff, "");

  while (buff[0] != 'c') {
      clearScreen();
      renderMapTab("logo", tab);

      renderMapTab("menu", tab);

      if (!selectedMenu) renderMapTab("add-new-card-enable", tab);
      else renderMapTab("add-new-card-disable", tab);

      if (selectedMenu) renderMapTab("view-exist-card-enable", tab);
      else renderMapTab("view-exist-card-disable", tab);
      

      printf("\n\t\tUse\tw for up\n\t\t\ts for down\n\t\t\tc for enter\n");
      printf("\t\tInput> ");

      scanf(" %c", buff);

      if (buff[0] == 'w' && selectedMenu) --selectedMenu;
      else if (buff[0] == 's' && !selectedMenu) ++selectedMenu;
    }

    clearScreen();

    if (!selectedMenu) menuNewCard();
    else menuViewCard();
  }
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

void struprr(char *str) {
  for (int i = 0 ; i < strlen(str) ; ++i) {
    str[i] = toupper(str[i]);
  }
}

/* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}  

 /* itoa:  convert n to characters in s */
 void itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  

// New card 
// Get biographical information from input
// And save it to JSON file
int menuNewCard(void) {
  checkLoad();

  char skills[10][2][40];
  int globalSkills = 0;

  char buff[__SYSTEM_TEXT];

  char name[__CARD_INFO_TEXT];
  char surname[__CARD_INFO_TEXT];
  char address[__CARD_INFO_TEXT];
  char phoneNumber[__CARD_INFO_TEXT];
  char email[__CARD_INFO_TEXT];

  char isEmail = 0;
  int age, i;
  char bd[20];
  char gender[20];
  while (1) {
    char checkExist = 0;
    clearScreen();
    renderMapTab("add-new-card-disable",2);
    printf("\n\t\tEnter your biographical information (type 0 to go back)\n");
    while (!checkExist) {
      checkExist = 1;

      printf("\t\tName: ");
      scanf("%s", name);
      struprr(name);
      
      CHECK_GO_BACK(name, "str");

      printf("\t\tSurname: ");
      scanf("%s", surname);
      struprr(surname);
      CHECK_GO_BACK(surname, "str");

      for (int i = 0 ; i < __CARD_ROW ; ++i) {
        if (!strcmp(_cacheData[i][0], "")) break;
        
        if (!strcmp(_cacheData[i][0], name) && !strcmp(_cacheData[i][1], surname)) {
          printf("\t\tName and surname has already used.\n");
          checkExist = 0;
          break;
        } else checkExist = 1;
      }
    }

    printf("\t\tGender: ");
    scanf("%s", gender);
    CHECK_GO_BACK(gender, "str");

    struprr(gender);

    printf("\t\tAge: ");
    scanf("%d", &age);
    CHECK_GO_BACK(age, "int");

    while (1) {
      printf("\t\tBirthday (dd/mm/yyyy): ");
      scanf("%s", bd);
      CHECK_GO_BACK(bd, "str");

      int slash = 0;
      for (int k = 0 ; k < strlen(bd) ; ++k) {
        if (bd[k] == '/') slash++;
      }
      if (slash != 2) {
        printf("\t\tInvalid birthday. please input again.\n");

      } else break;
    }

    printf("\t\tPhone Number: ");
    scanf("%s", phoneNumber);
    CHECK_GO_BACK(phoneNumber, "str");

    while (!isEmail) {
      printf("\t\tEmail: ");
      scanf("%s", email);
      CHECK_GO_BACK(email, "str");

      struprr(email);

      
      for (i = 0 ; i < strlen(email) ; ++i) {
        if (email[i] == '@') isEmail = 1;
      }

      if (!isEmail) {
        printf("\t\t!!! Incorrect email format\n");
      } else {
        for (int i = 0 ; i < __CARD_ROW ; ++i) {
          if (!strcmp(_cacheData[i][0], "")) break;
          
          if (!strcmp(_cacheData[i][6], email)) {
            printf("\t\tEmail has already used.\n");
            isEmail = 0;
            break;
          }
        }
      }
    }

    clearScreen();
    renderMapTab("add-new-card-disable", 1);
    printf("\n\t\t=============Summary Data=============\n");
    printf("\t\tName\t\t= %s\n\t\tSurname\t\t= %s\n\t\tGender\t\t= %s\n\t\tAge\t\t= %d\n\t\tBirthday\t= %s\n\t\tPhone Number\t= %s\n\t\tEmail\t\t= %s", name, surname, gender, age, bd, phoneNumber, email);
    char cc;
    printf("\n\t\tIs everything correct? (Y/N) ");
    scanf(" %c", &cc);

    if (cc == 'Y' || cc == 'y') break;
  }

  clearScreen();

  while (1) {
    renderMapTab("skills", 3);
    printf("\n\t\t=============Summary Data=============\n");
    printf("\t\tName\t\t= %s\n\t\tSurname\t\t= %s\n\t\tGender\t\t= %s\n\t\tAge\t\t= %d\n\t\tBirthday\t= %s\n\t\tPhone Number\t= %s\n\t\tEmail\t\t= %s", name, surname, gender, age, bd, phoneNumber, email);
    
    

    printf("\n\n\t\tPlease insert your programming skill data (Max 10 skills) (type 0 for go back)");

    int countSkills = 0;

    int maxName = 0;

    for (int i = 0 ; i < 10 ; ++i) {
      // reset
      strcpy(skills[i][0], "");
      skills[i][1][0] = 0;

      printf("\n\t\t[%d] Skill name: ", i+1);
      scanf(" %[^\n]s", skills[i][0]);
      if (!strcmp(skills[i][0], "0")) {
        strcpy(skills[i][0], "");
        break;
      } else {
        if (strlen(skills[i][0]) > maxName) maxName = strlen(skills[i][0]);
      }
        while (1) {
          printf("\t\t[%d] Skill level (0-10): ", i+1);
          scanf("%d", &skills[i][1][0]);

          if (skills[i][1][0] < 0 || skills[i][1][0] > 10) {
            printf("\t\tSkill must be value between 0-10\n");
            continue;
          }
          else break;
        }
      printf("\n");

      countSkills++;
    }

    clearScreen();

    renderMapTab("skills", 2);
    printf("\n\t\t=============Summary Data=============\n");
    printf("\t\tName\t\t= %s\n\t\tSurname\t\t= %s\n\t\tGender\t\t= %s\n\t\tAge\t\t= %d\n\t\tBirthday\t= %s\n\t\tPhone Number\t= %s\n\t\tEmail\t\t= %s", name, surname, gender, age, bd, phoneNumber, email);
    
    printf("\n\n\t\tSkills:\n");
    for (int i = 0 ; i < countSkills ; ++i) {
      printf("\t\t\t[%d] ", i+1);

      for (int j = 0 ; j < maxName-strlen(skills[i][0]) ; ++j) {
        printf(" ");
      }

      printf("%s| ", skills[i][0]);

      for (int j = 0 ; j < skills[i][1][0]; ++j) {
        printf("*");
      }
      printf("\n");
    }

    char cc;
    printf("\n\n\t\tIs everything correct? (Y/N) ");
    scanf(" %c", &cc);

    if (cc == 'Y' || cc == 'y') {
      globalSkills = countSkills;
      break;
    }
    else clearScreen();
  }

  int dataCount = 0;

  for (int i = 0 ; i < __CARD_ROW ; ++i) {
    if (!strcmp(_cacheData[i][0], "")) break;
    dataCount++;
  }

  strcpy(_cacheData[dataCount][0], name);
  strcpy(_cacheData[dataCount][1], surname);
  strcpy(_cacheData[dataCount][2], gender);

  char ageString[3];
  itoa(age, ageString);

  strcpy(_cacheData[dataCount][3], ageString);
  strcpy(_cacheData[dataCount][4], bd);
  strcpy(_cacheData[dataCount][5], phoneNumber);
  strcpy(_cacheData[dataCount][6], email);

  printf("BEFORE ADD email = %s\n", _cacheData[dataCount][6]);

  for (int i = 0 ; i < globalSkills*2 ; i+=2) {
    int level = skills[i/2][1][0];
    char levelString[3];

    itoa(level, levelString);

    strcpy(_cacheData[dataCount][8+i], skills[i/2][0]);
    strcpy(_cacheData[dataCount][8+i+1], levelString);
  }

  printf("AFTER ADD email = %s\n", _cacheData[dataCount][6]);



  updateData(_cacheData, "user-data", __CARD_ROW, __CARD_INFO);
  return 0;
}

int columnUse[10] = {
  10,
  11,
  10,
  7,
  12,
  9,
  9
};

void menuViewCard() {
  while (1) {
    clearScreen();
    checkLoad();

    int maxId = 0;

    printf("\t\t          "); renderMap("card-center1");
    printf("\t\t          "); renderMap("card-center2");
    printf("\t\t          "); renderMap("card-center3");
    printf("\t\t          "); renderMap("card-center4");
    printf("\t\t          "); renderMap("card-center5");
    printf("\t\t          "); renderMap("card-center6");
    printf("\t\t|  ID  |   NAME   |  SURNAME  |  GENDER  |  AGE  |  BIRTHDAY  |  PHONE  |  EMAIL  |\n");
    for (int i = 0 ; i < __CARD_ROW ; ++i ) {
      
      if (!strcmp(_cacheData[i][0], "")) break;
      maxId++;
      printf("\t\t|  %2d  |", i+1);
      for (int j = 0 ; j < 7 ; ++j) {
        if (!strcmp(_cacheData[i][j], "")) break;

        if (strlen(_cacheData[i][j]) > columnUse[j]) {
          for (int k = 0 ; k < columnUse[j] ; ++k) {
          if (k >= columnUse[j]-3) printf(".");
          else printf("%c", _cacheData[i][j][k]);
          }
        } else {

          for (int k = 0 ; k < columnUse[j] ; ++k) {
            if (k >= strlen(_cacheData[i][j])) {
              printf(" ");
            } else {
              printf("%c", _cacheData[i][j][k]);
            }
          }
        }

        printf("|");

      }
      printf("\n");
    }

    char isGoback = 0;

    while (1) {
      int id;
      printf("\n\n\t\tInsert user id to view card: ");
      scanf("%d", &id);

      if (id > maxId) printf("\t\tUser id %d is not exist. Please try again\n", id);
      else if (id <= 0) {
        while (1) {
          char cc;
          printf("\t\tDo you want to go back? (Y/N) ");
          scanf(" %c", &cc);

          if (cc == 'Y' || cc == 'y') isGoback = 1;

          break;
        }
        break;
      }
      else {
        clearScreen();
        printCard(_cacheData[id-1]);
        break;
      }
    }
    if (isGoback) break;
  }

}

#endif