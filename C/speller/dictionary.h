// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
// const means remain constant

// those three prototypes are essentially just:
// bool check(const string word);
// unsigned int hash(const string word);
// bool load(const string dictionary);
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);

unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
