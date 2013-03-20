#ifndef _WORDNODE_
#define _WORDNODE_

#include <string>
#include <vector>

class WordNode
{
public:
    WordNode(unsigned int, std::string theWord);
    ~WordNode();
    void addWordAssociation(unsigned int assocID);
    std::string getWord() const;
    bool hasAssociatedWords() const;
    unsigned int getRandomAssociatedWordID() const;
private:
    unsigned int _mWordID;
    std::string _mWord;
    std::vector<unsigned int> _mNextWordIDs;
};

#endif /* _WORDNODE_ */
