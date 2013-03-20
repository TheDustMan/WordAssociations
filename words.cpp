#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include <map>
#include <vector>

#include "WordNode.h"

const int SENTENCE_MAX_LENGTH = 15;

enum Choices 
  {
    NONE,
    GENERATE_SENTENCE,
    QUIT    
  };

typedef std::map<unsigned int, WordNode*> WordMap;
typedef std::map<std::string, unsigned int> MirrorWordMap;
WordMap wordMap;
MirrorWordMap mirrorWordMap;

void usage() 
{
  std::cout << "Please give a file name to analyze or a .wdf (word database file)" << std::endl;
}

void addNewWord(std::string newWord) 
{
  MirrorWordMap::iterator it = mirrorWordMap.find(newWord);
  if (it != mirrorWordMap.end()) {
#if DEBUG
    std::cout << "Word \"" << newWord << "\" is already in map, abort" << std::endl;
#endif
    return;
  }
#if DEBUG
  std::cout << "Adding word \"" << newWord << "\" to map" << std::endl;
#endif
  static unsigned int wordId = 1;
  WordNode *wn = new WordNode(wordId, newWord);
  wordMap.insert( std::pair<unsigned int, WordNode*>(wordId, wn) );
  mirrorWordMap.insert( std::pair<std::string, unsigned int>(newWord, wordId) );
  ++wordId;
}

void addAssociation(std::string word, std::string associatedWord)
{
  MirrorWordMap::iterator wordIDIt = mirrorWordMap.find(word);
  MirrorWordMap::iterator assocWordIDIt = mirrorWordMap.find(associatedWord);
  if (wordIDIt == mirrorWordMap.end() || assocWordIDIt == mirrorWordMap.end()) {
#if DEBUG
    std::cout << "Word \"" << word << "\" or \"" << associatedWord << "\" is not in WordMap, which makes no sense..." << std::endl;
#endif
    return;
  }
  WordMap::iterator wordIt = wordMap.find(wordIDIt->second);
#if DEBUG
  std::cout << "Associated word \"" << word << "\"(" << wordIDIt->second << ") with word \"" << associatedWord << "\"(" << assocWordIDIt->second << ")" << std::endl;
#endif
  wordIt->second->addWordAssociation(assocWordIDIt->second);
}

int loadMenu(std::string menu)
{
  std::ifstream inFile(menu.c_str());
  
  if (!inFile) {
    std::cout << "Unable to open menu file: " << menu << std::endl;
    return 1; // terminate with error
  }
  
  for (std::string line; std::getline(inFile, line); ) {
    std::cout << line << std::endl;
  }
  std::cout << std::endl;

  inFile.close();
  return 0;
}

int printMainMenu()
{
  std::string choice;
  if (loadMenu("menus/main.menu")) {
    std::cout << "Error loading main menu" << std::endl;
  }
  std::cin >> choice;
  if (choice == "1") { return GENERATE_SENTENCE; }
  else if (choice == "q") { return QUIT; }
  return NONE;
}

int readFile(char *filename)
{
  std::string prevWord = "";
  std::string currentWord;
  std::ifstream inFile;
  
  inFile.open(filename);
  if (!inFile) {
    std::cout << "Unable to open file";
    return 1; // terminate with error
  }
  
  while (inFile >> currentWord) {
    addNewWord(currentWord);
    if (prevWord != "") {
      addAssociation(prevWord, currentWord);
    }
    prevWord = currentWord;
  }
  
  inFile.close();
  return 0;
}

int main(int argc, char** argv) {
  srand((unsigned int)time(NULL));
  
  if (argc < 2) {
    usage();
    return 0;
  } else {
    for (int fileIter = 1; fileIter < argc; fileIter++) {
      std::cout << "Processing file \"" << argv[fileIter] << "\"" << std::endl;
      int ret = readFile(argv[fileIter]);
      if (ret) {
	return 1;
      }
    }
    std::cout << "Total words: " << wordMap.size() << std::endl;

    int choice;
    do {
      choice = printMainMenu();
      
      switch (choice) {
      case GENERATE_SENTENCE:
	{
	  // Do stuff with information
	  std::cout << "=================================================" << std::endl;
	  std::string input;
	  // Choose a random word
	  unsigned int wordID = rand() % wordMap.size() + 1;
#if DEBUG
	  std::cout << "WordID is " << wordID << std::endl;
#endif
	  WordMap::iterator it = wordMap.find(wordID);
	  int sentenceLength = 0;
	  do {
	    std::string currentWord = it->second->getWord();
	    std::cout << currentWord << " ";
	    if (currentWord.find(".") != std::string::npos) { break; }
	    wordID = it->second->getRandomAssociatedWordID();
	    it = wordMap.find(wordID);
	    sentenceLength++;
	    if (sentenceLength == SENTENCE_MAX_LENGTH) { break; }
	  } while(it->second->hasAssociatedWords());
	  std::cout << "=================================================" << std::endl;
	  std::cout << std::endl;
	  break;
	} /* case GENERATE_SENTENCE */
      case QUIT:
	{	  
	  // Cleanup
	  std::cout << "Cleaning up dynamically allocated memory." << std::endl;
	  for (WordMap::iterator it = wordMap.begin(); it != wordMap.end(); it++) {
#if DEBUG
	    std::cout << "Deleting memory for word \"" << it->second->getWord() << "\"" << std::endl;
#endif
	    delete it->second;
	  }
	  break;
	} /* case QUIT */
      case NONE:
	{
	  std::cout << "Invalid choice" << std::endl;
	  break;
	}
      } /* switch */
    } while (choice != QUIT);
  }
  return 0;
}
