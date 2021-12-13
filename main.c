#include "stdio.h"


#define TXT 1024
#define WORD 30

int checkChar(char c);

void getWord(char *word);

void getSentence(char *sentence);

int checkChar(char c) {
    if (c == '\t' || c == '\n' || c == ' ') {
        return 0;
    }
    return 1;
}

int checkSentence(char c) {
    if (c == '~') {
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

void getSentence(char *sentence) {
    char curChar = getchar();
    for (int i = 0; i < TXT; ++i) {
        if (checkSentence(curChar)) {
            sentence[i] = curChar;
        } else {
            return;
        }
        curChar = getchar();
    }
}

int main() {
    char word[WORD];
    char sentence[TXT];

    getWord(word);
    getSentence(sentence);
    printf("%s", word);
    printf("\n");
    printf("%s", sentence);

    return 1;
}
