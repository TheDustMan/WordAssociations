#include "DictionaryEntry.h"

DictionaryEntry::DictionaryEntry(std::string word) : _mWord(word) 
{

}

void DictionaryEntry::addDefinition(std::string definition)
{
    _mDefinitions.push_back(definition);
}

void DictionaryEntry::addDefinitions(std::vector<std::string> definitions)
{
    _mDefinitions.reserve(_mDefinitions.size() + definitions.size());
    _mDefinitions.insert(_mDefinitions.end(), definitions.begin(), definitions.end());
}

void DictionaryEntry::addExample(std::string example)
{
    _mExamples.push_back(example);
}

void DictionaryEntry::addPartOfSpeech(PartsOfSpeechEnums_t partOfSpeech)
{
    _mPartsOfSpeech.push_back(partOfSpeech);
}

void DictionaryEntry::addSyllable(std::string syllable)
{
    _mSyllables.push_back(syllable);
}

std::string DictionaryEntry::getWord()
{
    return _mWord;
}

std::vector<std::string> DictionaryEntry::getDefinitions()
{
    return _mDefinitions;
}

std::vector<std::string> DictionaryEntry::getExample()
{
    return _mExamples;
}

std::vector<PartsOfSpeechEnums_t> DictionaryEntry::getPartsOfSpeech()
{
    return _mPartsOfSpeech;
}

std::vector<std::string> DictionaryEntry::getSyllables()
{
    return _mSyllables;
}

std::string DictionaryEntry::toString() const
{
    std::ostringstream entryString;
    entryString << "Word: " << _mWord << std::endl;
    entryString << std::endl;
    entryString << "Syllables: ";
    if (_mSyllables.size()) {
        for (unsigned int i = 0U; i < _mSyllables.size(); ++i) {
            entryString << _mSyllables[i] <<  " ";
        }
    } else {
        entryString << "<N/A>";
    }
    entryString << std::endl << std::endl;
    entryString << "Parts of Speech: ";
    if (_mPartsOfSpeech.size()) {
        for (unsigned int i = 0U; i < _mPartsOfSpeech.size(); ++i) {
            entryString << PartsOfSpeechStrings[_mPartsOfSpeech[i]] <<  " ";
        }
    } else {
        entryString << "<N/A>";
    }
    entryString << std::endl << std::endl;
    entryString << "Definitions:" << std::endl;
    if (_mDefinitions.size()) {
        for (unsigned int i = 0U; i < _mDefinitions.size(); ++i) {
            entryString << (i+1) << ". " << _mDefinitions[i] << std::endl ;
        }
    } else {
        entryString << "<N/A>";
    }
    entryString << std::endl;
    entryString << "Examples:" << std::endl;
    if (_mExamples.size()) {
        for (unsigned int i = 0U; i < _mExamples.size(); ++i) {
            entryString << (i+1) << ". " << _mExamples[i] <<  " ";
        }
    } else {
        entryString << "<N/A>";
    }
    return entryString.str();
    /*
      //trying to use std::string instead of stringstream
    std::string entryString;
    entryString += "Word: " + _mWord + std::string("\n");
    entryString += std::string("\n");
    entryString += "Syllables: ";
    if (_mSyllables.size()) {
        for (unsigned int i = 0U; i < _mSyllables.size(); ++i) {
            entryString += _mSyllables[i] + std::string(" ");
        }
    } else {
        entryString += "<N/A>";
    }
    entryString += std::string("\n") + std::string("\n");
    entryString += "Parts of Speech: ";
    if (_mPartsOfSpeech.size()) {
        for (unsigned int i = 0U; i < _mPartsOfSpeech.size(); ++i) {
            entryString += PartsOfSpeechStrings[_mPartsOfSpeech[i]] + std::string(" ");
        }
    } else {
        entryString += "<N/A>";
    }
    entryString += std::string("\n") + std::string("\n");
    entryString += "Definitions: ";
    if (_mDefinitions.size()) {
        for (unsigned int i = 0U; i < _mDefinitions.size(); ++i) {
            entryString += _mDefinitions[i] + std::string(" ");
        }
    } else {
        entryString += "<N/A>";
    }
    entryString += std::string("\n");
    entryString += "Examples: ";
    if (_mExamples.size()) {
        for (unsigned int i = 0U; i < _mExamples.size(); ++i) {
            entryString += _mExamples[i] + std::string(" ");
        }
    } else {
        entryString += "<N/A>";
    }
    return entryString;
    */
}

std::ostream& operator+=(std::ostream &ostr, const DictionaryEntry &dictEntry)
{
    std::string dictEntryString = dictEntry.toString();
    ostr << dictEntryString;
}
