#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

#include "definitions.h"

int writeWordToFile(int partOfSpeech, std::vector<std::string>& wordInfo)
{
  if (wordInfo.empty()) {
    std::cout << "Trying to write no word information to file?" << std::endl;
    return 1;
  }
  //if (partOfSpeech == NONE) {
  //std::cout << "Trying to write NONE partOfSpeech to file?" << std::endl;
  // return 1;
  //}
  bool posFound = false;
  for (unsigned int j = 1; j <= LAST_UNIQUE_POS; ++j) {
    if (partOfSpeech & pos_masks[j]) {
      posFound = true;
      for (unsigned int i = 0; i < wordInfo.size(); ++i) {
	file_streams[j] << wordInfo[i] << std::endl;
      }
    }
  }
  if (!posFound) {
    for (unsigned int i = 0; i < wordInfo.size(); ++i) {
      file_streams[0] << wordInfo[i] << std::endl;
    }    
  }
  return 0;
}

int findPartOfSpeech(std::string line, int &pos)
{
  /*
  std::string lineCopy = line;
  unsigned int ttPos = lineCopy.find("<tt>");
  while (ttPos != std::string::npos) {
    lineCopy = lineCopy.substr(ttPos + 1, lineCopy.size());
    unsigned int endTTPos = lineCopy.find("</tt>");
    std::string posString = lineCopy.substr(ttPos + 4, endTTPos);
    ttPos = lineCopy.find("<tt>");
  }
  */
  for (int i = 1; i <= POS_SEARCH_STRINGS - 1; ++i) {
    if (line.find(pos_search_strings[i]) != std::string::npos) {
      pos |= pos_masks[i];
      return 0;
    }
  }
  pos = pos_masks[NONE];
  return 1;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Please feed me a file." << std::endl;
    }
    for (unsigned int i = 0; i < POS_FILES; ++i) {
      std::cout << "Opening: " << pos_files[i] << std::endl;
      file_streams[i].open(pos_files[i], std::fstream::out | std::fstream::app);
    }

    std::ifstream infile(argv[1]);
    std::string line;

    std::vector<std::string> wordInfo;
    bool foundNewWord = false;
    bool parsingWord = false;
    int speechPart = pos_masks[NONE];
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
	if (line.find(NEW_WORD_TAG) != std::string::npos) {
	  foundNewWord = true;
	  parsingWord = false;
	}
	if (foundNewWord) {
	  writeWordToFile(speechPart, wordInfo);
	  wordInfo.clear();
	  speechPart = pos_masks[0];
	  foundNewWord = false;
	  parsingWord = true; 
	}
	if (parsingWord) {
	  if (line.find(POS_TAG) != std::string::npos) {
	    findPartOfSpeech(line, speechPart);
	  }
	  wordInfo.push_back(line);
	}
    }
    if (!wordInfo.empty()) {
      writeWordToFile(speechPart, wordInfo);
    }

    for (unsigned int i = 0; i < POS_FILES; ++i) {
      file_streams[i].close();
    }
    infile.close();
    return 0;
}
