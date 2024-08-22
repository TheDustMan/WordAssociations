#ifndef _DICTIONARY_ENTRY_H_
#define _DICTIONARY_ENTRY_H_

#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "SpeechDefinitions.h"

class DictionaryEntry {
public:
  DictionaryEntry(std::string word);
  void addDefinition(std::string definition);
  void addDefinitions(std::vector<std::string> definitions);
  void addExample(std::string example);
  void addForm(std::string form);
  void addPartOfSpeech(PartsOfSpeechEnums_t partOfSpeech);
  void addPartsOfSpeech(std::vector<PartsOfSpeechEnums_t> partsOfSpeech);
  void addSyllable(std::string syllable);
  void addSyllables(std::vector<std::string> syllables);
  void setSyllableEmphasis(unsigned int emphasisPos);
  std::string getWord();
  std::vector<std::string> getDefinitions();
  std::vector<std::string> getExamples();
  std::vector<std::string> getForms();
  std::vector<PartsOfSpeechEnums_t> getPartsOfSpeech();
  std::vector<std::string> getSyllables();
  unsigned int getSyllableAmount() const;
  unsigned int getSyllableEmphasis() const;
  std::string toString() const;

private:
  unsigned int _mSyllableAmount;
  unsigned int _mSyllableEmphasis;
  std::string _mWord;
  std::vector<std::string> _mDefinitions;
  std::vector<std::string> _mExamples;
  std::vector<std::string> _mForms;
  std::vector<PartsOfSpeechEnums_t> _mPartsOfSpeech;
  std::vector<std::string> _mSyllables;

  friend std::ostream &operator<<(std::ostream &ostr,
                                  const DictionaryEntry &dictEntry);
};

#endif /* _DICTIONARY_ENTRY_H_ */
