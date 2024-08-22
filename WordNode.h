#ifndef _WORDNODE_
#define _WORDNODE_

#include <map>
#include <string>
#include <vector>

class WordNode {
public:
  WordNode(unsigned int, std::string theWord);
  ~WordNode();
  void addWordAssociation(unsigned int assocID);
  std::string getWord() const;
  bool hasAssociatedWords() const;
  unsigned int getRandomAssociatedWordID();
  unsigned int getAmountOfAssociations() const;
  unsigned int getAssociationAtIndex(unsigned int index);
  unsigned int getNumTimesAssociated(unsigned int assocWordID);

private:
  unsigned int _mWordID;
  std::string _mWord;
  // Maps association ID with number of associations
  typedef std::map<unsigned int, unsigned int> AssociationMap;
  AssociationMap _mAssociationMap;
  // Keep a vector of the associated words as well for easy indexing
  std::vector<unsigned int> _mAssociatedWordIDs;
};

#endif /* _WORDNODE_ */
