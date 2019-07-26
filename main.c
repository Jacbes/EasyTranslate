#include "data.h"
#include "string.h"

int main(int argc, char* argv[])
{
    if (argc != 4) {
        printf("%s%s",
               "Usage:\n",
               "./translate <in-file-name> <dictionary> <out-file-name>\n");
        return 0;
    }

    FILE* input = fopen(argv[1], "r");
    FILE* dictionary = fopen(argv[2], "r");
    int chrs = 0, lines = 0;
    char d;
    char delim[] = ".,-!?();:»« \n\t";

    if (input == NULL) {
        printf("Error open file\n");
        return 1;
    }

    while (fgetc(input) != EOF) {
        chrs++;
    }
    if (chrs == 0) {
        printf("Error in-file\n");
        return 1;
    }

    Text* inWords = initWords(chrs);
    if (inWords == NULL) {
        printf("Out of memory\n");
        return 1;
    }
    if (readWords(input, inWords, chrs, delim) != 0) {
        printf("Error in-file\n");
        return 1;
    }
    fclose(input);

    d = fgetc(dictionary);
    while (d != EOF) {
        if (d == ';') {
            lines++;
        }
        d = fgetc(dictionary);
    }
    if (lines == 0) {
        printf("Error dictionary\n");
        return 1;
    }

    Dict* inDict = initDictionary(lines);
    if (inDict == NULL) {
        printf("Out of memory\n");
        return 1;
    }
    if (readDictionary(dictionary, inDict, lines) != 0) {
        printf("Error dictionary\n");
        return 1;
    }
    fclose(dictionary);

    changeWords(inWords, inDict, chrs, lines);

    FILE* output = fopen(argv[3], "w");

    writeWords(output, inWords, chrs);

    fclose(output);

    free(inWords);
    free(inDict);

    return 0;
}
