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
static char tilde = '~';
static char comma = ',';

int checkChar(char c);

void getWord(char *word);

void getSentence(char *sentence);

void addToGimatricSum(char c);

void printSameValueWords(char *sentence);

char convertToAtbash(char c);

void reverseAtbashWord(char *atbash);

void findSameAtbash();

void checkAllocation(void *p);

void isEqual(char *noSpaceSentence, int wordLen, char *printPotentials, int *printedWords);

void checkAllocation(void *p) {
    if (p == NULL) {
        exit(1);
    }
}

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
    char *printPotentials = (char *) malloc((TXT * sizeof(char)));
    int printedWords = 0;
    for (int i = 0; i <= len - wordLen; ++i) {
        int spacesIndex = 0;
        while (isspace(sentenceInput[i + spacesIndex])) {
            spacesIndex++;
        }
        i = i + spacesIndex;
        isEqual(sentenceInput + i, wordLen, printPotentials, &printedWords);
    }
    printf("%s", printPotentials);
}

void isEqual(char *sentence, int wordLen, char *printPotentials, int *printedWords) {
    int regularCounter = 0;
    int reverseCounter = 0;
    int i = 0;
    int j = 0;
    char *atbashPrint = (char *) calloc(TXT, sizeof(char));
    char *reversePrint = (char *) calloc(TXT, sizeof(char));

    while (i < wordLen) {
        if (isalpha(sentence[j])) {
            if (atbash[i] == sentence[j]) {
                regularCounter++;
                atbashPrint[j] = sentence[j];
            }
            if (reverseAtbash[i] == sentence[j]) {
                reverseCounter++;
                reversePrint[j] = sentence[j];
            }
            i++;
            j++;
        } else {
            if (isspace(sentence[j])) {
                if (regularCounter > 0) {
                    atbashPrint[j] = ' ';
                }
                if (reverseCounter > 0) {
                    reversePrint[j] = ' ';
                }
                j++;
            }
        }
    }
    if (regularCounter == wordLen) {
        if (strstr(printPotentials, atbashPrint) == NULL) {
            if ((*printedWords) > 0) {
                strcat(printPotentials, &comma);
            }
            *printedWords = *printedWords + 1;
            strcat(printPotentials, atbashPrint);
        }

    }
    if (reverseCounter == wordLen) {
        if (strstr(printPotentials, reversePrint) == NULL) {
            if ((*printedWords) > 0) {
                strcat(printPotentials, &comma);
            }
            *printedWords = *printedWords + 1;
            strcat(printPotentials, reversePrint);
        }
    }
    free(atbashPrint);
    free(reversePrint);
}


void printSameValueWords(char *sentence) {
    size_t len = strlen(sentence);
    char *wordToPrint = (char *) malloc((TXT * sizeof(char)));
    checkAllocation(wordToPrint);
    int currSum = 0, startIndex = 0, sequencesFound = 0;
    for (int i = 0; i < len; ++i) {
        char currChar = sentence[i];

        if (isalpha(currChar)) {
            currSum += toupper(currChar) - GIMATRIC_START_VAL;
        }
        if (currSum > gimatric_word_sum) {
            while (startIndex <= i && currSum > gimatric_word_sum) {
                if (isalpha(sentence[startIndex])) {
                    currSum -= toupper(sentence[startIndex]) - GIMATRIC_START_VAL;
                }
                startIndex++;
            }
        }
        if (currSum == gimatric_word_sum) {
            while (!isalpha(sentence[startIndex]) && startIndex < i) {
                startIndex++;
            }
            if (sequencesFound > 0) {
                strcat(wordToPrint, &tilde);
            }
            strncat(wordToPrint, sentence + startIndex, (i + 1) - startIndex);
            currSum -= toupper(sentence[startIndex]) - GIMATRIC_START_VAL;
            startIndex++;
            sequencesFound++;
        }
    }
    puts(wordToPrint);
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
//    printf("same value: \n");
//    printSameValueWords(sentenceInput);
    printf("\n");
    printf("all atbash words: ");
//    printf("%s",reverseAtbash);
    findSameAtbash();
//    printf("%s",atbash);
    return 1;
}