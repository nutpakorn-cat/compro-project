#ifndef CARD_H
#define CARD_H

#define SCORE_POSITION 8
#define MARGIN 10

int center = 10;
FILE *output;

/*
|||||||||||||||||||||||||||||||||||||||
|                                     |
|    NAME: NUTPAKORN TASSANASORN      |
|    GENDER: MALE    AGE: 18          |
|    BIRTHDAY: 20/12/2542             |
|    PHONE: 093526233X                |
|    EMAIL: MOMOMAEWMEOW@GMAIL.COM    |
|                                     |
|||||||||||||||||||||||||||||||||||||||
*/

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

void frenderMap(char* mapName) {
  FILE *ptr_file;
  char buf[BUFFER_SIZE];

  char* mapUrl = (char *) malloc(__SYSTEM_TEXT * sizeof mapUrl);

  strcat(mapUrl, FILE_URL);
  strcat(mapUrl, mapName);
  strcat(mapUrl, FILE_EXTENSION);

  // Debug
  // printf("[DEBUG] Load resource from %s\n", mapUrl);

  ptr_file = fopen(mapUrl,"r");
  if (!ptr_file)
    throwError("There is no file here", "function.renderMap.mapUrl", mapUrl);

  while (fgets(buf, BUFFER_SIZE, ptr_file) != NULL) {
    printf("%s",buf);
    fprintf(output, "%s",buf);
  }

	fclose(ptr_file);

  printf("\n");
  fprintf(output, "\n");
  free(mapUrl);
}

void setCenter(const int max) {
  if (max/2 > center) center = (max/2) + 10;
}

void printWhite(const int max) {
  int whitespace = center - (max/2);

  for (int i = 0; i < whitespace; ++i) {
    printf(" ");
    fprintf(output, " ");
  }
}

char header[20][50] = {
  "NAME: ",
  "",
  "GENDER: ",
  "AGE: ",
  "BIRTHDAY: ",
  "PHONE: ",
  "EMAIL: "
};

int setZero[7] = {
  7,
  0,
  17,
  0,
  10,
  7,
  7
};

