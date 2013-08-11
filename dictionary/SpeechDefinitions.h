#ifndef _SPEECH_DEFINITIONS_H_
#define _SPEECH_DEFINITIONS_H_

const unsigned int NUM_PARTS_OF_SPEECH = 13;

enum PartsOfSpeechEnums_t
    {
        NONE,
        NOUN,
        ADJECTIVE,
        ADVERB,
        PRONOUN,
        INTERJECTION,
        CONJUNCTION,
        PREPOSITION,
        VERB,
        VERB_PAST_PARTICIPLE,
        VERB_TRANSITIVE,
        VERB_INTRANSITIVE,
        IMPERATIVE
    };

static const char* PartsOfSpeechStrings[NUM_PARTS_OF_SPEECH] =
    {
        "NONE",
        "NOUN",
        "ADJECTIVE",
        "ADVERB",
        "PRONOUN",
        "INTERJECTION",
        "CONJUNCTION",
        "PREPOSITION",
        "VERB",
        "VERB_PAST_PARTICIPLE",
        "VERB_TRANSITIVE",
        "VERB_INTRANSITIVE",
        "IMPERATIVE"
    };

#endif /* _SPEECH_DEFINITIONS_H_ */
