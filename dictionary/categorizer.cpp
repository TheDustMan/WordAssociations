#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>

#include "Dictionary.h"
#include "DictionaryEntry.h"
#include "MenuLoader.h"
#include "SpeechDefinitions.h"

const unsigned int NUM_TOKENS = 17;
const char* WORD_START_TAG = "<h1>";
const char* WORD_END_TAG = "</h1>";
const char* DEFINITION_START_TAG = "<def>";
const char* DEFINITION_END_TAG = "</def>";
const char* SYLLABLE_START_TAG = "<hw>";
const char* SYLLABLE_END_TAG = "</hw>";

static Dictionary _gDictionary;

enum MENU_CHOICES
    {
        INVALID,
        LOOKUP,
        QUIT
    };

typedef std::map<PartsOfSpeechEnums_t, std::vector<std::string> > PART_OF_SPEECH_TOKEN_MAP;
PART_OF_SPEECH_TOKEN_MAP part_of_speech_tokens =
    {
        {NONE, {""}},
        {NOUN, {"<tt>n.</tt>", "<tt>n. pl.</tt>", "<tt>n.pl.</tt>", "<tt>a. & n.</tt>", "<tt>n</tt>"}},
        {ADJECTIVE, {"<tt>a.</tt>", "<tt>a. & n.</tt>", "<tt>a. & adv.</tt>", "<tt>pron. & a.</tt>"}},
        {ADVERB, {"<tt>adv.</tt>", "<tt>a. & adv.</tt>"}},
        {PRONOUN, {"<tt>pron.</tt>", "<tt>pron. & a.</tt>"}},
        {INTERJECTION, {"<tt>interj.</tt>"}},
        {CONJUNCTION, {"<tt>conj.</tt>"}},
        {PREPOSITION, {"<tt>prep.</tt>"}},
        {VERB, {"<tt>v.</tt>"}},
        {VERB_PAST_PARTICIPLE, {"<tt>p.p.</tt>", "<tt>p. p.</tt>", "<tt>imp. & p. p.</tt>"}},
        {VERB_TRANSITIVE, {"<tt>v.t.</tt>", "<tt>v. t.</tt>", "<tt>v. i. & t.</tt>", "<tt>v. t. & i.</tt>"}},
        {VERB_INTRANSITIVE, {"<tt>v.i.</tt>", "<tt>v. i.</tt>", "<tt>v. i. & t.</tt>","<tt>v. t. & i.</tt>"}},
        {IMPERATIVE, {"<tt>imp.</tt>", "<tt>imp. & p. p.</tt>"}}
    };
            
const char *part_of_speech_files[NUM_PARTS_OF_SPEECH] =
    {
        "none.txt",
        "nouns.txt",
        "adjectives.txt",
        "adverbs.txt",
        "pronouns.txt",
        "interjections.txt",
        "conjunctions.txt",
        "prepositions.txt",
        "verbs.txt",
        "verbs_past_participle.txt",
        "verbs_transitive.txt",
        "verbs_intransitive.txt",
        "imperatives.txt"
    };

std::fstream file_handles[NUM_PARTS_OF_SPEECH];

enum CURRENT_ACTION 
    {
        NEW_WORD,
        PARSING_WORD
    };

void openPartOfSpeechFiles()
{
    for (unsigned int i = 0; i < NUM_PARTS_OF_SPEECH; ++i) {
        file_handles[i].open(part_of_speech_files[i], std::fstream::out | std::fstream::app);
    }
}

void closePartOfSpeechFiles()
{
    for (unsigned int i = 0; i < NUM_PARTS_OF_SPEECH; ++i) {
        file_handles[i].close();
    }
}

int writeWordToFile(const bool *const partsOfSpeech, std::vector<std::string>& wordInfo)
{
    if (wordInfo.empty()) {
        std::cout << "Trying to write no word information to file (this should happen once)" << std::endl;
        return 1;
    }
    //if (partOfSpeech == NONE) {
    //std::cout << "Trying to write NONE partOfSpeech to file?" << std::endl;
    // return 1;
    //}
    /* Write the word information to the appropriate file for each part of speech that
       the word belongs to */
    for (unsigned int posIter = 0; posIter < NUM_PARTS_OF_SPEECH; posIter++) {
        if (partsOfSpeech[posIter]) {
            for (unsigned int i = 0; i < wordInfo.size(); ++i) {
                file_handles[posIter] << wordInfo[i] << std::endl;
            }
        }
    }
    return 0;
}

void findPartOfSpeech(std::string &line, bool *partsOfSpeech)
{
    //static int counter = 0;
    for (PART_OF_SPEECH_TOKEN_MAP::iterator it = part_of_speech_tokens.begin();
         it != part_of_speech_tokens.end();
         it++) {
        if (it->first == NONE) { continue; }
        for (unsigned int tokenIter = 0; tokenIter < it->second.size(); tokenIter++) {
            if (line.find(it->second[tokenIter]) != std::string::npos) {
                partsOfSpeech[it->first] = true;
                partsOfSpeech[NONE] = false;
            }
        }
    }
    /*
    if (counter % 100 == 0) {
        std::cout << "Couldn't find part of speech wtf: " << counter++ << std::endl;
    }
    */

}

