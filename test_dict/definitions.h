const int POS_FILES = 13;
const int POS_SEARCH_STRINGS = 20;
const char *NEW_WORD_TAG = "<h1>";
const char *POS_TAG = "<tt>";
const int LAST_UNIQUE_POS = 12;

const char *pos_search_strings[POS_SEARCH_STRINGS] = {
    "",
    "<tt>n.</tt>",
    "<tt>a.</tt>",
    "<tt>adv.</tt>",
    "<tt>pron.</tt>",
    "<tt>interj.</tt>",
    "<tt>conj.</tt>",
    "<tt>prep.</tt>",
    "<tt>v.</tt>",
    "<tt>p.p.</tt>",
    "<tt>v.t.</tt>",
    "<tt>v.i.</tt>",
    "<tt>pret.</tt>",
    "<tt>v. t.</tt>",
    "<tt>v. i.</tt>",
    "<tt>n. pl.</tt>",
    "<tt>adv. & a.</tt>",
    "<tt>prep. or adv.</tt>",
    "<tt>adv. & prep.</tt>",
    "<tt>prep. & adv.</tt>",
};

const char *pos_files[POS_FILES] = {
    "none.txt",
    "nouns.txt",
    "adjectives.txt",
    "adverbs.txt",
    "pronouns.txt",
    "interjections.txt",
    "conjunctions.txt",
    "prepositions.txt",
    "verbs.txt",
    "verbs_past_participle.txt",
    "verbs_transitive.txt",
    "verbs_intransitive.txt",
    "preterites.txt",
};

std::fstream file_streams[POS_FILES];

const char *identifiers_pos_file_map[POS_SEARCH_STRINGS] = {
    "none.txt",
    "nouns.txt",
    "adjectives.txt",
    "adverbs.txt",
    "pronouns.txt",
    "interjections.txt",
    "conjunctions.txt",
    "prepositions.txt",
    "verbs.txt",
    "verbs_past_participle.txt",
    "verbs_transitive.txt",
    "verbs_intransitive.txt",
    "preterites.txt",
    "verbs_transitive.txt",
    "verbs_intransitive.txt",
    "nouns.txt",
    "none.txt",
    "none.txt",
    "none.txt",
    "none.txt"};

enum POS_IDENTIFIERS_MAP {
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
  VERB_PRETERITE, // LAST_UNIQUE_POS == 12
  VERB_TRANSITIVE_SPACE,
  VERB_INTRANSITIVE_SPACE,
  NOUN_PLURAL,
  ADVERB_ADJECTIVE,
  PREPOSITION_ADVERB_OR,
  ADVERB_PREPOSITION,
  PREPOSITION_ADVERB_AMP,
};

const int pos_masks[POS_SEARCH_STRINGS] = {
    /*0 NONE=*/0x0,
    /*1 NOUN=*/0x1,
    /*2 ADJECTIVE=*/0x2,
    /*3 ADVERB=*/0x4,
    /*4 PRONOUN=*/0x8,
    /*5 INTERJECTION=*/0x10,
    /*6 CONJUNCTION=*/0x20,
    /*7 PREPOSITION=*/0x40,
    /*8 VERB=*/0x80,
    /*9 VERB_PAST_PARTICIPLE=*/0x100,
    /*10 VERB_TRANSITIVE=*/0x200,
    /*11 VERB_INTRANSITIVE=*/0x400,
    /*12 VERB_PRETERITE=*/0x800,
    /*13 VERB_TRANSITIVE_SPACE=*/0x200,
    /*14 VERB_INTRANSITIVE_SPACE=*/0x400,
    /*15 NOUN_PLURAL=*/0x1,
    /*16 ADVERB_ADJECTIVE=*/0x4 | 0x2,
    /*17 PREPOSITION_ADVERB_OR=*/0x40 | 0x4,
    /*18 ADVERB_PREPOSITION=*/0x4 | 0x40,
    /*19 PREPOSITION_ADVERB_AMP=*/0x40 | 0x4};

enum CURRENT_ACTION { NEW_WORD, PARSING_WORD };
