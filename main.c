#include "stdio.h"
#include "string.h"
#include <stdlib.h>


#define TXT 1024
#define WORD 30

char *sentenceP;
char *wordP;

int checkChar(char c);

void getWord();

int checkChar(char c) {
    if (c == '\t' || c == '\n' || c == ' ') {
        return 0;
    }
    return 1;

}

void getWord(char *word) {
    char curChar = getchar();
    for (int i = 0; i < WORD; ++i) {
        if (checkChar(curChar)) {
            word[i] = curChar;
        } else {
            return;
        }
        curChar = getchar();
    }
}

int main() {
    char word[WORD];
//    char sentence[1024];

    getWord(word);
    printf("%s",word);

    return 1;
}