std::string getBetween(std::string str, std::string start, std::string end)
{
    
    size_t startPos = str.find(start);
    size_t endPos = str.find(end);
    size_t startMarkerSize = start.size();
    if (startPos == std::string::npos) {
        //std::cout << "Could not find start: " << start << std::endl;
        return "";
    }
    if (endPos == std::string::npos) {
        //std::cout << "Could not find end: " << end << std::endl;
        return "";
    }
    return str.substr(startPos + startMarkerSize, endPos - (startPos + startMarkerSize));
}

/* Find each occurence of the tags and store the contents into a cell of the vector */
std::vector<std::string> getAllTagContents(std::string str, std::string tagStart, std::string tagEnd)
{
    std::vector<std::string> contents;
    
    std::string tempStr = str;
    size_t tagEndSize = tagEnd.size();
    
    std::string content = "";
    do {
        content = getBetween(tempStr, tagStart, tagEnd);
        if (content.compare("") == 0) { break; }
        contents.push_back(content);
        tempStr = tempStr.substr(tempStr.find(tagEnd) + tagEndSize);
    } while (content.compare("") != 0);

    return contents;
}

void addDictionaryEntry(std::vector<std::string> wordInfo)
{
    if (wordInfo.empty()) {
        std::cout << "Trying to add an empty word into the dictionary." << std::endl;
        return;
    }
    std::string entryString = "";
    for (unsigned int i = 0; i < wordInfo.size(); ++i) {
        entryString += wordInfo[i];
    }
    std::string word = getBetween(entryString, WORD_START_TAG, WORD_END_TAG);
    std::vector<std::string> definitions = getAllTagContents(entryString, DEFINITION_START_TAG, DEFINITION_END_TAG);
    //std::string partsOfSpeech = getAllTagContents(entryString, DEFINITION_START_TAG, DEFINITION_END_TAG);
    DictionaryEntry *entry = new DictionaryEntry(word);
    entry->addDefinitions(definitions);
    _gDictionary.insertDictionaryEntry(entry);
}

void analyzeDictionary(std::string dictionaryFile)
{
    openPartOfSpeechFiles();

    std::ifstream infile(dictionaryFile);
    std::string line;
    
    std::vector<std::string> wordInfo;
    bool foundNewWord = false;
    bool parsingWord = false;
    bool speechParts[NUM_PARTS_OF_SPEECH] = {false};
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        if (line.find(WORD_START_TAG) != std::string::npos) {
            foundNewWord = true;
            parsingWord = false;
        }
        if (foundNewWord) {
            /* Process the previously gathered word before
               moving onto the next one */
            addDictionaryEntry(wordInfo);
            writeWordToFile(speechParts, wordInfo);
            wordInfo.clear();
            memset(speechParts, false, sizeof(speechParts));
            speechParts[NONE] = true;
            foundNewWord = false;
            parsingWord = true; 
        }
        if (parsingWord) {
            if (line.find("<tt>") != std::string::npos) {
                findPartOfSpeech(line, speechParts);
            }
            wordInfo.push_back(line);
        }
    }
    if (!wordInfo.empty()) {
        writeWordToFile(speechParts, wordInfo);
    }
    closePartOfSpeechFiles();
}

std::string printMenu(MenuLoader &menuLoader, std::string menuID)
{
    std::string choice;
    if (menuLoader.displayMenu(menuID)) {
        std::cout << "Error loading menu:" << menuID << std::endl;
    }
    std::cin >> choice;
    std::cout << std::endl;
    return choice;
}

int handleMenuInput(std::string menuInput)
{
    if (menuInput == "1") { return LOOKUP; }
    else if (menuInput == "q") { return QUIT; }
    return INVALID;
}

void beADictionaryApp()
{
    MenuLoader menuLoader;
    menuLoader.createMenu("main", "menus/main.menu");
    menuLoader.createMenu("lookup", "menus/lookup.menu");
    std::string menuInput;
    int menuChoice = INVALID;
    do {
        menuInput = printMenu(menuLoader, "main");
        menuChoice = handleMenuInput(menuInput);
        switch (menuChoice) {
        case LOOKUP:
            {
                std::string lookupWord = printMenu(menuLoader, "lookup");
                std::string wordInfo = _gDictionary.lookupWord(lookupWord);
                std::cout << "Dictionary Entry for: " << lookupWord << std::endl;
                std::cout << "--------------------------------------: " <<std::endl;
                std::cout << wordInfo << std::endl;
                break;
            }
        case QUIT:
            {
                // do any cleanup
                break;
            }
        case INVALID:
            {
                std::cout << "Invalid input: " << menuInput << std::endl << std::endl;
                break;
            }
        }
    } while (menuChoice != QUIT);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Please feed me a file." << std::endl;
    }
    analyzeDictionary(argv[1]);
    beADictionaryApp();
    return 0;
}
