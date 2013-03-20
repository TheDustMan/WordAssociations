#include "WordNode.h"

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
