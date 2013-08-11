#ifndef _DICTIONARY_ENTRY_H_
#define _DICTIONARY_ENTRY_H_

#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "SpeechDefinitions.h"

class DictionaryEntry
{
public:
    DictionaryEntry(std::string word);
    void addDefinition(std::string definition);
    void addExample(std::string example);
    void addPartOfSpeech(PartsOfSpeechEnums_t partOfSpeech);
    void addSyllable(std::string syllable);
    std::string getWord();
    std::vector<std::string> getDefinitions();
    std::vector<std::string> getExample();
    std::vector<PartsOfSpeechEnums_t> getPartsOfSpeech();
    std::vector<std::string> getSyllables();
    std::string toString() const;
private:
    std::string _mWord;
    std::vector<std::string> _mDefinitions;
    std::vector<std::string> _mExamples;
    std::vector<PartsOfSpeechEnums_t> _mPartsOfSpeech;
    std::vector<std::string> _mSyllables;

    friend std::ostream& operator<<(std::ostream& ostr, const DictionaryEntry& dictEntry);
};

#endif /* _DICTIONARY_ENTRY_H_ */
