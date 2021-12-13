#include "stdio.h"


#define TXT 1024
#define WORD 30
#define GIMATRIC_START_VAL 64

static int gimatric_word_sum = 0;

int checkChar(char c);

void getWord(char *word);

void getSentence(char *sentence);

void addToGimatricSum(char c);

char toUpper(char c);

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
            addToGimatricSum(curChar);
        } else {
            return;
        }
        curChar = getchar();
    }
}

char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
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

void addToGimatricSum(char c) {
    gimatric_word_sum += toUpper(c) - GIMATRIC_START_VAL;
}

int main() {
    char word[WORD];
    char sentence[TXT];

    getWord(word);
    getSentence(sentence);
    printf("\n");
    printf("%s", word);
    printf("\n");
    printf("%s", sentence);
    printf("\n");
    printf("%d", gimatric_word_sum);

    return 1;
}
