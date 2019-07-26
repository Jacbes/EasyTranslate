#include "data.h"
#include "string.h"

Text* initWords(int chrs)
{
    if (chrs <= 0) {
        return NULL;
    }

    Text* table = (Text*)malloc(sizeof(Text) * chrs);
    if (table == NULL) {
        return NULL;
    }

    for (int i = 0; i < chrs; i++) {
        table[i].str = (char*)malloc(sizeof(char) * MAX_STR);
        for (int j = 0; j < MAX_STR; j++) {
            table[i].str[j] = 0;
        }
        table[i].type = 0;
    }

    return table;
}

int readWords(FILE* input, Text* inWords, int chrs, char delim[])
{
    rewind(input);
    char o = 0;
    int k, i;

    o = fgetc(input);
    for (i = 0; i < chrs; i++) {
        if (schr(delim, o) == -1) {
            if (o == EOF) {
                break;
            }
            inWords[i].type = 1;
            k = 0;
            int flag = 1;
            while ((schr(delim, o) == -1) && (flag == 1)) {
                if (o == -1) {
                    break;
                }
                inWords[i].str[k] = o;
                o = fgetc(input);
                k++;
                if (o == -69) {
                    inWords[i].str[k] = o;
                    o = fgetc(input);
                    k++;
                } else if (o == -30) {
                    flag = 0;
                }
            }
            inWords[i].str[k] = '\0';
        } else if (schr(delim, o) != -1) {
            if (o == -30) {
                inWords[i].type = 2;
                inWords[i].str[0] = o;
                inWords[i].str[1] = fgetc(input);
                inWords[i].str[2] = fgetc(input);
                inWords[i].str[3] = '\0';
            } else {
                inWords[i].type = 2;
                inWords[i].str[0] = o;
                inWords[i].str[1] = '\0';
            }
            o = fgetc(input);
        }
    }

    if (i < chrs) {
        inWords = (Text*)realloc(inWords, sizeof(Text) * i);
    }

    if (inWords != NULL) {
        return 0;
    } else {
        return 1;
    }
}

Dict* initDictionary(int lines)
{
    if (lines == 0) {
        return NULL;
    }

    Dict* table = (Dict*)malloc(sizeof(Dict) * lines);
    if (table == NULL) {
        return NULL;
    }

    for (int i = 0; i < lines; i++) {
        table[i].rusword = (char*)malloc(sizeof(char) * MAX_STR);
        table[i].engword = (char*)malloc(sizeof(char) * MAX_STR);
        for (int j = 0; j < MAX_STR; j++) {
            table[i].rusword[j] = 0;
            table[i].engword[j] = 0;
        }
    }

    return table;
}

int readDictionary(FILE* dictionary, Dict* inDict, int lines)
{
    rewind(dictionary);
    int j;
    char o = 0;

    for (int i = 0; i < lines; i++) {
        if (o == EOF) {
            break;
        }
        j = 0;
        o = fgetc(dictionary);
        while (o != ';') {
            inDict[i].rusword[j] = o;
            o = fgetc(dictionary);
            j++;
        }
        if (j == 0) {
            return 1;
        }
        inDict[i].rusword[j] = '\0';
        j = 0;
        o = fgetc(dictionary);
        while (o != '\n') {
            if (o == EOF) {
                break;
            }
            inDict[i].engword[j] = o;
            o = fgetc(dictionary);
            j++;
        }
        if (j == 0) {
            return 1;
        }
        inDict[i].engword[j] = '\0';
    }

    return 0;
}

int changeWords(Text* inWords, Dict* inDict, int chrs, int lines)
{
    char* tWord = (char*)malloc(sizeof(char) * MAX_STR);
    char* dWord = (char*)malloc(sizeof(char) * MAX_STR);

    for (int i = 0; i < chrs; i++) {
        if (inWords[i].type == 1) {
            tWord = suprus(inWords[i].str, slen(inWords[i].str));
            for (int j = 0; j < lines; j++) {
                dWord = suprus(inDict[j].rusword, slen(inDict[j].rusword));
                if (sequal(tWord, dWord) == 1) {
                    if (isLowrus(inWords[i].str[1]) == 1) {
                        scopy(inDict[j].engword, inWords[i].str);
                        inWords[i].str[0] = toLowCase(inWords[i].str[0]);
                    } else {
                        scopy(inDict[j].engword, inWords[i].str);
                        inWords[i].str[0] = toUpCase(inWords[i].str[0]);
                    }
                }
            }
        } else if (inWords[i].type == 0) {
            break;
        }
    }

    free(tWord);
    free(dWord);

    return 0;
}

int writeWords(FILE* output, Text* inWords, int chrs)
{
    for (int i = 0; i < chrs; i++) {
        if (inWords[i].type != 0) {
            fprintf(output, "%s", inWords[i].str);
        } else {
            break;
        }
    }

    return 0;
}