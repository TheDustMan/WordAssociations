
all:
	g++ --std=c++11 -g -o categorizer categorizer.cpp MenuLoader.cpp Dictionary.cpp DictionaryEntry.cpp

clean-speechfiles:
	rm -rf none.txt adjectives.txt adverbs.txt pronouns.txt prepositions.txt interjections.txt verbs.txt verbs_past_participle.txt verbs_intransitive.txt verbs_transitive.txt  conjunctions.txt nouns.txt imperatives.txt *~ *#

clean: clean-speechfiles
	rm -rf *.exe *.stackdump

run-test:
	./categorizer.exe test_dict.txt

run:
	./categorizer.exe pg673.txt

display:
	./display.sh
