#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include <ctype.h>
#include <stdbool.h>


#define TXT 1024
#define WORD 30
#define GIMATRIC_START_VAL 64
char wordInput[WORD];
char sentenceInput[TXT];

static char atbash[30];
static char reverseAtbash[30];
static int gimatric_word_sum = 0;

int checkChar(char c);

void getWord(char *word);

void getSentence(char *sentence);

void addToGimatricSum(char c);

void printSameValueWords(char *sentence);

char convertToAtbash(char c);

void reverseAtbashWord(char *atbash);

void findSameAtbash();


int isEqual(char *noSpaceSentence, int wordLen);

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
            atbash[i] = convertToAtbash(curChar);
        } else {
            reverseAtbashWord(atbash);
            return;
        }
        curChar = getchar();
    }
}

char convertToAtbash(char c) {
    if (islower(c)) {
        return 'z' - c + 'a';
    }
    return 'Z' - c + 'A';
}

void reverseAtbashWord(char *atbashWord) {
    int len = strlen(atbashWord);
    for (int i = 0; i < len; ++i) {
        reverseAtbash[i] = atbashWord[len - i - 1];
    }
}

void findSameAtbash() {
    int len = strlen(sentenceInput);
    int wordLen = strlen(atbash);
    for (int i = 0; i <= len - wordLen; ++i) {
        int ans = isEqual(sentenceInput + i, wordLen);
        if (ans == 1) {
            printf("%s", atbash);
        }
        if (ans == 2) {
            printf("%s", reverseAtbash);
        }
    }
}

int isEqual(char *sentence, int wordLen) {
    int regularCount = 0;
    int reverseCount = 0;
    int j = 0;
    for (int i = 0; i < wordLen; ++i) {
        if (sentence[i] != ' ') {
            if (atbash[j] == sentence[i]) {
                regularCount++;
                j++;
            }
            if (reverseAtbash[j] == sentence[wordLen - i - 1]) {
                reverseCount++;
                j++;
            }
        }
    }
    if (regularCount == wordLen) {
        return 1;
    }
    if (reverseCount == wordLen) {
        return 2;
    }
    return 0;
}


void printSameValueWords(char *sentence) {
    size_t len = strlen(sentence);
    char *wordToPrint = (char *) malloc((TXT * sizeof(char)));
    int startIndex = 0;
    int currSum = 0;
    for (int i = 0; i < len; ++i) {
        char currChar = sentence[i];
        if (isalpha(currChar)) {
            currSum += toupper(currChar) - GIMATRIC_START_VAL;
        }
        if (currSum == gimatric_word_sum) {
            strncpy(wordToPrint, sentence+startIndex, ((i+1)-startIndex));
            puts(wordToPrint);
            startIndex++;
            currSum -= toupper(sentence[startIndex]) - GIMATRIC_START_VAL;
            wordToPrint = (char *) realloc(wordToPrint, (TXT * sizeof(char)));
        }
        if (currSum > gimatric_word_sum) {
            currSum -= toupper(sentence[startIndex]) - GIMATRIC_START_VAL;
            startIndex++;
        }
    }
    free(wordToPrint);

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
    if (isalpha(c)) {
        gimatric_word_sum += toupper(c) - GIMATRIC_START_VAL;
    }
}


int main() {
    getWord(wordInput);
    getSentence(sentenceInput);
//    printf("\n");
//    printf("%s", wordInput);
//    printf("\n");
//    printf("%s", sentenceInput);
//    printf("\n");
//    printf("%d", gimatric_word_sum);
    printf("same value: \n");
    printSameValueWords(sentenceInput);
    printf("\n");
//    printf("all atbash words: ");
//    findSameAtbash();
//    printf("%s",atbash);
    return 1;
}