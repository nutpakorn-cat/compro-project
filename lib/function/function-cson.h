#ifndef FUNCTION_JSON_H
#define FUNCTION_JSON_H

char ***explode(char* str, char* explodeCharacter, const int _row) {
    int i = 0, j = 0;
    char ***output = (char ***) malloc(_row * sizeof **output);

    for (i = 0 ; i < _row ; ++i) {
        output[i] = (char **) malloc(__CARD * sizeof *output);
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
    
    i = 0; j = 0;
    output[i][j] = (char *) malloc(__CARD_INFO_TEXT * sizeof output[i][j]);
    strcpy(output[i][j], tok);
    
    if (j >= __CARD_INFO-1) {
        j = 0;
        ++i;
    }
    else ++j;
    
    while((tok = strtok(NULL, explodeCharacter))) {
        output[i][j] = (char *) malloc(__CARD_INFO_TEXT * sizeof output[i][j]);

        if (tok[0] == 0x20) tok[0] = 0x2;
        strcpy(output[i][j], tok);

        if (j >= __CARD_INFO-1) {
            j = 0;
            ++i;
        }
        else ++j;
    }

    free(src);
    free(tok);
    return output;
}

#endif