void printCard(char** data)
{
  int max = 0;
  int tmp;

  for (int i = 0 ; i < SCORE_POSITION ; ++i) {
    if (!i || i == 2) {
      tmp = strlen(data[i]) + strlen(data[i+1]);
      tmp += setZero[i];
       //printf("DEBUG[%d] = %d %d %d Data: {%s, %s}\n", i, tmp, strlen(data[i]), strlen(data[i+1]), data[i], data[i+1]);
      
      ++i;
    } 
    else {
      tmp = strlen(data[i]);
      tmp += setZero[i];
      //printf("DEBUG[%d] = %d %d Data: {%s}\n", i, tmp, strlen(data[i]), data[i]);
    }

    if (tmp > max) {
      max = tmp;
      //printf("Max Here\n");
    }
  }

  int scoreCount = 0;

  int scoreMax = -1;
  int scoreMaxName = SCORE_POSITION;
  int scoreMaxScore = SCORE_POSITION;

  int tmpScore;
  for (int i = SCORE_POSITION ; i < __CARD_ROW ; i+=2) {
    if (!strcmp(data[i], "")) break;
    ++scoreCount;

    if (strlen(data[i]) > scoreMaxName) scoreMaxName = strlen(data[i]);
    if (atoi(data[i+1]) > scoreMaxScore) scoreMaxScore = atoi(data[i+1]);

    tmpScore = MARGIN + MARGIN + scoreMaxName + scoreMaxScore + 2;

    if (tmpScore > scoreMax) scoreMax = tmpScore;
    
  }

  // printf("Score count is %d\n", scoreCount);

  
  char f[50];
  char outputUrl[50];
  while (1) {
    printf("\tPlease insert file name to save (Example: output.txt): ");
    scanf("%s", f);

    
    strcpy(outputUrl, "");

    strcat(outputUrl, "output/");
    strcat(outputUrl, f);

    // printf("FIle at %s\n", outputUrl);

    FILE *testFile;

    testFile = fopen(outputUrl, "r");
    if (testFile) {
      char over;
      printf("\tFile name %s is already exist!! Do you want to override the file? (Y/N) ", f);
      scanf(" %c", &over);
      if (over == 'N' || over == 'n') continue;
    }
    fclose(testFile);

    output = fopen(outputUrl, "w+");

    if (!output) {
      printf("Error occur with file name %s. please try again.", f);
      continue;
    } else break;
  }

  clearScreen();

  if (scoreMax != -1) setCenter(scoreMax);

  setCenter(62);
  setCenter((2*MARGIN) + max);
  // printf("Center is %d\n", center);

  printWhite(62); frenderMap("card-info1"); 
  printWhite(62); frenderMap("card-info2");
  printWhite(62); frenderMap("card-info3");
  printWhite(62); frenderMap("card-info4");
  printWhite(62); frenderMap("card-info5");

  fprintf(output, "\n");    
  printf("\n");

  // Print top
  printWhite((2*MARGIN) + max);
  for (int i = 0 ; i < (2*MARGIN) + max ; ++i) {
    printf("|");
    fprintf(output, "|");
  }

  fprintf(output, "\n");
  printf("\n");
  
  printWhite((2*MARGIN) + max);
  for (int i = 0 ; i < (2*MARGIN) + max ; ++i) {
    if (!i || i == ((2*MARGIN) + max) - 1) {
      printf("|");
      fprintf(output, "|");
    }
    else {
      printf(" ");
      fprintf(output, " ");
    }
  }

  fprintf(output, "\n");  
  printf("\n");
  for (int i = 0 ; i < SCORE_POSITION-1 ; ++i) {
    printWhite((2*MARGIN) + max);
    for (int j = 0 ; j < MARGIN ; ++j) {
      if (!j) {
        printf("|");
        fprintf(output, "|");
      }
      else {
        printf(" ");
        fprintf(output, " ");
      }
    } 

    int rest = 0;
    // Header
    if (!i) {
      fprintf(output, "%s%s %s", header[i], data[i], data[i+1]);
      printf("%s%s %s", header[i], data[i], data[i+1]);
      rest = max - (strlen(data[i]) + strlen(data[i+1]) + setZero[i]);
      ++i;
    } else if (i == 2) {
      fprintf(output, "%s%s    %s%s", header[i], data[i], header[i+1] , data[i+1]);
      printf("%s%s    %s%s", header[i], data[i], header[i+1] , data[i+1]);
      rest = max - (strlen(data[i]) + strlen(data[i+1]) + setZero[i]);
      ++i;
    } else {
      fprintf(output, "%s%s", header[i], data[i]);
      printf("%s%s", header[i], data[i]);
      rest = max - (strlen(data[i]) + setZero[i]);
    }

    while (rest) {
      fprintf(output, " ");
      printf(" ");
      rest--;
    }

    for (int j = 0 ; j < MARGIN ; ++j) {
      if (j == MARGIN-1) {
        fprintf(output, "|");
        printf("|");
      }
      else {
        fprintf(output, " ");
        printf(" ");
      }
    } 

    fprintf(output, "\n");  
    printf("\n");

  }
  
  printWhite((2*MARGIN) + max);
  for (int i = 0 ; i < (2*MARGIN) + max ; ++i) {
    if (!i || i == ((2*MARGIN) + max) - 1) {
      printf("|");
      fprintf(output, "|");
    }
    else {
      fprintf(output, " ");
      printf(" ");
    }
    
  }

  fprintf(output, "\n");  
  printf("\n");
  printWhite((2*MARGIN) + max);
  for (int i = 0 ; i < (2*MARGIN) + max ; ++i) {
    printf("|");
    fprintf(output, "|");
  }
  // Skill

  fprintf(output, "\n");  
  printf("\n");
  if (scoreMax == -1) {
    printWhite((2*MARGIN) + max);
    for (int i = 0 ; i < (2*MARGIN) + max ; ++i) {
      fprintf(output, "|");
      printf("|");
    }
    fprintf(output, "\n");  
    printf("\n");

    printWhite((2*MARGIN) + max);
    for (int i = 0 ; i < (2*MARGIN) + max ; ++i) {
      if (!i || i == ((2*MARGIN) + max) - 1) {
        fprintf(output, "|");
        printf("|");
      }
      else if (i==((2*MARGIN) + max-10)/2) {
        fprintf(output, "Empty Data");
        printf("Empty Data");
        i += 9;
      }
      else {
        fprintf(output, " ");
        printf(" ");
      }
    }
    fprintf(output, "\n");  
    printf("\n");
    printWhite((2*MARGIN) + max);
    for (int i = 0 ; i < (2*MARGIN) + max ; ++i) {
      fprintf(output, "|");
      printf("|");
    }
  }
  else {
    max = scoreMax;
    printWhite(max);
    for (int i = 0 ; i < max ; ++i) {
      printf("|");
      fprintf(output, "|");
    }
    fprintf(output, "\n");  
    printf("\n"); 
    

    

    for (int i = 0 ; i < scoreCount*2 ; i+=2) {
      printWhite(max);
      for (int j = 0 ; j < MARGIN ; ++j) {
        if (!j) {
          printf("|");
          fprintf(output, "|");
        }
        else {
           printf(" ");
           fprintf(output, " ");
        }
      } 

      int whiteprint = scoreMaxName - strlen(data[SCORE_POSITION+i]);
      for (int j = 0 ; j < whiteprint ; ++j) {
        printf(" ");
        fprintf(output, " ");
      }

      printf("%s| ", data[SCORE_POSITION+i]);
      fprintf(output, "%s| ", data[SCORE_POSITION+i]);
      for (int j = 0 ; j < atoi(data[SCORE_POSITION+i+1]) ; ++j) {
        printf("*");
        fprintf(output, "*");
      }

      whiteprint = scoreMaxScore - atoi(data[SCORE_POSITION+i+1]);
      for (int j = 0 ; j < whiteprint ; ++j) {
        fprintf(output, " ");
        printf(" ");
      }

      for (int j = 0 ; j < MARGIN ; ++j) {
        if (j == MARGIN-1) {
          fprintf(output, "|");
          printf("|");
        }
        else {
          fprintf(output, " ");
          printf(" ");
        }
      } 
      fprintf(output, "\n");  
      printf("\n");
    }

    printWhite(max);
    for (int i = 0 ; i < max ; ++i) {
      fprintf(output, "|");
      printf("|");
    }
    fprintf(output, "\n");  
    printf("\n");

    printf("\n\n\tOutput file is %s\n", outputUrl);

    while (1) {
      char cc;
      printf("\tDo you want to go back (Y/N) ");
      scanf(" %c", &cc);

      if (cc == 'Y' || cc == 'y') break;

    }

    clearScreen();
    



  }

  fclose(output);
}

#endif