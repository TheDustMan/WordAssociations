#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include "DictionaryEntry.h"
#include <map>
#include <string>
#include <vector>

class Dictionary
{
 private:
    typedef std::map<std::string, DictionaryEntry*> DictionaryMap;
 public:
    Dictionary();
    ~Dictionary();
    int insertDictionaryEntry(DictionaryEntry *entry);
    std::string lookupWord(std::string word);
    bool wordExists(std::string word);
    //private:
    DictionaryEntry* getDictionaryEntry(std::string word);
 private:
    DictionaryMap _mDictionary;
};

#endif /* _DICTIONARY_H_ */
