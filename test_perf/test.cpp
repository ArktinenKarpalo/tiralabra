#include "powerset.h"
#include "gtest/gtest.h"
#include "thompson.h"
#include "hopcroft.h"
#include "ds/node_nfa.h"
#include "ds/matcher.h"
#include "ioutils.h"

static std::vector<std::string> input_words;
class WordList : public ::testing::Test {
	protected:
	static void SetUpTestSuite() {
		input_words = utils::readFile("data/words.txt");
	}
};

static std::vector<std::string> input_world;
class World : public ::testing::Test {
	protected:
	static void SetUpTestSuite() {
		input_world = utils::readFile("data/world192.txt");
	}
};


TEST_F(WordList, DFA_MIN_suffix_ism) {
	Powerset *ps = new Powerset(".*ism");
	Hopcroft *hc = new Hopcroft(ps);
	for(auto w : input_words) {
		if(hc->match(w)) {
		}
	}
	delete ps;
}

TEST_F(WordList, DFA_suffix_ism) {
	Powerset *ps = new Powerset(".*ism");
	for(auto w : input_words) {
		if(ps->match(w)) {
		}
	}
	delete ps;
}

TEST_F(WordList, NFA_suffix_ism) {
	Thompson *ts = new Thompson(".*ism");
	for(auto w : input_words) {
		if(ts->match(w)) {
		}
	}
	delete ts;
}

TEST_F(WordList, DFA_MIN_prefix_non) {
	Powerset *ps = new Powerset("non.*");
	Hopcroft *hc = new Hopcroft(ps);
	for(auto w : input_words) {
		if(hc->match(w)) {
		}
	}
	delete ps;
}

TEST_F(WordList, DFA_prefix_non) {
	Powerset *ps = new Powerset("non.*");
	for(auto w : input_words) {
		if(ps->match(w)) {
		}
	}
	delete ps;
}

TEST_F(WordList, NFA_prefix_non) {
	Thompson *ts = new Thompson("non.*");
	for(auto w : input_words) {
		if(ts->match(w)) {
		}
	}
	delete ts;
}

TEST_F(WordList, DFA_MIN_or) {
	Powerset *ps = new Powerset("colpus|okra|tulip");
	Hopcroft *hc = new Hopcroft(ps);
	for(auto w : input_words) {
		if(hc->match(w)) {
		}
	}
	delete ps;
}

TEST_F(WordList, DFA_or) {
	Powerset *ps = new Powerset("colpus|okra|tulip");
	for(auto w : input_words) {
		if(ps->match(w)) {
		}
	}
	delete ps;
}

TEST_F(WordList, NFA_or) {
	Thompson *ts = new Thompson("colpus|okra|tulip");
	for(auto w : input_words) {
		if(ts->match(w)) {
		}
	}
	delete ts;
}

TEST_F(WordList, DFA_MIN_substr) {
	Powerset *ps = new Powerset(".*c.*a.*t.*");
	Hopcroft *hc = new Hopcroft(ps);
	for(auto w : input_words) {
		if(hc->match(w)) {
		}
	}
	delete ps;
}

TEST_F(WordList, DFA_cat_substr) {
	Powerset *ps = new Powerset(".*c.*a.*t.*");
	for(auto w : input_words) {
		if(ps->match(w)) {
		}
	}
	delete ps;
}

TEST_F(WordList, NFA_cat_substr) {
	Thompson *ts = new Thompson(".*c.*a.*t.*");
	for(auto w : input_words) {
		if(ts->match(w)) {
		}
	}
	delete ts;
}

TEST_F(World, DFA_MIN_word_rate) {
	Powerset *ps = new Powerset("rate");
	Hopcroft *hc = new Hopcroft(ps);
	for(auto w : input_words) {
		if(hc->match(w)) {
		}
	}
	delete ps;
}

TEST_F(World, DFA_word_rate) {
	Powerset *ps = new Powerset("rate");
	for(auto w : input_words) {
		if(ps->match(w)) {
		}
	}
	delete ps;
}

TEST_F(World, NFA_word_rate) {
	Thompson *ts = new Thompson("rate");
	for(auto w : input_words) {
		if(ts->match(w)) {
		}
	}
	delete ts;
}