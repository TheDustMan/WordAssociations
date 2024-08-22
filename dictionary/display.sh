#!/bin/bash

echo "test_dict.txt"
echo "=============="
cat test_dict.txt
echo ""


for i in `ls adjectives.txt adverbs.txt conjunctions.txt interjections.txt none.txt nouns.txt prepositions.txt pronouns.txt verbs.txt verbs_intransitive.txt verbs_past_participle.txt verbs_transitive.txt`; do 
    echo "$i" 
    echo "==============="; 
    cat $i; 
    echo ""
done
