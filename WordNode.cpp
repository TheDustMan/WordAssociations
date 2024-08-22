#include "WordNode.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

WordNode::WordNode(unsigned int wordId, std::string theWord)
{
    _mWordID = wordId;
    _mWord = theWord;
}

WordNode::~WordNode()
{

}

std::string WordNode::getWord() const
{
    return _mWord;
}

void WordNode::addWordAssociation(unsigned int wordID)
{
    AssociationMap::iterator it = _mAssociationMap.find(wordID);
    if (it != _mAssociationMap.end()) {
        // Word association exists, increment counter
        ++(it->second);
    } else {
        // Association not yet in map, add it
        _mAssociationMap.insert(std::pair<unsigned int, unsigned int>(wordID, 1));
        // Push wordID into ID vector
        _mAssociatedWordIDs.push_back(wordID);
    }
}

bool WordNode::hasAssociatedWords() const
{
    return !_mAssociatedWordIDs.empty();
}

unsigned int WordNode::getRandomAssociatedWordID()
{
    unsigned int r = rand() % _mAssociatedWordIDs.size();
    return _mAssociatedWordIDs[r];
}

unsigned int WordNode::getAmountOfAssociations() const
{
  return _mAssociatedWordIDs.size();
}

unsigned int WordNode::getAssociationAtIndex(unsigned int index)
{
  if (index >=  _mAssociatedWordIDs.size()) {
    std::cout << "Index out of bounds, please try again." << std::endl;
  }
  return _mAssociatedWordIDs[index];
}

unsigned int WordNode::getNumTimesAssociated(unsigned int assocWordID)
{
    AssociationMap::iterator it = _mAssociationMap.find(assocWordID);
    if (it == _mAssociationMap.end()) {
        std::cout << "There is no associated word with ID: " << assocWordID << std::endl;        
        return 0;
    }
    return it->second;
}

