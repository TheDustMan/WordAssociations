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

void WordNode::addWordAssociation(unsigned int assocID)
{
    _mNextWordIDs.push_back(assocID);
}

bool WordNode::hasAssociatedWords() const
{
    return !_mNextWordIDs.empty();
}

unsigned int WordNode::getRandomAssociatedWordID() const
{
    int r = rand() % _mNextWordIDs.size();
    return _mNextWordIDs[r];
}

unsigned int WordNode::getAmountOfAssociations() const
{
  return _mNextWordIDs.size();
}

unsigned int WordNode::getAssociationAtIndex(unsigned int index) const
{
  if (index >=  _mNextWordIDs.size()) {
    std::cout << "Index out of bounds, please try again." << std::endl;
  }
  return _mNextWordIDs[index];
}
