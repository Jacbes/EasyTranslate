#include "string.h"

int slen(const char* s)
{
    int i, len;

    for (i = 0; s[i] != '\0'; i++);
    len = i;

    return len;
}

int schr(const char* str, char ch)
{
    int i, index = -1;

    for (i = 0; (str[i] != '\0') && (str[i] != ch); i++);
    if (str[i] == ch) {
        index = i;
    }

    return index;
}

int sequal(const char* s1, const char* s2)
{
    int i, flg = 1;

    for (i = 0; flg && (s1[i] != '\0' || s2[i] != '\0'); i++) {
        if (s1[i] != s2[i]) {
            flg = 0;
        }
    }

    return flg;
}

int scopy(const char* s1, char* s2)
{
    int i;

    for (i = 0; s1[i] != '\0'; i++) {
        s2[i] = s1[i];
    }
    s2[i] = '\0';

    return 0;
}

char toLowCase(char ch)
{
    if (ch >= 'A' && ch <= 'Z') {
        return ch + ('a' - 'A');
    }

    return ch;
}

char toUpCase(char ch)
{
    if (ch >= 'a' && ch <= 'z') {
        return ch + ('A' - 'a');
    }

    return ch;
}

char* suprus(const char* str, int len)
{
    char* ch = (char*)malloc(sizeof(char) * len);

    scopy(str, ch);

    for (int m = 0; m < len - 1; m++) {
        if (ch[m] == -48) {
            if (ch[m + 1] > -81) {
                ch[m + 1] -= 32;
            }
        } else if (ch[m] == -47) {
            if (ch[m + 1] == -111) {
                ch[m + 1] -= 16;
            } else {
                if (ch[m + 1] < -81) {
                    ch[m] -= 1;
                    ch[m + 1] += 32;
                }
            }
        }
    }

    return ch;
}

int isLowrus(char s2)
{
    if (s2 == -111) {
        return 1;
    }
    if ((s2 <= -113) && (s2 >= -128)) {
        return 1;
    }
    if ((s2 <= -65) && (s2 >= -80)) {
        return 1;
    }

    return 0;
}