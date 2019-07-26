#ifndef TRANSLATE_STRING_H
#define TRANSLATE_STRING_H

#include <stdio.h>
#include <stdlib.h>

int slen(const char* s);
int schr(const char* str, char ch);
int sequal(const char* s1, const char* s2);
int scopy(const char* s1, char* s2);
char toLowCase(char ch);
char toUpCase(char ch);
char* suprus(const char* ch, int len);
int isLowrus(char s2);

#endif // TRANSLATE_STRING_H
