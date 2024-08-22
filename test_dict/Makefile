
all:
	g++ -g -o categorizer categorizer.cpp

clean:
	rm -rf none.txt adjectives.txt adverbs.txt pronouns.txt prepositions.txt interjections.txt verbs.txt verbs_past_participle.txt verbs_intransitive.txt verbs_transitive.txt  conjunctions.txt nouns.txt preterite*.txt *~

run-test:
	./categorizer.exe test_dict.txt

run:
	./categorizer.exe pg673.txt
