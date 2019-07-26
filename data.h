#ifndef TRANSLATE_DATA_H
#define TRANSLATE_DATA_H

#define MAX_STR 40

typedef struct {
    int type;
    char* str;
} Text;

typedef struct {
    char* rusword;
    char* engword;
} Dict;

#include <stdio.h>
#include <stdlib.h>

Text* initWords(int value);
int readWords(FILE* input, Text* inWords, int chrs, char delim[]);
Dict* initDictionary(int lines);
int readDictionary(FILE* dictionary, Dict* inDict, int lines);
int changeWords(Text* inWords, Dict* inDict, int chrs, int lines);
int writeWords(FILE* output, Text* inWords, int chrs);

#endif // TRANSLATE_DATA_H