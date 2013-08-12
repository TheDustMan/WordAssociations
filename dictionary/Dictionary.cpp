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
        std::cout << "The word: " << word << " is already in the dictionary." << std::endl;
        return 1;        
    }
    _mDictionary.insert(std::pair<std::string, DictionaryEntry*>(word, entry));
    return 0;
}

std::string Dictionary::lookupWord(std::string word)
{
    std::string wordInfoStr = "";
    DictionaryMap::iterator dictIter = _mDictionary.find(word);
    if (dictIter == _mDictionary.end()) {
        wordInfoStr = "The word " + word + " doesn't exist in the dictionary.";
    } else {
        wordInfoStr = dictIter->second->toString();
    }
    return wordInfoStr;
}
