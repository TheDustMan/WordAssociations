#include <iostream>
#include "Dictionary.h"

Dictionary::Dictionary()
{

}

Dictionary::~Dictionary()
{
    DictionaryMap::iterator dictIter;
    for (dictIter = _mDictionary.begin(); dictIter != _mDictionary.end(); dictIter++) {
        delete dictIter->second;
    }
}

int Dictionary::insertDictionaryEntry(DictionaryEntry *entry)
{
    if (!entry) {
        std::cout << "Trying to insert a NULL entry into the dictionary." << std::endl;
        return 1;
    }
    std::string word = entry->getWord();
    DictionaryMap::iterator dictIter = _mDictionary.find(word);
    if (dictIter != _mDictionary.end()) {
        //std::cout << "The word: " << word << " is already in the dictionary." << std::endl;
        return 1;        
    }
    _mDictionary.insert(std::pair<std::string, DictionaryEntry*>(word, entry));
    return 0;
}

std::string Dictionary::lookupWord(std::string word)
{
    std::string wordInfoStr = "";
    DictionaryEntry* entryPtr = this->getDictionaryEntry(word);
    if (!entryPtr) {
        wordInfoStr = "The word " + word + " doesn't exist in the dictionary.";
    } else {
        wordInfoStr = entryPtr->toString();
    }
    return wordInfoStr;
}

bool Dictionary::wordExists(std::string word)
{
    return (this->getDictionaryEntry(word) != 0);
}

DictionaryEntry* Dictionary::getDictionaryEntry(std::string word)
{
    DictionaryEntry* entryPtr = 0;
    DictionaryMap::iterator dictIter = _mDictionary.find(word);
    if (dictIter != _mDictionary.end()) {
        entryPtr = dictIter->second;
    }    
    return entryPtr;
}
