#ifndef CSON_H
#define CSON_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

typedef char ***CSON_STRING;
typedef int CSON_ROW;
typedef int CSON_COLUMN;
typedef void _CSON;

CSON_STRING explode(char* str, char* explodeCharacter, const CSON_ROW rowMax, const int info);
CSON_STRING loadCache(char *fileName, const CSON_ROW rowMax, const int info);

_CSON updateData(CSON_STRING update, char* fileName, CSON_ROW rowMax, const int info);

CSON_STRING explode(char* str, char* explodeCharacter, const CSON_ROW rowMax, const int info) {
    int i = 0, j = 0;
    char ***output = (char ***) malloc(rowMax * sizeof **output);

    for (i = 0 ; i < rowMax ; ++i) {
        output[i] = (char **) malloc(info * sizeof *output);
    }

    char *tok;
    char *src = (char *) malloc(strlen(str) + __SYSTEM_TEXT);

    strcpy(src, str);

    tok = strtok(src, explodeCharacter);

    if(tok == NULL)
    {
        printf("no tokens found");
        free(src);
        while (!0x0) {}
    }

    for (i = 0 ; i < rowMax ; ++i) {
        for (j = 0 ; j < info ; ++j) {
            output[i][j] = (char *) malloc(__SYSTEM_TEXT * sizeof output[i][j]);

            strcpy(output[i][j], "");
        }
    }

    i = 0; j = 0;
    strcpy(output[i][j], tok);

    if (j >= info-1) {
        j = 0;
        ++i;
    }
    else ++j;

    while((tok = strtok(NULL, explodeCharacter))) {
        if (tok[0] == 0x20 || tok[0] == '\n') tok[0] = 2;

        if (tok[strlen(tok)-1] == '\n') tok[strlen(tok)-1] = 0x3;
        strcpy(output[i][j], tok);

        if (j >= info-1) {
            j = 0;
            ++i;
        }
        else ++j;
    }

    free(src);
    free(tok);
    return output;
}

CSON_STRING loadCache(char *fileName, const CSON_ROW rowMax, const int info) {
  CSON_ROW row = 1;
  FILE *ptr_file;
  char buf[BUFFER_SIZE];

  char *dbUrl = (char *) malloc(__SYSTEM_TEXT * sizeof dbUrl);
  char *input = (char *) malloc(1000 * sizeof input);

  strcpy(input, "");
  strcpy(buf, "");

  // Initial string for Windows
  strcpy(dbUrl, "");

  strcat(dbUrl, DB_URL);
  strcat(dbUrl, fileName);
  strcat(dbUrl, DB_EXTENSION);

  ptr_file =fopen(dbUrl,"r");
  if (!ptr_file) {
    printf("There is no file here %s ", dbUrl);
    while (1) {}
  }

  while (fgets(buf, BUFFER_SIZE, ptr_file) != NULL) {
    strcat(input, buf);
    ++row;
  }
	fclose(ptr_file);

  return explode(input, ",", rowMax, info);
}

_CSON updateData(CSON_STRING update, char* fileName, CSON_ROW rowMax, const int info) {
  FILE *ptr_file;
  char *dbUrl = (char *) malloc(__SYSTEM_TEXT * sizeof dbUrl);

    // Initial string for Windows
  strcpy(dbUrl, "");

  strcat(dbUrl, DB_URL);
  strcat(dbUrl, fileName);
  strcat(dbUrl, DB_EXTENSION);

  ptr_file =fopen(dbUrl,"w");
  if (!ptr_file) {
    printf("There is no file here %s ", dbUrl);
    while (1) {}
  }

  for (int i = 0 ; i < rowMax ; ++i) {
      for (int j = 0 ; j < info  ; ++j) {
          if (j == info-1) {
              if (i == rowMax-1) {
                  fprintf(ptr_file, "%s", update[i][j]);
              } else {
                  fprintf(ptr_file, "%s,\n", update[i][j]);
              }
          } else {
            fprintf(ptr_file, "%s, ", update[i][j]);
          }
      }
  }

  fclose(ptr_file);
}

#endif
